#ifndef LISTS_H
#define LISTS_H

#include <utility>

/// В этом файле рассматриваются реализации трех наиболее простых типов данных:
/// список, стек, очередь.


///Список
///------
/*
Список (list) - это набор элементов, упорядоченных по возрастанию индекса
A0, A1, A2...An.
Размер списка равен N. Индекс элемента списка равен i, элемент списка равен a[i].

Реализация с помощью массива
----------------------------

Очевидный первый выбор при реализации списка - использовать массив. Действительно,
массив уже поддерживает идею "списка", так как его элементы расположены в непрерывном
куске оперативной памяти друг за другом, так что доступ по индексу - это просто перемещение
указателя на элемент.
Так как размер массива задается при создании массива, то операции вставки и удаления элементов
потенциально дороги (вычислите сложность операций вставки элемента в позицию i
и удаления элемента по индексу i). Однако доступ к элементу осуществляется за константное время.

Задание: напишите класс ArrayList для работы со списком целых чисел. Реализуйте его с помощью
динамического массива. Добавьте методы
at(i), возвращающий элемент по индексу i,
push_back(x), push_front(x), добавляющие элемент x в конец и в начало списка
pop_back(x), pop_front(x), удаляющие элемент x из конца и из начала списка
insert(x, i), remove(i), вставка элемента x в позицию i, удаление элемента по индексу i
i=find(x) (простой линейный поиск).
Добавьте также методы empty(), clear(), resize(n), size().
По желанию реализуйте класс как шаблонный, с произвольным типом элементов.

Реализация с помощью связного списка
------------------------------------

Эта реализация получает то очевидное преимущество, что теперь элементы списка не обязаны
располагаться в памяти рядом друг с другом. Это позволяет удешевить операции вставки
и удаления элементов.
Связный список состоит из серии узлов, которые необязательно располагаются в памяти рядом.
Каждый узел состоит из элемента и указателя на следующий элемент. Последний узел связного
списка указывает на nullptr.
Для обхода списка мы просто следуем по указателям в узлах, пока не доберемся до конца списка.
То есть доступ по индексу и поиск в связном списке имеют сложность O(N).
Для вставки элемента нам достаточно будет создать новый узел и переназначить указатели (O(1)).
Для удаления элемента - переназначить один указатель (O(1)) и удалить узел.

Исходный список
┌──┐─┐  ┌──┐─┐  ┌──┐─┐  ┌──┐─┐  ┌──┐─┐
│a0│.│->│a1│.│->│a2│.│->│a3│.│->│a4│.│->nullptr
└──┘─┘  └──┘─┘  └──┘─┘  └──┘─┘  └──┘─┘

Вставка элемента:

┌──┐─┐  ┌──┐─┐        ┌──┐─┐  ┌──┐─┐  ┌──┐─┐
│a0│.│->│a1│.│---Х--->│a2│.│->│a3│.│->│a4│.│->nullptr
└──┘─┘  └──┘─┘        └──┘─┘  └──┘─┘  └──┘─┘
            │          ↑
            │ ┌──┐─┐   │
            └>│a │.│───┘
              └──┘─┘
Удаление элемента: (узел a2 удаляется)

┌──┐─┐  ┌──┐─┐  ┌──┐─┐  ┌──┐─┐  ┌──┐─┐
│a0│.│->│a1│.│  │a2│.│  │a3│.│->│a4│.│->nullptr
└──┘─┘  └──┘─┘  └──┘─┘  └──┘─┘  └──┘─┘
            │            ↑
            └────────────┘
Такая реализация связного списка позволяет обходить элементы списка в одном направлении.
Если требуется обходить список с конца, то в узел следует добавить указатель на предыдущий
элемент. Получится двусвязный список.


Код для класса двусвязного списка и его итераторов
--------------------------------------------------
- Назовем класс List.
- Так как список двусвязный, мы будем хранить в классе указатели на начало и конец списка.
- Узел списка будет определен в собственном классе Node.
- Итераторы iterator и const_iterator - тоже отдельные классы, определенные внутри List.
- Чтобы сохранить поведение стандартных итераторов, когда метод end возвращает указатель на
  элемент после последнего (на несуществующий элемент), мы добавим в конец списка узлов
  пустой узел (хвост), который будет работать как ограничитель списка.
- Аналогично добавим в начало списка пустой узел (голову), который будет ограничителем начала списка,
  чтобы нам было удобно перебирать элементы с конца списка.

Таким образом, пустой список на самом деле будет содержать два узла, голову и хвост, между
которыми ничего нет.
*/

template<typename T> //список хранит произвольные объекты класса T
class List
{
private:
    struct Node //объявлен приватным, так как должен быть виден только внутри класса List
    {   //Узел хранит
        T data; //данные
        Node *prev; //указатель на предыдущий узел
        Node *next; //указатель на следующий узел
        //конструкторы узла
        //копирующий конструктор
        Node(const T & d = T(), Node *p = nullptr, Node *n = nullptr)
            : data(d), prev(p), next(n) {}
        //перемещающий конструктор
        Node(T && d, Node *p = nullptr, Node *n = nullptr)
            : data(std::move(d)), prev(p), next(n) {}
    };
public:
    class const_iterator //объявлен публичным, так как должен быть виден везде
    {
    public:
        //конструктор по умолчанию
        const_iterator() : current{nullptr} {}
        //перегрузка оператора разыменования
        const T& operator* () const {//возвращаем константную ссылку, так как это константный итератор
            return retrieve();
        }
        //перегрузка префиксного инкремента
        const_iterator & operator++ () {
            current = current->next; //передвигаем указатель на следующий элемент
            return *this; //и возвращаем ссылку на итератор
        }
        //перегрузка постфиксного инкремента
        const_iterator operator++ (int) {
            const_iterator old = *this; //запоминаем прежнее положение указателя
            ++(*this); //передвигаем указатель на следующий элемент
            return old; //возвращаем прежнее положение указателя
        }
        //перегрузка оператора равно
        bool operator==(const const_iterator &other) const {
            return current == other.current;
        }
        //перегрузка оператора не равно
        bool operator!=(const const_iterator &other) const {
            return !(*this==other);
        }
    protected: //объявляем следующие члены защищенными, чтобы класс iterator имел к ним доступ
        Node *current; //итератор запоминает текущий узел
        T& retrieve() const {//внутренний метод получения данных из итератора
            return current->data;
        }
        //конструктор итератора объявлен защищенным, чтобы никто не мог создать произвольный
        //итератор иначе кроме как через методы begin и end класса List
        const_iterator(Node *p) : current{p} {}
        //добавлен дружественный класс List, чтобы он имел доступ к приватным членам класса const_iterator
        friend class List<T>;
    };
    //Чтобы использовать уже написанные методы, унаследуем класс iterator от класса const_iterator
    class iterator: public const_iterator
    {
    public:
        iterator() {}
        //перегружаем оператор разыменования
        T& operator* () {//возвращаем обычную ссылку, так как это неконстантный итератор
            return const_iterator::retrieve();
        }
        //перегружаем оператор разыменования, чтобы иметь возможность возвращать константную ссылку
        const T& operator* () const {
            return const_iterator::retrieve();
        }
        //перегрузка префиксного инкремента
        iterator & operator++ () {
            this->current = this->current->next;
            return *this;
        }
        //перегрузка постфиксного инкремента
        iterator operator++ (int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
    protected:
        //конструктор итератора объявлен защищенным, чтобы никто не мог создать произвольный
        //итератор иначе кроме как через методы begin и end класса List
        iterator(Node *p) : const_iterator{p} {}
        friend class List<T>;
    };
public:
    List()  //конструктор по умолчанию
    {
        init();
    }
    //копирующий конструктор
    List(const List &other) {
        init();
        for (auto &x: other)
            push_back(x);
    }
    //деструктор
    ~List() {
        clear(); //удаляем все узлы между головой и хвостом
        delete head;//удаляем голову
        delete tail;//удаляем хвост
    }
    //копирующий оператор присваивания
    List & operator=(const List &other) {
        List copy = other;
        std::swap(*this, copy);
        return *this;
    }
    //перемещающий конструктор
    List(List && other) : _size(other._size), head(other.head), tail(other.tail)
    {
        other._size = 0;
        other.head = nullptr;
        other.tail = nullptr;
    }
    //перемещающий оператор присваивания
    List &operator=(List && other) {
        std::swap(_size, other._size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        return *this;
    }

    iterator begin() {
        return {head->next}; //конструируем итератор из узла после головы.
    }
    const_iterator begin() const {
        return {head->next}; //конструируем итератор из узла после головы.
    }
    iterator end() {
        return {tail};
    }
    const_iterator end() const {
        return {tail};
    }

    int size() const {
        return _size;
    }
    bool empty() const {
        return _size==0;
    }

    void clear() {
        while (!empty()) pop_front(); //удаляем узлы из начала по одному
    }
    T & front() {
        return *begin();
    }
    const T & front() const {
        return *begin();
    }
    T & back() {
        return *--end();
    }
    const T & back() const {
        return *--end();
    }
    void push_front(const T &x) {
        insert(begin(), x);
    }
    void push_front(T && x) {
        insert(begin(), std::move(x));
    }
    void push_back(const T &x) {
        insert(end(), x);
    }
    void push_back(T && x) {
        insert(end(), std::move(x));
    }
    void pop_front() {
        erase(begin());
    }
    void pop_back() {
        erase(--end());
    }

    //Вставка узла состоит из двух фаз:
    //1. создание нового узла, предыдущим для него будет предыдущий узел текущего (p->prev),
    //   а следующим - текущий узел (p)
    //2. Переназначение указателей для узлов p и p->prev

//    ->┌────┐─ ─ ─ ->┌────┐->
//      │prev│        │  p │
//    <-└────┘<- ─ ─ -└────┘<-
//       ↑ │           ↑  │
//       │ └->┌────┐───┘  │
//       │    │ x  │      │
//       └────└────┘<-────┘
    iterator insert(iterator it, const T &x) {//вставляем узел перед узлом, на который указывает it
        Node *p = it.current;
        _size++;
        Node *newNode = new Node(x, p->prev, p); //создание узла
        p->prev->next = newNode;
        p->prev = p->prev->next;
        return iterator{p->prev}; //возвращаем новый итератор, указывающий на вставленный узел
    }
    iterator insert(iterator it, T && x) {//вставляем узел перед узлом, на который указывает it
        Node *p = it.current;
        _size++;
        Node *newNode = new Node(std::move(x), p->prev, p);
        p->prev->next = newNode;
        p->prev = p->prev->next;
        return iterator{p->prev}; //возвращаем новый итератор, указывающий на вставленный узел
    }
    //Удаление узла - это просто уничтожение элемента и переназначение указателей
    iterator erase(iterator it) {
        Node *p = it.current;
        iterator retVal{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        _size--;
        return retVal;
    }
    iterator erase(iterator from, iterator to) {
        for (iterator it = from; it!=to;)
            it = erase(it);
        return to;
    }

private:
    int _size;//размер списка
    Node *head;//голова списка
    Node *tail;//хвост списка
    void init() {//создание пустого списка - длина равна 0, голова и хвост указывают друг на друга
        _size = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

//Задание:
//Добавьте в класс Vector поддержку итераторов

/*
Область применения классов Vector и List очень широка. Они могут использоваться там,
где требуется хранить последовательность элементов и иметь возможность перебирать
эти элементы один за другим. Однако классы Vector и List различаются реализацией:

                                         Vector           List
Хранение в памяти                   последовательное     произвольное
Вставка в конец                       O(N)                  O(1)
Вставка в начало                      O(N)                  O(1)
Вставка в середину                    O(N)                  O(1)
Удаление из конца                     O(1)                  O(1)
Удаление из начала                    O(N)                  O(1)
Удаление из середины                  O(N)                  O(1)
Получение произвольного элемента      O(1)                  O(N)
*/

///Стек
///------

/*
Стек (stack) - это список, в котором вставка и удаление элементов возможны только в одном
месте - в конце списка, называемом _вершиной_ стека.

Две основные операции, которые должны иметь все реализации стека - это добавление элемента
в стек (push) и удаление элемента с вершины стека (pop). Кроме того, обычно добавляют еще
метод top, возвращающий элемент на вершине стека. Заметим, что метод pop удаляет
последний добавленный элемент (представьте стопку тарелок).
Операции pop и top на пустом стеке вообще говоря не определены, то есть должны возвращать ошибку.

Стеки часто описывают как контейнеры LIFO (last it, first out).

Реализации стека
----------------

Очевидным выбором будет взять уже имеющийся класс list или vector, так как они уже предоставляют
весь необходимый инструментарий. Далее проще всего объявить производный класс stack, в котором скрыть все
методы, лишние в рамках логики стека (доступ к произвольным элементам, итерацию по элементам и т.д.).

В редких случаях требуется написать собственный класс stack, если анализ производительности
показывает, что имеющиеся реализации недостаточно быстры или экономны. В этом случае можно пойти
двумя путями: реализовать стек с помощью связного списка или с помощью вектора.

Задание 1: написать реализацию стека с помощью двусвязного списка.

Задание 2: написать реализацию стека с помощью  вектора. Класс Stack должен хранить
вектор элементов _data и переменную topOfStack, которая равна индексу верхнего элемента
стека. В пустом стеке topOfStack = -1. При добавлении элемента x в стек topOfStack увеличивается на 1,
и _data[topOfStack] = x. При удалении элемента значение _data[topOfStack] возвращается, а topOfStack
уменьшается на 1.

Применение стеков
-----------------

1. Задача балансировки символов.

При компиляции программ одна пропущенная скобка ) } ] может повлечь серьезные ошибки в программе.
Поэтому компилятору при разборе исходного текста требуется проверить, чтобы для каждой открывающей
скобки имелась своя закрывающая, и они шли в правильном порядке. Например, ([]) - правильная
последовательность, а ([)] , []) , ({]) - неправильные.
Написать программу, проверяющую правильность балансировки скобок, несложно, если использовать стек.
Алгоритм здесь простой:
1. создай пустой стек.
2. читай символы файла один за другим.
 2.1. если символ - открывающая скобка, помести ее в стек.
 2.2. если символ - закрывающая скобка и стек пуст, то сообщи об ошибке. Если стек не пуст,
      то удали символ из стека. Если удаленный символ не соответствует типу закрывающей скобки,
      сообщи об ошибке.
3. если в конце файла стек не пуст, сообщи об ошибке.

Задания:
1. Напишите программу, анализирующую файл сpp на балансировку скобок и выводящую номер строки
   и номер символа в строке, где нарушена балансировка, или сообщение о правильности файла.
2. Оцените сложность алгоритма балансировки.


Замечание: Задача балансировки символов возникает очень часто не только при обработке файлов cpp.
Теги HTML и XML также имеют концепцию "открывающих" и "закрывающих" тегов, нарушение последовательности
которых может привести к неправильному отображению страницы HTML. В качестве дополнительного задания
напишите программу, анализирующую файл html на сбалансированность тегов.
Тег <name> является открывающим, </name> - закрывающим. Между именем тега и скобкой > может содержаться
дополнительный текст - атрибуты тега (<body style="color:red" id="b1">).
Существуют непарные теги, которые записываются так: <br/>. У таких тегов нет закрывающей пары



2. Постфиксный калькулятор

Предположим, нам необходимо посчитать стоимость покупок в магазине. Для этого мы, имея
в своем распоряжении калькулятор, складываем стоимость товаров и умножаем сумму на величину налога в данном штате
   4.99+5.99+6.99*1.06
В зависимости от того, какой калькулятор мы использовали - простой или инженерный - мы получим либо
правильную величину 19.05, либо неправильную 18.39, которая, однако, математически точна.
Разница в расчетах вызвана тем, что умножение - это операция с большим приоритетом, чем сложение,
и инженерные калькуляторы принимают во внимание приоритет операций.
Предположим теперь, что второй товар налогом не облагается, и мы должны вычислить величину
   4.99*1.06 + 5.99 + 6.99*1.06
Инженерный калькулятор на этот раз даст правильный результат, а простой калькулятор - нет,
так как простому калькулятору теперь нужно где-то хранить промежуточные вычисления.
Если мы попытаемся смоделировать эти промежуточные вычисления, мы придем к следующему алгоритму:
- умножить 4.99 на 1.06 и сохранить результат в А1
- сложить А1 и 5.99
- умножить 6.99 на 1.06 и сохранить результат в А2
- сложить А1 и А2
Запишем этот алгоритм в таком виде: 4.99 1.06 * 5.99 + 6.99 1.06 * +
Такая запись называется обратной польской нотацией, или постфиксной нотацией, и рассчитывается в точности
согласно словесному описанию. Самый простой способ реализовать расчет по обратной польской нотации -
использовать стек.

Алгоритм постфиксного калькулятора:
1. Читаем запись слева направо
  1.1. Если встретилось число, помещаем его в стек.
  1.2. Если встретилась операция, извлекаем два элемента из стека и применяем к ним операцию.
       Затем помещаем результат в стек.

Пример: 6 5 2 3 + 8 * + 3 + *
Задание: Запишите работу алгоритма на этом примере. Запишите обычной нотацией вычисляемое выражение.

Дополнительное задание: Напишите функцию, которая для заданной строки возвращает результат вычисления
выражения в обратной польской нотации, записанного в этой строке. Функция должна поддерживать
целые и вещественные числа и арифметические операции + - * /

Дополнительное задание: оцените сложность алгоритма постфиксного калькулятора.



3. Использование стека для преобразования выражения в обратную польскую нотацию.

Предположим, у нас есть строка, которая содержит арифметическое выражение в обычной нотации
(ее часто называют инфиксной): a+b*c+(d*e+f)*g
Стек можно использовать для преобразования ее в обратную польскую нотацию
a b c * + d e * f + g * +
Идея алгоритма состоит в использовании стека в качестве хранилища невыполненных операторов.
Ноо, так как некоторые арифметические операторы имеют больший приоритет, необходимо извлечь их
из стека и переместить в вывод. Поэтому перед помещением оператора в стек мы проверяем,
какой оператор хранится в стеке. Если нам встретились скобки, то воспринимаем их как
оператор с максимальным приоритетом.

1. Создадим пустой стек.
2. Операнд немедленно поместим в вывод.
3. Правая скобка: извлекаем элементы из стека и выводим их в вывод, пока не извлечем левую скобку.
4. Любой другой символ: читаем символы из стека, пока не встретим оператор с меньшим приоритетом.
Одно исключение: не извлекать ( из стека, если обрабатывается не ).
Когда мы добрались до оператора с меньшим приоритетом, помещаем в стек текущий оператор.
5. Если мы достигли конца входа, извлекаем элементы из стека, помещая их в вывод.

Пример: преобразуем выражение a+b*c+(d*e+f)*g в префиксную нотацию.

текущий символ   стек    результат
a                        a
+                +
b                +       a b
*                + *     a b
c                + *     a b c
+                +       a b c * +   //+ имеет меньший приоритет, поэтому выталкиваем * из стека
                                     // также выталкиваем первый +, т.к. он имеет равный приоритет
(                + (     a b c * +
d                + (     a b c * + d
*                + ( *   a b c * + d
e                + ( *   a b c * + d e
+                + ( +   a b c * + d e *
f                + ( +   a b c * + d e * f
)                +       a b c * + d e * f + //выталкиваем всё из стека до открывающей скобки
*                + *     a b c * + d e * f +
g                + *     a b c * + d e * f + g
вход пуст: выталкиваем всё из стека
                         a b c * + d e * f + g * +

Задание: напишите функцию, которая преобразует строку в обычной нотации в обратную польскую нотацию.
Затем напишите функцию, которая для заданной строки возвращает результат вычисления
выражения, записанного в этой строке. Функция должна поддерживать
целые и вещественные числа, арифметические операции + - * / и круглые скобки.

*/

#endif // LISTS_H