#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class WavFile {
public:
    WavFile();
    bool read(const std::string& filename);
    bool write(const std::string& filename);

    std::vector<int16_t>& getSamples();
    int getSampleRate() const;
    int getNumChannels() const;

private:
    struct WavHeader {
        char chunkId[4];
        uint32_t chunkSize;
        char format[4];
        char subchunk1Id[4];
        uint32_t subchunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
        char subchunk2Id[4];
        uint32_t subchunk2Size;
    };

    WavHeader header;
    std::vector<int16_t> samples;
    
};