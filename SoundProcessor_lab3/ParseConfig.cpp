#include "ParseConfig.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool ConfigParser::readConfigFile(const std::string& filename, std::vector<Converter*>& converters) {
    std::ifstream config(filename);
    if (!config) {
        std::cerr << "������: �� ������� ������� ���� " << filename << " ��� ������." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(config, line)) {
        // ���������� ������ ������ � �����������
        if (line.empty() || line[0] == '#') continue;

        std::string command;
        std::vector<int> params;

        // ������ ������ � ��������� �������
        if (!parseLine(line, command, params)) {
            std::cerr << "������: �������� ������������ � ������: " << line << std::endl;
            return false;
        }

        // ������� ��������� �� ������ ������� � ����������
        Converter* converter = createConverter(command, params);
        if (!converter) {
            std::cerr << "������: �� ������� ������� ��������� ��� �������: " << command << std::endl;
            return false;
        }

        converters.push_back(converter);
    }
    return true;
}

bool ConfigParser::parseLine(const std::string& line, std::string& command, std::vector<int>& params) {
    std::istringstream iss(line);
    iss >> command;

    // �������� �� ���������� �������
    if (command != "mix" && command != "mute" && command != "echo") {
        return false;
    }

    // ��������� ��������� �� ������
    int param;
    while (iss >> param) {
        params.push_back(param);
    }

    // �������� ���������� � ����������� �� �������
    if (command == "mix") {
        return params.size() >= 2; // mix ������� ��� ������� 2 ���������
    }
    else if (command == "mute") {
        return params.size() == 2; // mute ������� ����� 2 ���������
    }
    else if (command == "echo") {
        return params.size() >= 1; // echo ������� ��� ������� 1 ��������
    }
    return false;
}

Converter* ConfigParser::createConverter(const std::string& command, const std::vector<int>& params) {
    if (command == "mute") {
        // ������� MuteConverter � ����������� start � end
        return new MuteConverter(params[0], params[1]);
    }
    else if (command == "mix") {
        // ������� MixConverter. ��������� �������������� ����� (��������, params[1] ��������� �� ������)
        // ����� ����� �������� �������������� �����, ��������, �� inputWavs
        // ��������, ��� ��� ���������� ������
        std::vector<int16_t> additionalStream; // ����� �������� ��������� �����
        return new MixConverter(additionalStream, params[0]);
    }
    else if (command == "echo") {
        // ������� EchoConverter � ����������� delay � decay
        int delay = params[0];
        float decay = params.size() > 1 ? static_cast<float>(params[1]) / 100.0f : 0.5f;
        return new EchoConverter(delay, decay);
    }
    return nullptr;
}