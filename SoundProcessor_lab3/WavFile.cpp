#include "WavFile.h"

WavFile::WavFile() {
	header = { {'R', 'I', 'F', 'F'}, 0, {'W', 'A', 'V', 'E'}, {'f', 'm', 't', ' '},
			   16, 1, 1, 44100, 44100 * 2, 2, 16, {'d', 'a', 't', 'a'}, 0 };
}

bool WavFile::read(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << " для чтения." << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(WavHeader));
    if (header.audioFormat != 1 || header.numChannels != 1 || header.bitsPerSample != 16 || header.sampleRate != 44100) {
        std::cerr << "Ошибка: неподдерживаемый формат файла WAV." << std::endl;
        return false;
    }

    samples.resize(header.subchunk2Size / sizeof(int16_t));
    file.read(reinterpret_cast<char*>(samples.data()), header.subchunk2Size);
    file.close();
    return true;
}

bool WavFile::write(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << " для чтения." << std::endl;
        return false;
    }

    header.chunkSize = 36 + samples.size() * sizeof(int16_t);
    header.subchunk2Size = samples.size() * sizeof(int16_t);

    file.write(reinterpret_cast<char*>(&header), sizeof(WavHeader));
    file.write(reinterpret_cast<char*>(samples.data()), samples.size() * sizeof(int16_t));
    file.close();
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