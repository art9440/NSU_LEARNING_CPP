#include "Converter.h"

// Реализация MuteConverter
MuteConverter::MuteConverter(int start, int end) : start(start), end(end) {
    std::cout << "MuteConverter is done" << std::endl;
}

std::vector<int16_t> MuteConverter::process(const std::vector<int16_t>& input) {
    int start_ = start * 44100;
    int end_ = end * 44100;
    std::vector<int16_t> output = input;
    for (int i = start_; i < end_ && i < output.size(); ++i) {
        output[i] = 0;
    }
    return output;
}

void MuteConverter::setParams(const std::vector<int>& params) {
    if (params.size() >= 2) {
        start = params[0];
        end = params[1];
    }
}

// Реализация MixConverter
MixConverter::MixConverter(const std::vector<int16_t>& additionalStream, int startPosition)
    : additionalStream(additionalStream), startPosition(startPosition) {}

std::vector<int16_t> MixConverter::process(const std::vector<int16_t>& input) {
    std::vector<int16_t> output = input;
    for (size_t i = startPosition; i < output.size() && (i - startPosition) < additionalStream.size(); ++i) {
        int32_t mixedSample = static_cast<int32_t>(output[i]) + additionalStream[i - startPosition];
        // Ограничиваем значение в пределах диапазона int16_t
        if (mixedSample > INT16_MAX) {
            output[i] = INT16_MAX;
        }
        else if (mixedSample < INT16_MIN) {
            output[i] = INT16_MIN;
        }
        else {
            output[i] = static_cast<int16_t>(mixedSample);
        }
    }
    return output;
}

void MixConverter::setParams(const std::vector<int>& params) {
    if (!params.empty()) {
        startPosition = params[0];
    }
}

// Реализация EchoConverter
EchoConverter::EchoConverter(int delay, float decay) : delay(delay), decay(decay) {}

std::vector<int16_t> EchoConverter::process(const std::vector<int16_t>& input) {
    std::vector<int16_t> output = input;
    for (size_t i = delay; i < output.size(); ++i) {
        int16_t echoSample = static_cast<int16_t>(output[i - delay] * decay);
        int32_t mixedSample = static_cast<int32_t>(output[i]) + echoSample;

        // Ограничиваем значение в пределах диапазона int16_t
        if (mixedSample > INT16_MAX) {
            output[i] = INT16_MAX;
        }
        else if (mixedSample < INT16_MIN) {
            output[i] = INT16_MIN;
        }
        else {
            output[i] = static_cast<int16_t>(mixedSample);
        }
    }
    return output;
}

void EchoConverter::setParams(const std::vector<int>& params) {
    if (params.size() >= 2) {
        delay = params[0];
        decay = static_cast<float>(params[1]) / 100.0f; // Преобразуем значение в процентах в коэффициент
    }
}
