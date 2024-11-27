#include <vector>
#include <cstdint>
#include <iostream>
#include "memory"

class Converter {
public:
    virtual ~Converter() = default;

    virtual std::vector<int16_t> process(const std::vector<int16_t>& input) = 0;

    // Убедитесь, что сигнатура метода setParams совпадает с производными классами
    virtual void setParams(const std::vector<int>& params) = 0;
};

// MuteConverter
class MuteConverter : public Converter {
public:
    MuteConverter(int start = 0, int end = 0);
    std::vector<int16_t> process(const std::vector<int16_t>& input) override;
    void setParams(const std::vector<int>& params) override; // Совпадает с базовым классом

private:
    int start, end;
};

// MixConverter
class MixConverter : public Converter {
public:
    MixConverter(const std::vector<int16_t>& additionalStream, int startPosition = 0);
    std::vector<int16_t> process(const std::vector<int16_t>& input) override;
    void setParams(const std::vector<int>& params) override; // Совпадает с базовым классом

private:
    std::vector<int16_t> additionalStream;
    int startPosition;
};

// EchoConverter
class EchoConverter : public Converter {
public:
    EchoConverter(int delay = 0, float decay = 0.5f);
    std::vector<int16_t> process(const std::vector<int16_t>& input) override;
    void setParams(const std::vector<int>& params) override; // Совпадает с базовым классом

private:
    int delay;
    float decay;
};
