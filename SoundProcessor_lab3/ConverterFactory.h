#ifndef CONVERTERFACTORY_H
#define CONVERTERFACTORY_H

#include <string>
#include <vector>
#include "Converter.h"
#include "WavFile.h"

class ConverterFactory {
public:
    // ����� ��� ��������� ������ ������������ � �������� ����������
    static std::unique_ptr<Converter> createConverterFromLine(const std::string& line,
        std::vector<WavFile>& inputWavs);
};

#endif // CONVERTERFACTORY_H
