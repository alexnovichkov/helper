#ifndef AUTO_C11_H
#define AUTO_C11_H

#include <initializer_list>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <atomic>

void usingAuto()
{
    //Ключевое слово auto позволяет не указывать тип переменной при ее объявлении.
    //Тип переменной определяется компилятором из значения переменной при инициализации:

    auto i = 42;          // int
    auto d = 42.5;        // double
    auto s = "text";      // char const *
    auto v = { 1, 2, 3 }; // std::initializer_list<int>

    //Если требуется переменная конкретного типа, то следует использовать
    //auto name = type-id { expression };
    //auto name = function ( arguments );

    auto b  = new char[10]{ 0 };            // char*
    auto s1 = std::string {"text"};         // std::string
    auto v1 = std::vector<int> { 1, 2, 3 }; // std::vector<int>
    auto p  = std::make_shared<int>(42);    // std::shared_ptr<int>

    //С помощью auto можно объявлять именованные лямбда-функции,
    //если лямбда-функцию не требуется передавать или возвращать из функции:

    auto upper = [](char const c) {return toupper(c); };

    //Объявление параметров лямбды с помощью auto:

    auto add = [](auto const a, auto const b) {return a + b;};

    //С помощью auto можно попросить компилятор вывести тип возвращаемого значения, если он неизвестен
    //(но может быть выведен при компиляции) или не важен:

    template <typename F, typename T>
    auto apply(F&& f, T value)
    {
      return f(value);
    }
}

void benefitsOfAuto()
{
    //Преимущества использования auto:
    //--------------------------------

    //1. Невозможность оставить переменную неинициализированной. Объявление переменной с помощью auto
    //требует инициализирующего значения, чтобы компилятор мог вывести тип переменной.

    //2. Исключается ошибка неявного приведения типов.
    //Например, определение размера вектора: стандартный метод size() возвращает size_t.
    auto v = std::vector<int>{ 1, 2, 3 };
    int size1 = v.size(); // неявное преобразование size_t->int, возможна потеря точности
    auto size2 = v.size(); // OK, переменная size2 имеет тип size_t

    //3. Использование auto предпочтительно в хорошей объектно-ориентированной программе,
    //так как добавляет абстракции в код: код становится проще менять (под другие типы),
    //и он перестает зависеть от конкретных типов

    //4. Во многих случаях, даже если мы явно указываем конкретный тип, нам он не важен.
    //Типичный пример: итераторы. Если вы итерируете по контейнеру, вас не волнует настоящий тип
    //итератора, только сам итератор. Поэтому использование auto сокращает время на набор кода и упрощает
    //семантику кода.
    std::map<int, std::string> m;
    //явное использование типа итератора, долго набирать и приходится помнить имя типа, который вам не важен.
    for (std::map<int, std::string>::const_iterator
         it = m.cbegin();
         it != m.cend(); ++it)
    { /*...*/ }
    //использование auto для выведения типа итератора. Кратко и не затемняет суть кода
    for (auto it = m.cbegin(); it != m.cend(); ++it)
    { /*...*/ }

    //5. Объявления переменных приводятся к одному стилю - тип переменной всегда справа.
    //Сравните:
    int *p1 = new int[10]; //имя типа указано и справа и слева -> дублирование информации
    auto p2 = new int[10]; //имя типа только справа
}

void gotchasOfAuto()
{
    //Недостатки использования auto
    //-----------------------------

    //1. Слово auto - это заменитель только имени типа, но не квалификаторов типа const/volatile
    //и ссылок. Если вам нужны const/volatile и/или ссылка, их нужно указать явно.
    //В примере ниже метод foo.get() возвращает ссылку на int. При инициализации переменной x
    //из возвращаемого значения выводимый компилятором тип будет int, а не int&.
    //Поэтому любые изменения x не повлияют на foo.x_ (как планировалось автором класса).
    //Требуется явно указать auto&:

    class foo {
        int x_;
    public:
        foo(int const x = 0) :x_{ x } {}
        int& get() { return x_; }
    };
    foo f(42);
    auto x = f.get(); //ошибка
    //auto &x = f.get(); //OK
    x = 100;
    std::cout << f.get() << '\n'; // prints 42

    //2. Невозможно использовать auto для неперемещаемых типов:
    auto ai = std::atomic<int>(42); // ошибка!

    //3. Невозможно использовать auto для многосложных типов, таких как long long, long double
    //Придется добавлять литералы или использовать синонимы типов:

    auto l1 = long long{ 42 }; // ошибка
    using llong = long long;
    auto l2 = llong{ 42 };     // OK - синоним типа
    auto l3 = 42LL;            // OK - литерал
}

//Слово auto можно использовать для указания типа возвращаемого из функции значения.
//В C++11 необходимо использовать особую форму объявления функции.
//В C++14 это требование снято, компилятор выведет тип возвращаемого значения из типа переменной
//в выражении с return. Все точки выхода из функции должны иметь одинаковый тип:
// C++11
auto func1(int const i) -> int
{
    return 2*i;
}
// C++14
auto func2(int const i)
{
    return 2*i;
}

//Как упоминалось выше, auto не хранит const/volatile и &. Это ведет к проблемам при использовании
//auto в качестве возвращаемого типа.
//Рассмотрим уже приведенный метод foo.get(). На этот раз добавим функцию-обертку proxy_get()
//которая принимает ссылку на foo, вызывает get() и возвращает значение, полученное из get(),
//которое имеет тип int&. Однако компилятор выводит тип возвращаемого значения proxy_get()
//равным int, а не int&. Это приведет к попытке присвоить int в int&:

class foo
{
    int x_;
public:
    foo(int const x = 0) :x_{ x } {}
    int& get() { return x_; } //возвращаемый тип равен int&
};
auto proxy_get(foo& f) { return f.get(); } //возвращаемый тип равен int
auto f = foo{ 42 };
auto& x = proxy_get(f); // невозможно преобразовать 'int' в 'int &'

//Эту проблему можно решить в C++14, применяя явный вывод типа с помощью decltype:
//возвращаемый тип выводится компилятором на основе типа f.get();, то есть равен int&
decltype(auto) proxy_get1(foo& f) { return f.get(); }
auto f1 = foo{ 42 };
decltype(auto) x1 = proxy_get1(f); //тип x1 выводится компилятором на основе возвращаемого типа proxy_get1

//Слово decltype применяется для исследования объявленного типа объекта, класса или выражения.
//В основном его применяют, когда стандартный синтаксис C++ не позволяет объявить нужный тип.
//Например, при объявлении типа лямбда-функции или типа, зависящего от параметров шаблона.

//Слово auto очень полезно при объявлении так называемых обобщенных лямбда-функций,
//в которых и тип аргументов, и тип возвращаемого значения не важен, а важна только логика:
auto ladd = [] (auto const a, auto const b) { return a + b; };
//В этом примере лямбда-функция скомпилируется для любых типов переменных a и b, для которых
//определен оператор +.
auto i = ladd(40, 2);            // 42

using namespace std::literals::string_literals;
auto s = ladd("forty"s, "two"s); // "fortytwo"s

//Обобщенные лямбды можно использовать начиная с C++14.

#endif // AUTO_C11_H
