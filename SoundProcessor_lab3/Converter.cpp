#include "Converter.h"

MuteConverter::MuteConverter(int start, int end): start(start), end(end) {}


std::vector<int16_t> MuteConverter::process(const std::vector<int16_t>& input)
{
    std::vector<int16_t> output = input;
    // Применяем "заглушку" на интервале [start, end]
    for (int i = start; i < end && i < output.size(); ++i) {
        output[i] = 0;
    }
    return output;
}