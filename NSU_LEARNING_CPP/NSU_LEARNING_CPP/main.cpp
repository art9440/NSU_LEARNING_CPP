#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>
using namespace std; //можно написать в начале cpp файла, чтобы не писать везде std::

int main(int argc, char **argv)
{
    std::cout << "Hello world!" << "\n";

    cout << Module1::getMyName() << "\n";
    std::cout << Module2::getMyName() << "\n";

    using namespace Module1;
    std::cout << getMyName() << "\n"; // (A) -- John
    // В этом случае компилятор не выдал ошибки call of overloaded ____ is ambiguous,
    // так как ему не надо было выбирать какой метод использовать
    std::cout << Module2::getMyName() << "\n";
    


    using namespace Module2;                   // (B)
    std::cout << Module2::getMyName() << "\n"; // COMPILATION ERROR (C)
                                               // Проблема компиляции происходит из-за того, что компилятор не может выбрать какой
                                               // именно из методов getMyName использовать в данном случае, так как мы неявно
                                               // обозначаем пространство имен для Module2
    using Module2::getMyName;
    std::cout << getMyName() << "\n"; // (D) -- James

    std::cout << Module3::getMyName() << "\n"; // -- Peter
}
