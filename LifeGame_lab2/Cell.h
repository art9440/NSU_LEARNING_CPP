#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

class Cell {
public:
    // �����������, �������� ��������� ��������� ������
    Cell(bool is_alive = false) : alive(is_alive) {}

    // ����� ��� ��������, ���� �� ������
    bool isAlive() const { return alive; }

    // ����� ��� ��������� ��������� ������
    void setAlive(bool state) { alive = state; }

    // ������������ ��������� ������ (�����������)
    void toggle() { alive = !alive; }

private:
    bool alive; // ��������� ������: true - ����, false - ������
}; 