#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <vector>
#include <string>
#include "Cell.h"
#include "ParseConsole.h"
#include <fstream>
#include <iostream>

class Universe {
private:
    int grid_size;                    // ������ ��������� (����� ������� ����������� ����)
    int currentIteration = 0;         // ������� �������� ����
    std::string universe_rule;  // ������� �������� ������, ����������� �� �����
    std::string universe_name;
    std::vector<std::vector<Cell>> grid; // ��������� ������ ������, �������������� ���������

    std::vector<int> birthConditions;    // ������� ��� �������� ������
    std::vector<int> survivalConditions; // ������� ��� ��������� ������

    // ��������������� ������
    bool willBeAlive(int x, int y) const;       // ���������, ����� �� ������ ���� �� ��������� ����
    int countAliveNeighbors(int x, int y) const; // ������������ ���������� ����� �������
    void parseRule(const std::string& rule);    // ��������� ������� ����� �������� �� �����

public:
    // �����������, ����������� ������ ������ ���������
    Universe(int grid_size);

    // ����� ��� ������������� ���������, ���������� true ��� �������� ��������
    bool initialize(const ParseConsole& parser);

    // ����� ��� ������� � �������-������ (� �������� ����������� ��������)
    void runOffline(int iterations, const std::string& outputFile = "");

    // ����� ��� ������� � ������-������ (������� ������� � �������)
    void runOnline();

    // �������� ������ ��� ���������� �������� � ����������� ��������� ���������
    void tick(int iterations = 1);
    void display() const;

    // ������ ��� ������ � ���������� ��������
    void setCell(int x, int y, bool alive);
    bool getCell(int x, int y) const;

    // ������ ��� ���������� � �������� ��������� ��������� �� ������
    bool saveToStream(std::ostream& os) const;
    bool loadFromStream(std::istream& is);

    friend std::istream& operator>>(std::istream& is, Universe& universe);
    friend std::ostream& operator<<(std::ostream& os, const Universe& universe);
    friend class TestUniverse;
};

#endif // UNIVERSE_H
