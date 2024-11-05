#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool alive; // true, ���� ������ ����; false, ���� ������
public:
    // ����������� �� ��������� ������� ������� ������
    Cell(bool is_alive = false);

    // ���������� true, ���� ������ ����
    bool isAlive() const;

    // ������������� ��������� ������ (����/������)
    void setAlive(bool state);

    // ����������� ��������� ������ (���� ���� ���� � ���������� �������, � ��������)
    void toggle();


};

#endif // CELL_H

