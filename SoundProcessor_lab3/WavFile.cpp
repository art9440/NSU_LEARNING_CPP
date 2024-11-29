#include "WavFile.h"
#include "Exceptions.h"
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
        throw WavFileOpenException(filename, "reading");
    }

    // 1. Читаем RIFF и формат
    inFile.read(header.chunkId, 4);
    if (std::strncmp(header.chunkId, "RIFF", 4) != 0) {
        throw InvalidWavFormatException(filename);
    }

    header.chunkSize = readUint32(inFile);

    inFile.read(header.format, 4);
    if (std::strncmp(header.format, "WAVE", 4) != 0) {
        throw InvalidWavFormatException(filename);
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
                throw InvalidWavFormatException(filename);
            }

            foundFmt = true;
        }
        else if (std::strncmp(subchunkId, "data", 4) == 0) {
            // Читаем подчанк 'data'
            header.subchunk2Size = subchunkSize;
            samples.resize(header.subchunk2Size / (header.bitsPerSample / 8));
            inFile.read(reinterpret_cast<char*>(samples.data()), header.subchunk2Size);

            if (!inFile) {
                throw WavFileReadException(filename);
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
        throw MissingSubchunkException(filename, "fmt ");
    }

    if (!foundData) {
        throw MissingSubchunkException(filename, "data");
    }

    std::cout << "Successfully read file: " << filename << std::endl;
    std::cout << "Number of samples: " << samples.size() << std::endl;
   
    return true;
}



bool WavFile::write(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw WavFileOpenException(filename, "writing");
    }

    // Write header as-is
    outFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    if (!outFile) {
        throw FileWriteException(filename);
    }

    // Write audio data
    if (samples.empty()) {
        throw FileWriteException(filename);
    }

    outFile.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(int16_t));
    if (!outFile) {
        throw FileWriteException(filename);
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
