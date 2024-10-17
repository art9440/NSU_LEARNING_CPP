#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>


const int BYTE_SIZE = 8;

class BitArray
{
private:
    std::vector<char> bit_array; // Вектор для хранения битов, где каждый элемент хранит 8 бит (char).
    int bit_count;               // Общее количество бит в массиве.

public:

    class BitReference {
    private:
        int bit_position;
        char& ref;
    public:
        BitReference(const char& ref, int bit_pos);

        BitReference& operator=(bool val);

        operator bool() const;
    };

    BitReference operator[](int i);


    // Конструктор по умолчанию. Инициализирует пустой BitArray.
    BitArray();

    // Деструктор. Освобождает память, если это необходимо.
    ~BitArray();

    // Конструирует массив, хранящий заданное количество бит.
    // Первые sizeof(long) бит можно инициализировать с помощью параметра value.
    explicit BitArray(int num_bits, unsigned long value = 0);

    // Конструктор копирования. Копирует содержимое другого BitArray.
    BitArray(const BitArray& b);

    // Обменивает значения двух битовых массивов.
    void swap(BitArray& b);

    // Оператор присваивания. Присваивает содержимое другого BitArray текущему объекту.
    BitArray& operator=(const BitArray& b);

    // Изменяет размер массива. В случае расширения, новые элементы инициализируются значением value.
    void resize(int num_bits, bool value = false);

    // Очищает массив, сбрасывая все биты.
    void clear();

    // Добавляет новый бит в конец массива. При необходимости происходит перераспределение памяти.
    void push_back(bool bit);

    // Битовая конъюнкция. Выполняет побитовое AND с другим BitArray.
    BitArray& operator&=(const BitArray& b);

    // Битовая дизъюнкция. Выполняет побитовое OR с другим BitArray.
    BitArray& operator|=(const BitArray& b);

    // Битовое XOR. Выполняет побитовое XOR с другим BitArray.
    BitArray& operator^=(const BitArray& b);

    // Битовый сдвиг влево с заполнением нулями.
    BitArray& operator<<=(int n);

    // Битовый сдвиг вправо с заполнением нулями.
    BitArray& operator>>=(int n);

    // Возвращает новый BitArray, сдвинутый влево на n бит.
    BitArray operator<<(int n) const;

    // Возвращает новый BitArray, сдвинутый вправо на n бит.
    BitArray operator>>(int n) const;

    // Устанавливает бит с индексом n в значение val.
    BitArray& set(int n, bool val = true);

    // Заполняет все биты массива значением true.
    BitArray& set();

    // Устанавливает бит с индексом n в значение false.
    BitArray& reset(int n);

    // Заполняет массив значениями false (сбрасывает все биты).
    BitArray& reset();

    // Возвращает true, если хотя бы один бит в массиве равен true (1).
    bool any() const;

    // Возвращает true, если все биты в массиве равны false (0).
    bool none() const;

    // Битовая инверсия. Возвращает новый массив с инвертированными битами.
    BitArray operator~() const;

    // Подсчитывает количество битов, установленных в 1.
    int count() const;

    // Возвращает значение бита по индексу i.
    bool operator[](int i) const;

    // Возвращает количество битов в массиве.
    int size() const;

    // Проверяет, является ли массив пустым (не содержит битов).
    bool empty() const;

    // Возвращает строковое представление массива битов.
    std::string to_string() const;

     //Класс итератора для доступа к битам BitArray.
    class Iterator {
    private:
        int index;                // Текущий индекс итератора.
        const BitArray* bitarr;    // Указатель на BitArray, по которому идет итерация.

    public:
        // Конструктор итератора для BitArray, начиная с индекса idx.
        Iterator(const BitArray* bArr, int idx);

        // Деструктор итератора.
        ~Iterator();

        // Разыменовывает итератор для доступа к значению текущего бита.
        BitReference operator*() const;

        // Оператор инкрементации. Переносит итератор на следующий бит.
        Iterator& operator++();

        // Оператор декрементации. Переносит итератор на предыдущий бит.
        Iterator& operator--();

        // Сравнение двух итераторов на неравенство.
        bool operator!=(const Iterator& iterator) const;

        // Сравнение двух итераторов на равенство.
        bool operator==(const Iterator& iterator) const;
    };

    // Возвращает итератор, указывающий на первый бит в массиве.
    Iterator begin();

    // Возвращает итератор, указывающий на позицию за последним битом в массиве.
    Iterator end();
};

// Сравнение двух BitArray на равенство.
bool operator==(const BitArray& a, const BitArray& b);

// Сравнение двух BitArray на неравенство.
bool operator!=(const BitArray& a, const BitArray& b);

// Возвращает результат побитового AND двух BitArray.
BitArray operator&(const BitArray& b1, const BitArray& b2);

// Возвращает результат побитового OR двух BitArray.
BitArray operator|(const BitArray& b1, const BitArray& b2);

// Возвращает результат побитового XOR двух BitArray.
BitArray operator^(const BitArray& b1, const BitArray& b2);
