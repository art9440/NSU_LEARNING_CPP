#include <vector>
#include <string>
#include "Converter.h"

class ConfigParser {
public:
    // ����� ��� ������ ����������������� ����� � �������� �����������
    bool readConfigFile(const std::string& filename, std::vector<Converter*>& converters);

private:
    // ����� ��� �������� ������ ������������ � ���������� ���� �������
    bool parseLine(const std::string& line, std::string& command, std::vector<int>& params);

    // ����� ��� �������� ���������� �� ������ ������� � ����������
    Converter* createConverter(const std::string& command, const std::vector<int>& params);
};

