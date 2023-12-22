#ifndef NEW_IN_C17_H
#define NEW_IN_C17_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

/**
 * Этот файл демонстрирует возможности C++17
 */

using namespace std;

pair<int,int> divide_reminder(int dividend, int divisor)
{
    return {dividend / divisor, dividend % divisor};
}

/**
 * пример декомпозиции структур
 * Применяется для pair, tuple, map, structure
 */
void decomposition()
{
    //декомпозиция пары
    const auto [fraction, remainder] = divide_reminder(16, 3);
    cout << "16/3 is "<<fraction <<" * 3 + "<< remainder<<endl;

    //декомпозиция работает и для tuple, map, и для пользовательских структур:
    struct employee {
        string name;
        int salary;
    };

    vector<employee> employees {{"Alex", 200}, {"Hellen", 250}};
    for (const auto &[name, salary]: employees) {
        cout << "Name: "<< name
             << ", Salary: "<< salary <<endl;
    }
}

/**
 * Пример вывода типа класса шаблона
 * Применяется для pair, tuple, собственных классов
 */
template <typename T1, typename T2>
class wrapper {
    T1 t1;
    T2 t2;
public:
    explicit wrapper(T1 t1, T2 t2) : t1(t1), t2(t2) {}
};

void templateTypeDeduction()
{
    //вместо старой записи
    wrapper<int, string> w1 {2, "abc"};
    //можно писать
    wrapper w2 {3, "def"};

    //аналогично для pair, tuple, map
    pair p {2,2};
}

/**
 * пример ограничения области видимости
 * Применяется в if и switch
 */
void hideLocalIfSwitch()
{
    switch (auto var(12); var) {
        case 1: {break;}
        case 2: break;
        case 12: break;
    }

    if (auto var=12; var >= 0) {
        cout<<"Var is "<<var<<endl;
    }
}

/**
 * @brief folding
 * Пример использования свертки параметров шаблонов
 */

//правая или левая ассоциативная свертка
//допустима для операторов:
// + - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*
template<typename...T>
auto sum(T...t)
{
    return (t+...); //правая свертка
    return (...+t); //левая свертка
}

//бинарная свертка с начальным значением
template<typename... T>
auto binarySum(T...t)
{
    return (t+...+0); //правая свертка
    return (0+...+t); //левая свертка

}

//содержит ли диапазон хотя бы одно из значений
template<typename R, typename...Ts>
auto matchesAny(const R &range, Ts...ts)
{
    return (std::count(begin(range), end(range), ts)+...);
}

//попадают ли все элементы в диапазон
template<typename T, typename...Ts>
bool within(T min, T max, Ts...ts)
{
    return ((min <= ts && ts <= max) && ...);
}

//отправить все элементы в вектор
template<typename T, typename...Ts>
void insertMulti(vector<T> &vec, Ts...ts)
{
    (vec.push_back(ts), ...);
}

void folding()
{
    //использование суммирования
    int theSum {sum(1,2,3,4,5,6)};

    //для строк нужно использовать переменные соответствующего типа:
    auto str1 = "abc"s;
    auto str2 = "def"s;
    string stringSum {sum(str1, str2)};
    cout << theSum <<" "<<stringSum << endl;

    //cout << sum(); //ошибка! унарная свертка без начального значения!

    cout << binarySum() << " "<< binarySum(1,2,3)<<endl;

    vector<int> v{1,2,3,4,5};
    cout << matchesAny(v,2,5)<<endl; //2
    cout << matchesAny(v, 100,200)<<endl; //0
    cout << matchesAny("abcdef", 'f','g')<<endl; //1
}

#endif // NEW_IN_C17_H
