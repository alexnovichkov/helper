#ifndef STL_ALGORITHMS_H
#define STL_ALGORITHMS_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>

//Алгоритмы, применяющие функцию к диапазону элементов
//----------------------------------------------------
// Function std::for_each(InIt first, InIt last, Function function)
// OutIt transform(InIt first1, InIt last1, OutIt target, UnaOp operation)
// OutIt transform(InIt1 first1, InIt1 last1, InIt2 first2, OutIt target, BinOp operation)

//Алгоритмы проверки элементов в контейнере
//---------------------------------------
//bool all_of(InIt first, InIt last, UnaPred predicate)
//bool none_of(InIt first, InIt last, UnaPred predicate)
//bool any_of(InIt first, InIt last, UnaPred predicate)
//DiffType count(InIt first, InIt last, const T& value)
//DiffType count_if(InIt first, InIt last, UnaPred predicate)

//Алгоритмы поиска элементов в контейнере
//---------------------------------------
//InIt find(InIt first, InIt last, const T& value)
//InIt find_if(InIt first, InIt last, UnaPred predicate)
//InIt find_if_not(InIt first, InIt last, UnaPred predicate)
//InIt find_first_of(InIt first1, InIt last1, FwIt first2, FwIt last2[, BinPred predicate])
//FwIt adjacent_find(FwIt first, FwIt last[, BinPred predicate])

// Алгоритмы бинарного поиска
//---------------------------
// bool binary_search(FwIt first, FwIt last, const T& value[, Compare comp])
// FwIt lower_bound(FwIt first, FwIt last, const T& value[, Compare comp])
// FwIt upper_bound(FwIt first, FwIt last, const T& value[, Compare comp])
// pair<FwIt, FwIt> equal_range(FwIt first, FwIt last, const T& value[, Compare comp])

//Алгоритмы поиска подпоследовательностей
//---------------------------------------
//FwIt1 search(FwIt1 first1, FwIt1 last1, FwIt2 first2, FwIt2 last2[, BinPred predicate])
//FwIt1 find_end(FwIt1 first1, FwIt1 last1, FwIt2 first2, FwIt2 last2[, BinPred predicate])
//FwIt search_n(FwIt first, FwIt last, Size count, const T& value[, BinPred predicate])

//Алгоритмы поиска минимума и максимума
//-------------------------------------
//const T& min(const T& a, const T& b[, Compare comp])
//const T& max(const T& a, const T& b[, Compare comp])
//T min(initializer_list<T> t[, Compare comp])
//T max(initializer_list<T> t[, Compare comp])
//pair<const T&, const T&> minmax(const T& a, const T& b[, Compare comp])
//pair<T, T> minmax(initializer_list<T> t[, Compare comp])
//FwIt min_element(FwIt first, FwIt last[, Compare comp])
//FwIt max_element(FwIt first, FwIt last[, Compare comp])
//pair<FwIt, FwIt> minmax_element(FwIt first, FwIt last[, Compare comp])

//Алгоритмы сравнения последовательностей
//---------------------------------------
//bool equal(InIt1 first1, InIt1 last1, InIt2 first2[, BinPred predicate])
//pair<InIt1, InIt2> mismatch(InIt1 first1, InIt1 last1, InIt2 first2[, BinPred predicate])
//bool equal(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2[, BinPred predicate])
//pair<InIt1, InIt2> mismatch(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2[, BinPred predicate])

//Алгоритмы копирования и перемещения
//----------------------------------
//OutIt copy(InIt first, InIt last, OutIt targetFirst)
//OutIt copy_if(InIt first, InIt last, OutIt targetFirst, UnaPred predicate)
//BidIt2 copy_backward(BidIt1 first, BidIt1 last, BidIt2 targetLast)
//OutIt copy_n(InIt start, Size count, OutIt target)
//OutIt move(InIt first, InIt last, OutIt targetFirst)
//BidIt2 move_backward(BidIt1 first, BidIt1 last, BidIt2 targetLast)
//FwIt2 swap_ranges(FwIt1 first1, FwIt1 last1, FwIt2 first2)

// Генерирующие алгоритмы
//-----------------------
//void fill(FwIt first, FwIt last, const T& value)
//OutIt fill_n(OutIt first, Size count, const T& value)
//void generate(FwIt first, FwIt last, Generator gen)
//OutIt generate_n(OutIt first, Size count, Generator gen)
//void iota(FwIt first, FwIt last, T value)

//Алгоритмы удаления и замены
//---------------------------
//FwIt remove(FwIt first, FwIt last, const T& value)
//FwIt remove_if(FwIt first, FwIt last, UnaPred predicate)
//FwIt unique(FwIt first, FwIt last[, BinPred predicate])
//void replace(FwIt first, FwIt last, const T& oldVal, const T& newVal)
//void replace_if(FwIt first, FwIt last, UnaPred predicate, const T& newVal)

//Алгоритмы обращения и сдвига
//----------------------------
//void reverse(BidIt first, BidIt last)
//FwIt rotate(FwIt first, FwIt middle, FwIt last)
//OutIt reverse_copy(BidIt first, BidIt last, OutIt target)
//OutIt rotate_copy(FwIt first, FwIt middle, FwIt last, OutIt target)

//Алгоритмы сортировки
//--------------------


//Арифметические алгоритмы
//------------------------
//T accumulate(InIt first, InIt last, T startValue[, BinOp op])
//T inner_product(InIt1 first1, InIt1 last1, InIt2 first2, T startValue[, BinOp1 op1, BinOp2 op2])
//OutIt partial_sum(InIt first, InIt last, OutIt target[, BinOp op])
//OutIt adjacent_difference(InIt first, InIt last, OutIt target[, BinOp op])






//Алгоритмы STL, или более точно, обобщенные алгоритмы STL - это шаблонные функции,
//которые позволяют обобщить ряд операций, выполняемых над элементами контейнера,
//таким образом, чтобы реализация алгоритма не зависела от типа контейнера.
//Всё, что нужно алгоритму STL - это два итератора (на начало и конец обрабатываемого диапазона),
//плюс функция, которая будет выполняться над элементами контейнера. Таким образом,
//один и тот же алгоритм STL можно применить к контейнерам различных типов, если
//эти контейнеры поддерживают необходимые итераторы.

//Если контейнер предоставляет доступ к произвольному элементу, или обход элементов по индексу,
//или изменение отдельных элементов, то вы можете и не использовать алгоритмы STL,
//ограничиваясь простыми циклами. Однако алгоритмы STL позволяют записать тот же код
//короче и понятнее.

void forVsAlgorithm()
{
    std::vector<int> v {1,2,3,4,5};
    //удвоение элементов при помощи цикла
    std::vector<int> v1 = v;
    for (unsigned int i = 0; i<v1.size(); i++) {
        v1[i] *= 2;
    }
    //удвоение элементов при помощи алгоритма
    std::vector<int> v2 = v;
    //алгоритм transform применяет лямбда-функцию к каждому элементу контейнера, меняя элементы.
    std::transform(v2.begin(), v2.end(), v2.begin(), [](auto &n){ return n*2; });
    //или при помощи заранее объявленной функции
    //std::transform(v2.begin(), v2.end(), v2.begin(), makeDouble);
    //где makeDouble может быть объявлена например так:
    //void makeDouble(int &n) {n*=2;}
}

//Каждый алгоритм принимает аргументом либо какое-либо значение, либо функцию, которая будет
//применяться к элементам контейнера. Классический подход к использованию алгоритмов -
//объявить где-нибудь выше все необходимые вспомогательные функции. Это приводит
//к разбуханию кода программы и к появлению множества лишних сущностей. Поэтому C++11
//добавил поддержку т.н. лямбда-функций, которые не имеют имени и определяются прямо
//в месте их использования.
//(См. lambda_functions.h)



//Входные и выходные итераторы
//----------------------------

//В файле stl_iterators были описаны три типа итераторов, которые поддерживаются
//библиотекой STL - прямой, двунаправленный и произвольного доступа.
//Для использования алгоритмов библиотека STL определяет еще два типа итераторов -
//входной (input) и выходной (output) итераторы.

//Входной итератор используется для чтения элементов контейнера. Он должен поддерживать
//оператор разыменования для доступа к содержимому элемента, а также операторы ++, == и !=

//Выходной итератор используется для чтения элементов контейнера и записи элементов в
//контейнер. К нему требования менее строгие - он должен поддерживать разыменование и ++.

//Все итераторы стандартных контейнеров STL уже являются входными итераторами, то есть
//предоставляют доступ к элементам для чтения. Кроме того, все неконстантные итераторы
//являются выходными итераторами. Кроме того, STL добавляет ряд выходных итераторов,
//называемых адаптерами.

//Назначение выходных итераторов будет разобрано в секции алгоритмов, которые копируют
//данные в контейнеры.

//Терминология
//------------

//• Function : вызываемая функция, то есть лямбда-функция, функциональный объект
//  или указатель на функцию.
//• InIt, OutIt, FwIt, BidIt, RanIt : итераторы: входной, выходной, прямой, двунаправленный,
//  произвольного доступа.
//• UnaOp, BinOp : унарная или бинарная операция, то есть Function, принимающая один
//  или два аргумента.
//• UnaPred, BinPred : унарный или бинарный предикат, то есть унарная или бинарная операция,
//  возвращающая bool.
//• Size : количество элементов в контейнере.
//• DiffType : тип, представляющий расстояние между итераторами.
//• T : тип элемента в контейнере.
//• Compare : Функциональный объект, используемый для сравнения элементов. Если он не задан,
//  используется оператор <. Compare должен принимать два аргумента и возвращать true,
//  если первый аргумент меньше (в любом смысле) второго аргумента.

//Алгоритмы, применяющие функцию к диапазону элементов
//----------------------------------------------------

// Function std::for_each(InIt first, InIt last, Function function)
// применяет function к каждому элементу в диапазоне [first, last).
// Обычно используется в тех случаях, где не требуется менять элементы контейнера.
// При этом Function должна иметь сигнатуру void function(const T& elem);
// а итераторы first, last лучше использовать константные.
// for_each возвращает указатель на функцию или функциональный объект, который был
// передан третьим аргументом. Это иногда требуется, если переданный в for_each объект
// сохраняет состояние о последнем произведенном вызове оператора ().

// OutIt transform(InIt first1, InIt last1, OutIt target, UnaOp operation)
// OutIt transform(InIt1 first1, InIt1 last1, InIt2 first2, OutIt target, BinOp operation)
// Первая версия применяет operation к каждому элементу в диапазоне [first1, last1)
// и записывает результат в target. target может совпадать с first1.
// Вторая версия применяет бинарную операцию operation к каждому элементу в диапазоне
// [first1, last1), вторым аргументом операции выступает first2. Затем результат
// записывается в target. При передвижении итератора от first1 к last1 также движется итератор
// от first2 к first2+(last1-first1)
// transform возвращает выходной итератор, указывающий на элемент, следующий за последним измененным.

// Алгоритм transform не гарантирует последовательный обход элементов из диапазона
// [first1, last1). Если важно обойти все элементы по очереди, то следует использовать
// for_each.

void forEachAlgorithm()
{
    std::vector<int> vec{ 1,2,3,4,5,6 };
    //выводим в консоль
    std::for_each(vec.cbegin(), vec.cend(),
        [](auto& n) { std::cout << n << " "; });
    // 1 2 3 4 5 6

    //функцию вывода в консоль можно определить явно:
    //void print(const int &element) {
    //    std::cout << element << " ";
    //}
    //но тогда мы лишаемся обобщенности типа элемента.
    //Функцию print можно объявить обобщенной:
//    template<typename T>
//    void print(const T &element) {
//        std::cout << element << " ";
//    }
    //Функцию вывода в консоль можно объявить в виде лямбда-выражения:
    auto print = [](const auto& n) { std::cout << " " << n; };
    //Такое выражение можно объявлять в любом месте программы, даже внутри блока кода.


    //Алгоритм for_each можно также использовать для изменения элементов диапазона, если сигнатура
    //функции принимает аргумент по неконстантной ссылке. При этом входные итераторы
    //first, last не должны быть константными.

    //добавим 20 к каждому элементу вектора
    std::for_each(vec.begin(), vec.end(), [](auto &n){ n += 20;});
    std::for_each(vec.cbegin(), vec.cend(), print); //21 22 23 24 25 26
    std::cout << std::endl;
}

//Если в качестве function передать функциональный объект, то можно хранить дополнительную
//информацию о ходе работы алгоритма.

struct Sum
{//функциональный объект, то есть класс, который переопределяет operator()
    void operator()(int n) { sum += n; }
    int sum = 0;
};

void forEachAlgorithm1()
{
    std::vector<int> nums {3, 4, 2, 8, 15, 267};
    //поскольку for_each возвращает указатель на применяемую функцию, мы можем
    //получить результат:
    Sum s = std::for_each(nums.cbegin(), nums.cend(), Sum());
    std::cout << "sum: " << s.sum << '\n';
}

void transformAlgorithm()
{
    std::vector<int> vec{ 1,2,3,4,5,6 };
    //удваиваем элементы вектора
    std::transform(vec.cbegin(), vec.cend(), vec.begin(),
        [](auto& element) { return element * 2; });
    //умножаем на -1
    std::transform(vec.cbegin(), vec.cend(), vec.begin(), std::negate<>());
    //std::negate<> - это функциональный объект, который определен в заголовочном файле <functional>
    //и умножает переданное ему число на -1.

    auto print = [](const auto& n) { std::cout << " " << n; };

    //выводим в консоль
    std::for_each(vec.cbegin(), vec.cend(), print);
    std::cout << std::endl;
    // -2 -4 -6 -8 -10 -12


    std::string s("hello");
    //преобразуем строку в верхний регистр
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) -> unsigned char { return std::toupper(c); });
    //В лямбда-выражении выше мы после стрелки явно указали, значение какого типа
    //должно быть возвращено (->unsigned char). Если мы это не сделаем, то тип возвращаемого значения
    //будет int, так как именно такой тип возвращает функция std::toupper().

    //для каждого символа строки получаем его код и сохраняем в новом векторе
    std::vector<std::size_t> ordinals;
    std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
                   [](unsigned char c) -> std::size_t { return c; });
    //выводим в консоль
    std::for_each(ordinals.cbegin(), ordinals.cend(), print);
    std::cout << std::endl;
    // 72 69 76 76 79

    //std::back_inserter - это функция, возвращающая т.н. адаптер итератора. Адаптеры
    //итераторов позволяют расширить возможности стандартных итераторов.
    //std::back_inserter возвращает объект типа std::back_insert_iterator, который
    //способен вставлять результат работы алгоритма в контейнер, переданный ему в виде аргумента,
    //используя метод контейнера push_back().
    //Мы могли избежать использования std::back_inserter, заранее создав вектор ordinals
    //нужного размера и передав в std::transform третьим аргументом ordinals.begin()

    //Пример использования бинарной функции с алгоритмом transform:
    //получим попарные суммы элементов контейнера и поместим результат в другой контейнер

    std::vector<int> v{ 1,2,3,4,5,6 };
    std::vector<int> sums;
    std::transform(v.begin(), v.end()-1, v.begin()+1, std::back_inserter(sums), std::plus<>{});
    //std::plus<>{} - это функциональный объект, определенный в заголовочном файле <functional>
    //и возвращающий сумму элементов, то есть являющийся бинарной функцией.
    //выводим в консоль
    std::for_each(sums.cbegin(), sums.cend(),print);
    std::cout << std::endl;
    //3 5 7 9 11
}

//Алгоритмы проверки элементов в контейнере
//---------------------------------------

//bool all_of(InIt first, InIt last, UnaPred predicate)
//bool none_of(InIt first, InIt last, UnaPred predicate)
//bool any_of(InIt first, InIt last, UnaPred predicate)
//     Возвращают true, если все, ни один или хотя бы один элемент в диапазоне [first, last)
//     удовлетворяет унарному предикату. Если диапазон пуст, all_of() и none_of()
//     возвращают true, any_of() возвращает false.

//DiffType count(InIt first, InIt last, const T& value)
//DiffType count_if(InIt first, InIt last, UnaPred predicate)
//     Возвращает количество элементов из диапазона [first, last), которые равны данному value,
//     или удовлетворяют унарному предикату.

void useAllNoneAny()
{
    //унарный предикат, возвращающий true, если число четное
    auto even = [](const auto &elem) { return elem % 2 == 0;};

    std::vector<int> v {1,2,3,4,5,6};
    std::cout << std::all_of(v.cbegin(), v.cend(), even) << std::endl; //false
    std::cout << std::any_of(v.cbegin(), v.cend(), even) << std::endl; //true
    std::cout << std::none_of(v.cbegin(), v.cend(), even) << std::endl; //false

    //функциональный объект, возвращающий true, если число делится на n
    struct DivisibleBy
    {
        const int d;
        DivisibleBy(int d) : d(d) {}
        bool operator()(int n) const { return n % d == 0; }
    };

    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(3))) {
        std::cout << "At least one number is divisible by 3\n";
    }
    std::cout << "Exactly " << std::count_if(v.cbegin(), v.cend(), DivisibleBy(3)) <<
                 " numbers are divisible by 3\n";
}

//Алгоритмы поиска элементов в контейнере
//---------------------------------------

//InIt find(InIt first, InIt last, const T& value)
//InIt find_if(InIt first, InIt last, UnaPred predicate)
//InIt find_if_not(InIt first, InIt last, UnaPred predicate)
//    Ищет в диапазоне [first, last) первый элемент, который равен value, удовлетворяет
//    унарному predicate, или не удовлетворяет predicate. Возвращает итератор на найденный
//    элемент, или  last  если элемент не найден.

//InIt find_first_of(InIt first1, InIt last1, FwIt first2, FwIt last2[, BinPred predicate])
//    Ищет в диапазоне [first1, last1) первый элемент, который содержится в
//    диапазоне [first2, last2). Возвращает last1 если элемент не найден или [first2, last2) пуст.
//    Если задан бинарный предикат, он используется для определения равенства элементов.
//FwIt adjacent_find(FwIt first, FwIt last[, BinPred predicate])
//    Возвращает итератор на первый элемент первой пары смежных элементов
//    в диапазоне [first, last), которые равны друг другу или удовлетворяют бинарному предикату.
//    Возвращает last, если подходящий элемент не найден.

void useFind()
{
    //Простой поиск элемента в контейнере
    int n1 = 3;
    int n2 = 5;

    std::vector<int> v{0, 1, 2, 3, 4};

    auto result1 = std::find(std::begin(v), std::end(v), n1);
    auto result2 = std::find(std::begin(v), std::end(v), n2);

    if (result1 != v.end()) {
        std::cout << "v contains: " << n1 << '\n';
    } else {
        std::cout << "v does not contain: " << n1 << '\n';
    }

    if (result2 != v.end())
        std::cout << "v contains: " << n2 << '\n';
    else
        std::cout << "v does not contain: " << n2 << '\n';

    //Поиск с предикатом
    std::vector<int> v1{0, 1, -2, 3, 4};

    auto result = std::find_if(std::begin(v), std::end(v), [](const auto &n){return n<0;});
    if (result != v1.end()) {
        std::cout << "The first negative element has index "<< std::distance(result, v1.begin()) << "\n";
    }
    else {
        std::cout << "v1 does not contain negative numbers\n";
    }

    //Поиск любого символа
    std::string s = "This isn't a phrase!";
    std::string delimiters = " .!?,";
    auto res = std::find_first_of(s.cbegin(), s.cend(), delimiters.cbegin(), delimiters.cend());
    if (res != s.cend()) {
        std::cout << "The first delimiter of s is ["<< (*res) <<"]\n";
    }
    else
        std::cout << "s has no delimiters from "<< delimiters << '\n';

    //Поиск смежных значений
    //Найдем первую пару чисел в векторе, которые отличаются по модулю не более чем на 2
    std::vector<int> vec {0,3,2,4,5,8};
    auto first = std::adjacent_find(std::begin(vec), std::end(vec),
                                    [](int n1, int n2){return std::abs(n1-n2)<=2;});
    if (first != vec.end()) {
        std::cout << "The first element in pair |n1-n2|<=2 is " << (*first) << "\n";
    }

    //Проверка контейнера на отсортированность по возрастанию
    auto i2 = std::adjacent_find(vec.begin(), vec.end(), std::greater<int>());
    if (i2 == v1.end()) {
        std::cout << "The entire vector is sorted in ascending order\n";
    } else {
        std::cout << "The last element in the non-decreasing subsequence is at: "
                  << std::distance(vec.begin(), i2) << '\n';
    }
}

// Алгоритмы бинарного поиска
//---------------------------

//Если контейнер содержит уже отсортированные элементы, то для ускорения поиска элементов
//можно использовать рекурсивные алгоритмы бинарного поиска. Если контейнер
//не отсортирован, то поведение следующих алгоритмов не определено.

// bool binary_search(FwIt first, FwIt last, const T& value[, Compare comp])
//      Возвращает true, если в диапазоне [first, last) есть элемент, равный value.

// FwIt lower_bound(FwIt first, FwIt last, const T& value[, Compare comp])
// FwIt upper_bound(FwIt first, FwIt last, const T& value[, Compare comp])
//      Возвращает итератор на первый элемент в диапазоне [first, last), который
//      не меньше чем value (lower_bound()) или больше чем value (upper_bound()).
//      Оба возвращенных итератора можно использовать для вставки value в контейнер,
//      (например, методом insert()).

// pair<FwIt, FwIt> equal_range(FwIt first, FwIt last, const T& value[, Compare comp])
//    Возвращает пару итераторов для нижней и верхней границ.

void useBinarySearch()
{
    //вставка элементов в отсортированный вектор
    std::vector<int> vec {11,22,33};
    auto it = std::lower_bound(vec.begin(), vec.end(), 18);
    vec.insert(it, 18); //11,18,22,33

    //удаление повторяющихся элементов из отсортированного массива
    std::vector<int> v {1,2,3,3,4,5};
    auto result = std::equal_range(v.begin(), v.end(), 3);
    v.erase(result.first, result.second);
}

//Алгоритмы поиска подпоследовательностей
//---------------------------------------

//Поиск подпоследовательности - это задача нахождения индекса (итератора), с которого
//в контейнере начинается определенная последовательность элементов.

//FwIt1 search(FwIt1 first1, FwIt1 last1, FwIt2 first2, FwIt2 last2[, BinPred predicate])
//FwIt1 find_end(FwIt1 first1, FwIt1 last1, FwIt2 first2, FwIt2 last2[, BinPred predicate])
//    Возвращает итератор на начало первой / последней подпоследовательности, равной
//    диапазону [first2, last2). Возвращает first1 / last1, если диапазон [first2, last2)
//    пуст, или last1, если диапазон [first2, last2) не найден.

//FwIt search_n(FwIt first, FwIt last, Size count, const T& value[, BinPred predicate])
//    Возвращает итератор на первую подпоследовательность, состоящую из элементов value,
//    длиной count. Возвращает first, если count = 0, или last, если подпоследовательность не
//    найдена.

//возвращает true, если строка s содержится в контейнере cont
template <typename Container>
bool in_quote(const Container& cont, const std::string& s)
{
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}

void useSearch()
{
    std::string str = "why waste time learning, when ignorance is instantaneous?";

    std::cout << in_quote(str, "learning") << '\n'
              << in_quote(str, "lemming")  << '\n';
    //Замечание: для строк проще использовать метод str.find()

    //То же самое, но для вектора
    std::string s = "time";
    std::vector<char> vec(str.begin(), str.end());
    auto it = std::search(vec.begin(), vec.end(), s.begin(), s.end());
    if (it != vec.end()) {
        std::cout << "time found at index " << it-vec.begin() << std::endl;
    }
    else {
        std::cout << "time not found\n";
    }

    //Поиск повторяющихся пробелов в строке
    std::string in = "Lorem ipsum dolor sit  amet, consectetur adipiscing elit,"
                     " sed  do eiusmod tempor incididunt ut    labore  et dolore magna aliqua";
    auto res = std::search_n(in.begin(), in.end(), 2, ' ');
    if (res != in.end()) {
        const auto pos = res-in.begin();
        std::cout << in.substr(pos - 3, pos + 5) << std::endl; // "sit  ame";
    }
}


//Алгоритмы поиска минимума и максимума
//-------------------------------------

//const T& min(const T& a, const T& b[, Compare comp])
//const T& max(const T& a, const T& b[, Compare comp])
//    Возвращают ссылку на минимальное или максимальное из двух значений, или ссылку на
//    first, если они равны.

//T min(initializer_list<T> t[, Compare comp])
//T max(initializer_list<T> t[, Compare comp])
//    Возвращают копию минимального или максимального значения из данного списка,
//    или копию первого элемента, если все элементы списка равны.

//pair<const T&, const T&> minmax(const T& a, const T& b[, Compare comp])
//    Возвращает пару, состоящую из ссылок на минимальное и максимальное из двух значений,
//    в таком порядке. Если оба значения равны, возвращается пара pair(a, b).

//pair<T, T> minmax(initializer_list<T> t[, Compare comp])
//    Возвращает пару, состоящую из копий минимального и максимального значений
//    в списке t. Если несколько элементов равны минимальному, возвращается копия самого левого.
//    Если несколько элементов равны максимальному, возвращается копия самого правого.

//FwIt min_element(FwIt first, FwIt last[, Compare comp])
//FwIt max_element(FwIt first, FwIt last[, Compare comp])
//pair<FwIt, FwIt> minmax_element(FwIt first, FwIt last[, Compare comp])
//    Возвращают итератор, указывающий на первый минимальный или максимальный элемент,
//    или пару итераторов, указывающих на первый минимальный и последний максимальный
//    элементы в диапазоне [first, last).
//    Возвращают last или пару pair(first, first), если диапазон [first, last) пуст.

void useMinMax()
{
    std::cout << "smaller of 1 and 9999 is " << std::min(1, 9999) << '\n'
              << "smaller of 'a', and 'b' is '" << std::min('a', 'b') << "\n"
              << "shortest of \"foo\", \"bar\", and \"hello\" is \""
              << std::min({ "foo", "bar", "hello" },
                          [](const std::string_view s1, const std::string_view s2) {
        return s1.size() < s2.size();
    }) << "\n";

//    smaller of 1 and 9999 is 1
//    smaller of 'a', and 'b' is 'a'
//    shortest of "foo", "bar", and "hello" is "foo"

    std::vector<int> v{3, 1, 4, 1, 5, 9};
    std::vector<int>::iterator result = std::min_element(v.begin(), v.end());
    std::cout << "min element at: " << std::distance(v.begin(), result);

    auto it = std::minmax_element(v.begin(), v.end());
    std::cout << "min = " << *it.first << ", max = " << *it.second << '\n';
}

//Алгоритмы сравнения последовательностей
//---------------------------------------

//bool equal(InIt1 first1, InIt1 last1, InIt2 first2[, BinPred predicate])
//    Пусть n = last1 - first1, тогда equal возвращает true, если все элементы
//    в диапазонах [first1, last1) и [first2, first2 + n) попарно равны. Второй диапазон
//    должен иметь не меньше n элементов.

//pair<InIt1, InIt2> mismatch(InIt1 first1, InIt1 last1, InIt2 first2[, BinPred predicate])
//    Пусть n = (last1 - first1), возвращает пару итераторов, указывающих на первые элементы
//    в диапазонах [first1, last1) и [first2, first2 + n), которые не равны попарно. Второй
//    диапазон должен иметь не меньше n элементов.

//bool equal(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2[, BinPred predicate])
//pair<InIt1, InIt2> mismatch(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2[, BinPred predicate])
//    Более безопасные версии предыдущих алгоритмов, в которых задается конец второго диапазона.

bool is_palindrome(const std::string& s)
{
    return std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
}

std::string mirror_ends(const std::string& in)
{
    return std::string(in.begin(),
                       std::mismatch(in.begin(), in.end(), in.rbegin()).first);
}

void useEqual()
{
    //Определяет, является ли строка палиндромом
    std::string s = "radar";
    std::cout << "\"" << s << "\" "
              << (is_palindrome(s) ? "is" : "is not")
              << " a palindrome\n";

    //Ищет самую длинную подстроку, с которой начинается и которой заканчивается данная строка
    std::cout << mirror_ends("abXYZba") << '\n'
              << mirror_ends("abca") << '\n'
              << mirror_ends("aba") << '\n';
//    ab
//    a
//    aba
}

//Алгоритмы копирования и перемещения
//-----------------------------------

//OutIt copy(InIt first, InIt last, OutIt targetFirst)
//OutIt copy_if(InIt first, InIt last, OutIt targetFirst, UnaPred predicate)
//    Копирует либо все элементы (copy), либо только те элементы, которые удовлетворяют
//    унарному предикату (copy_if), из диапазона [first, last) в диапазон, начинающийся
//    с targetFirst. Диапазоны не должны пересекаться. Целевой диапазон должен быть
//    достаточного размера, чтобы вместить копируемые элементы. Возвращает итератор на
//    целевой диапазон.

void useCopy()
{
    std::vector<int> source {1,4,-6,5,80,2,8,8};
    //Скопируем этот вектор в другой, используя copy
    std::vector<int> dest(10); //создали вектор из 10 элементов
    std::copy(source.begin(), source.end(), dest.begin()); //скопировали элементы.
    //В векторе dest 10 элементов, но только первые 8 взяты из source

    //Скопируем вектор source в другой, используя back_inserter
    std::vector<int> dest1; //пустой
    std::copy(source.begin(), source.end(), std::back_inserter(dest1));
    //Теперь в векторе dest1 ровно 8 элементов
    //То же самое можно сделать проще: dest1 = source;

    //Копируем только нечетные элементы из исходного вектора в целевой
    std::vector<int> odds;
    std::copy_if(source.begin(), source.end(), std::back_inserter(dest1),
                 [](int n){return n%2 !=0;});
    //odds = {1,5}
}

//BidIt2 copy_backward(BidIt1 first, BidIt1 last, BidIt2 targetLast)
//    Копирует все элементы диапазона [first, last) в диапазон, заканчивающийся targetLast.
//    targetLast не должен находиться в диапазоне [first, last) .
//    Целевой диапазон должен быть достаточного размера. Копирование производится
//    в обратном порядке (от (last-1), копируемого в (targetLast-1), до first.
//    Возвращает итератор на начало целевого диапазона.

//OutIt copy_n(InIt start, Size count, OutIt target)
//    Копирует count элементов, начиная с элемента start, в диапазон, начинающийся с target.
//    Целевой диапазон должен быть достаточного размера. Возвращает итератор на конец
//    целевого диапазона.

//OutIt move(InIt first, InIt last, OutIt targetFirst)
//BidIt2 move_backward(BidIt1 first, BidIt1 last, BidIt2 targetLast)
//    Похожи на copy() и copy_backward(), но перемещают элементы вместо копирования.

//FwIt2 swap_ranges(FwIt1 first1, FwIt1 last1, FwIt2 first2)
//    Обменивает элементы из диапазона [first1, last1) с элементами в диапазоне
//    [first2, first2 + (last1 - first1)).
//    Диапазоны не должны пересекаться, второй диапазон не должен быть меньше первого.
//    Возвращает итератор, указывающий за последним элементом во втором диапазоне.

#include <numeric>

void useCopy1()
{
    std::string in = "1234567890";
    std::string out;

    //копируем первые 4 символа
    std::copy_n(in.begin(), 4, std::back_inserter(out));
    std::cout << out << '\n';
    //то же самое, но методами std::string:
    out = in.substr(0,4);

    //вектор из 128 элементов
    std::vector<int> v_in(128);
    //заполняем вектор числами по возрастанию
    std::iota(v_in.begin(), v_in.end(), 1); //определена в <numeric>

    std::vector<int> v_out(v_in.size());
    //копируем первые 100 элементов
    std::copy_n(v_in.cbegin(), 100, v_out.begin());
    //суммируем первые 100 элементов
    std::cout << std::accumulate(v_out.begin(), v_out.end(), 0) << '\n'; //определена в <numeric>

    //заполняем вектор первыми 10 целыми числами (лучше использовать std::iota)
    std::vector<int> from_vector;
    for (int i = 0; i < 10; i++) {
        from_vector.push_back(i);
    }

    //copy_backward
    std::vector<int> to_vector(15);

    std::copy_backward(from_vector.begin(), from_vector.end(), to_vector.end());

    std::cout << "to_vector contains: ";
    for (auto i: to_vector) {
        std::cout << i << " ";
    }
    //to_vector contains: 0 0 0 0 0 0 1 2 3 4 5 6 7 8 9
}

// Генерирующие алгоритмы
//-----------------------

//void fill(FwIt first, FwIt last, const T& value)
//OutIt fill_n(OutIt first, Size count, const T& value)
//    Присваивает value всем элементам в диапазоне [first, last) или [first, first+count).
//    fill_n()  возвращает итератор, указывающий на (first + count), или на first, если
//    count < 0.

//void generate(FwIt first, FwIt last, Generator gen)
//OutIt generate_n(OutIt first, Size count, Generator gen)
//    Аналогичен fill() и fill_n(), но использует функцию-генератор.
//    Генератор gen - это функция без аргументов, возвращающая значение.

//void iota(FwIt first, FwIt last, T value)
//    Этот алгоритм определен в заголовочном файле <numeric>.
//    Записывает в диапазон [first, last) последовательно увеличивающиеся значения:
//    *first = value++
//    *(first + 1) = value++
//    *(first + 2) = value++

void useGenerating()
{
    std::vector<int> vec(6);
    int val = 11;
    std::generate(vec.begin(), vec.begin()+3,
                  [&val](){val *= 2; return val;}); // 22 44 88 0 0 0
    std::iota(vec.begin()+3, vec.end(), 1); // 22 44 88 1 2 3

    //Если требуется заполнить одинаковыми значениями весь вектор, то иногда проще использовать
    //конструктор вектора:
    std::vector<int> v(7, 5); //5 5 5 5 5 5 5
}

//Алгоритмы удаления и замены
//---------------------------

//FwIt remove(FwIt first, FwIt last, const T& value)  
//FwIt remove_if(FwIt first, FwIt last, UnaPred predicate)  
//     Сдвигают все элементы из диапазона [first, last), которые не равны 
//     value или не удовлетворяют унарному предикату predicate, к началу диапазона, 
//     после чего [first, result) содержит все элементы, которые были сохранены. 
//     Возвращают итератор result, указывающий на элемент, следующий за последним сохраненным. 
//     Эти алгоритмы стабильны, то есть сохраняют относительный порядок элементов. 
//     Элементы в диапазоне [result, last) использовать нельзя, так как они могут оказаться
//     в неопределенном состоянии. Обычно они удаляются вызовом алгоритмы erase().
//     Эта идиома называется remove-erase.

//Замечание: хотя алгоритм называется remove, на самом деле он не удаляет элементы из контейнера,
//а только перемещает их в одно место. Предположим, нам необходимо удалить из вектора
//v = {1,2,3,4,5,6,7,8} все нечетные числа. После работы алгоритма remove вектор v примет вид
//v = {2,4,6,8,x,x,x,x}. Элементы начиная с 4-го (удаляемые) оказались в конце вектора, а оставшиеся 
//сгруппированы в начале. 

//FwIt unique(FwIt first, FwIt last[, BinPred predicate])  
//      Удаляет (подобно remove) все неуникальные последовательные элементы из диапазона [first, last). Можно 
//      использовать бинарный предикат, определяющий равенство элементов.
    
//void replace(FwIt first, FwIt last, const T& oldVal, const T& newVal)  
//void replace_if(FwIt first, FwIt last, UnaPred predicate, const T& newVal)  
//      Заменяет все элементы в диапазоне [first, last), равные oldVal или удовлетворяющие унарному 
//      предикату, на newVal. 

void useUnique()
{
    std::vector<int> v {3,4,4,4,5,6,4,5,5,7};
    auto result = std::unique(v.begin(), v.end()); 
    v.erase(result, v.end()); // v = 3,4,5,6,4,5,7

    //Чтобы удалить вообще все повторяющиеся элементы, можно сначала отсортировать вектор.
}

void useRemove()
{
    //Удаление пробелов из строки
    std::string str1 = "Text with some   spaces";
    str1.erase(std::remove(str1.begin(), str1.end(), ' '),
               str1.end());
    std::cout << str1 << '\n';
 
    //Удаление пробелов из строки, используя предикат
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(), 
                              str2.end(),
                              [](unsigned char x){return std::isspace(x);}),
               str2.end());
    std::cout << str2 << '\n';
}



//Алгоритмы обращения и сдвига
//----------------------------
//void reverse(BidIt first, BidIt last)
//    Меняет порядок следования элементов из диапазона [first, last)
//    на обратный

//FwIt rotate(FwIt first, FwIt middle, FwIt last)
//    Сдвигает элементы из диапазона [first, last) влево таким образом, что
//    элемент middle становится первым элементом в диапазоне, а элемент (middle - 1)
//    становится последним элементом. Возвращает указатель на (first + (last - middle)) .
//    Для сдвига вправо можно использовать обратные итераторы

//OutIt reverse_copy(BidIt first, BidIt last, OutIt target)
//OutIt rotate_copy(FwIt first, FwIt middle, FwIt last, OutIt target)
//    То же, что reverse() и rotate(), но копируют результат и записывают в target.
//    Диапазон target должен быть достаточно большим, чтобы вместить копируемые элементы.
//    Диапазоны [first, last) и target не должны пересекаться. Возвращает конечный итератор
//    диапазона target.

//Примеры
void useReverse()
{
    //обращение вектора, с изменением этого вектора
    std::vector<int> v{1,2,3};
    std::reverse(std::begin(v), std::end(v));
    for(auto e : v) std::cout << e;
    std::cout << '\n'; // 321

    //обращение вектора с копированием результата в другой вектор
    std::vector<int> v1(3); //пустой вектор из 3 элементов
    std::reverse_copy(v.begin(),v.end(),v1.begin()); // v1 = {1,2,3}

    //обращение вектора, но вывод результата сразу в консоль
    std::reverse_copy(std::begin(v),std::end(v), std::ostream_iterator<int>(std::cout," "));
    // 3 2 1
}

void useRotate()
{
    std::vector<int> v {1,2,3,4,5};
    //сдвиг влево
    std::rotate(v.begin(),v.begin()+1,v.end()); //2,3,4,5,1
    //сдвиг вправо
    std::rotate(v.rbegin(),v.rbegin()+2,v.rend()); //5,1,2,3,4

    //Сортировка вставкой с использованием rotate:
    std::vector<int> vec{2, 4, 2, 0, 5, 10, 7, 3, 7, 1};
    // insertion sort
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        std::rotate(std::upper_bound(vec.begin(), i, *i), i, i+1);
    }
}

//Алгоритмы сортировки
//--------------------



//Арифметические алгоритмы
//------------------------
//#include <numeric>

//T accumulate(InIt first, InIt last, T startValue[, BinOp op])
//    Возвращает результат типа T, который представляет собой последовательное применение
//    формулы result += element или result = op(result, element), начиная со startValue,
//    для каждого элемента из диапазона [first, last) .

//T inner_product(InIt1 first1, InIt1 last1, InIt2 first2, T startValue[, BinOp1 op1, BinOp2 op2])
//    Возвращает результат типа T, который представляет собой последовательное применение
//    формулы result += (el1 * el2) или result = op1(result, op2(el1, el2)), начиная
//    со startValue, для каждого el1 из [first1, last1) и каждого el2 из
//    [first2, first2 + (last1 - first1)) по порядку. Второй диапазон должен быть не меньше первого.
//    Функция op1 используется для "суммирования" результата
//    Функция op2 используется для "умножения" el1 и el2

//OutIt partial_sum(InIt first, InIt last, OutIt target[, BinOp op])
//    Рассчитывает частичные суммы увеличивающихся подпоследовательностей элементов
//    из [first, last) и записывает результат в диапазон target.
//    По умолчанию используется оператор +
//     *(target) = *first
//     *(target + 1) = *first + *(first + 1)
//     *(target + 2) = *first + *(first + 1) + *(first + 2)
//    ...
//    Возвращает конечный итератор диапазона target, то есть итератор на (target + (last - first)).
//    Диапазон target должен быть достаточно большим для сохранения результата.
//    Диапазон target может совпадать с входным диапазоном (т.е. targe = first).

//OutIt adjacent_difference(InIt first, InIt last, OutIt target[, BinOp op])
//    Вычисляет разность смежных элементов из диапазона [first, last) и записывает результат
//    в target. По умолчанию используется оператор -
//    *(target) = *first
//    *(target + 1) = *(first + 1) - *first
//    *(target + 2) = *(first + 2) - *(first + 1)
//    ...
//    Возвращает конечный итератор диапазона target, то есть итератор на (target + (last - first)).
//    Диапазон target должен быть достаточно большим для сохранения результата.
//    Диапазон target может совпадать с входным диапазоном (т.е. targe = first).

void useNumeric()
{
    //Использование accumulate для суммирования элементов вектора
    std::vector<int> vec{4,5,3,1,2,6};
    int sum = std::accumulate(vec.begin(), vec.end(), 0); //sum==21

    //расчет скалярного произведения двух векторов:
    double v1[] = {0,1,2};
    double v2[] = {1,0,2};
    double dotProduct = std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 0);
    //dotProduct = 0*1+1*0+2*2 = 4

    //определение количества совпадающих пар элементов в двух векторах
    std::vector<int> a{0, 1, 2, 3, 4};
    std::vector<int> b{5, 4, 2, 3, 1};
    int r = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<>(), std::equal_to<>());
    std::cout << "Number of pairwise matches between a and b: " <<  r << '\n'; // 2

    //расчет частичных сумм
    std::vector<int> v(5, 1); // 1 1 1 1 1
    std::vector<int> partial(5);
    std::partial_sum(v.begin(), v.end(), partial.begin()); //1 2 3 4 5

    //заполнение вектора значениями последовательности Фибоначчи, используя adjacent_difference
    std::array<int, 10> ones {1};
    adjacent_difference(begin(ones), std::prev(end(ones)), std::next(begin(ones)), std::plus<> {});
    copy(begin(ones), end(ones), std::ostream_iterator<int> {std::cout, " "}); //1 1 2 3 5 8 13 21 34 55
}


#endif // STL_ALGORITHMS_H
