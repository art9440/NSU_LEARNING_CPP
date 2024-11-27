#include <vector>
#include <cstdint>
#include <iostream>
#include "memory"

class Converter {
public:
    virtual ~Converter() = default;

    virtual std::vector<int16_t> process(const std::vector<int16_t>& input) = 0;

    // ���������, ��� ��������� ������ setParams ��������� � ������������ ��������
    virtual void setParams(const std::vector<int>& params) = 0;
};

// MuteConverter
class MuteConverter : public Converter {
public:
    MuteConverter(int start = 0, int end = 0);
    std::vector<int16_t> process(const std::vector<int16_t>& input) override;
    void setParams(const std::vector<int>& params) override; // ��������� � ������� �������

private:
    int start, end;
};

// MixConverter
class MixConverter : public Converter {
public:
    MixConverter(const std::vector<int16_t>& additionalStream, int startPosition = 0);
    std::vector<int16_t> process(const std::vector<int16_t>& input) override;
    void setParams(const std::vector<int>& params) override; // ��������� � ������� �������

private:
    std::vector<int16_t> additionalStream;
    int startPosition;
};

// EchoConverter
class EchoConverter : public Converter {
public:
    EchoConverter(int delay = 0, float decay = 0.5f);
    std::vector<int16_t> process(const std::vector<int16_t>& input) override;
    void setParams(const std::vector<int>& params) override; // ��������� � ������� �������

private:
    int delay;
    float decay;
};
