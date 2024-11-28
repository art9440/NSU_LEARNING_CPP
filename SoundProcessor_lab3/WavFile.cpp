#include "WavFile.h"
#include <cstring>
#include <stdexcept>
#include <algorithm>

WavFile::WavFile() {
    // Инициализация стандартного заголовка для WAV-файла
    header = {{'R', 'I', 'F', 'F'},  // chunkId
        0,                     // chunkSize (заполнится позже)
        {'W', 'A', 'V', 'E'},  // format
        {'f', 'm', 't', ' '},  // subchunk1Id
        16,                    // subchunk1Size (для PCM)
        1,                     // audioFormat (1 = PCM)
        1,                     // numChannels (моно)
        44100,                 // sampleRate
        88200,                 // byteRate (sampleRate * numChannels * bitsPerSample / 8)
        2,                     // blockAlign (numChannels * bitsPerSample / 8)
        16,                    // bitsPerSample
        {'d', 'a', 't', 'a'},  // subchunk2Id
        0                      // subchunk2Size (заполнится позже)
    };
}

bool WavFile::read(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Failed to open file " << filename << " for reading." << std::endl;
        return false;
    }

    // 1. Читаем RIFF и формат
    inFile.read(header.chunkId, 4);
    if (std::strncmp(header.chunkId, "RIFF", 4) != 0) {
        std::cerr << "Error: Missing 'RIFF' identifier in WAV file." << std::endl;
        return false;
    }

    header.chunkSize = readUint32(inFile);

    inFile.read(header.format, 4);
    if (std::strncmp(header.format, "WAVE", 4) != 0) {
        std::cerr << "Error: Missing 'WAVE' format identifier." << std::endl;
        return false;
    }

    // 2. Перебираем подчанки, пока не найдём 'fmt ' и 'data'
    bool foundFmt = false;
    bool foundData = false;

    while (!inFile.eof()) {
        char subchunkId[4];
        inFile.read(subchunkId, 4);  // Читаем идентификатор чанка
        uint32_t subchunkSize = readUint32(inFile);  // Размер чанка

        if (std::strncmp(subchunkId, "fmt ", 4) == 0) {
            // Читаем подчанк 'fmt '
            header.subchunk1Size = subchunkSize;
            header.audioFormat = readUint16(inFile);
            header.numChannels = readUint16(inFile);
            header.sampleRate = readUint32(inFile);
            header.byteRate = readUint32(inFile);
            header.blockAlign = readUint16(inFile);
            header.bitsPerSample = readUint16(inFile);

            if (header.audioFormat != 1 || header.numChannels != 1 || header.bitsPerSample != 16 || header.sampleRate != 44100) {
                std::cerr << "Error: Unsupported WAV format (must be PCM, mono, 16-bit, 44100 Hz)." << std::endl;
                return false;
            }

            foundFmt = true;
        }
        else if (std::strncmp(subchunkId, "data", 4) == 0) {
            // Читаем подчанк 'data'
            header.subchunk2Size = subchunkSize;
            samples.resize(header.subchunk2Size / (header.bitsPerSample / 8));
            inFile.read(reinterpret_cast<char*>(samples.data()), header.subchunk2Size);

            if (!inFile) {
                std::cerr << "Error: Failed to read audio data from WAV file." << std::endl;
                return false;
            }

            foundData = true;
            break;  // Завершаем перебор после нахождения 'data'
        }
        else {
            // Пропускаем неизвестный подчанк
            inFile.seekg(subchunkSize, std::ios::cur);
        }
    }

    if (!foundFmt) {
        std::cerr << "Error: Missing 'fmt ' subchunk in WAV file." << std::endl;
        return false;
    }

    if (!foundData) {
        std::cerr << "Error: Missing 'data' subchunk in WAV file." << std::endl;
        return false;
    }

    std::cout << "Successfully read file: " << filename << std::endl;
    std::cout << "Number of samples: " << samples.size() << std::endl;

    return true;
}



bool WavFile::write(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Can't open file for writing: " << filename << std::endl;
        return false;
    }

    // Write header as-is
    outFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    if (!outFile) {
        std::cerr << "Error: Can't write header to file: " << filename << std::endl;
        return false;
    }

    // Write audio data
    if (samples.empty()) {
        std::cerr << "Error: No samples to write to file: " << filename << std::endl;
        return false;
    }

    outFile.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(int16_t));
    if (!outFile) {
        std::cerr << "Error: Can't write audio data to file: " << filename << std::endl;
        return false;
    }

    std::cout << "Successfully wrote file: " << filename << std::endl;

    return true;
}

std::vector<int16_t>& WavFile::getSamples() {
    return samples;
}

int WavFile::getSampleRate() const {
    return header.sampleRate;
}

int WavFile::getNumChannels() const {
    return header.numChannels;
}


uint16_t WavFile::readUint16(std::ifstream& inFile) {
    uint16_t value;
    inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
    if (!inFile) {
        throw std::runtime_error("Error: Failed to read uint16_t from file.");
    }
    return value;
}

uint32_t WavFile::readUint32(std::ifstream& inFile) {
    uint32_t value;
    inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
    if (!inFile) {
        throw std::runtime_error("Error: Failed to read uint32_t from file.");
    }
    return value;
}
