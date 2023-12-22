#ifndef BIGFIVE_C11_H
#define BIGFIVE_C11_H

#include <utility> //для std::swap

class IntHolder {

private:

/*
В C++11 при объявлении класса компилятор самостоятельно добавляет пять функций:
деструктор, конструктор копирования, конструктор перемещения, оператор присваивания, оператор перемещения.

1. Деструктор  ~IntHolder();
Добавляется, если нужно корректно уничтожить созданный объект. То есть освободить ресурсы,
закрыть файлы, очистить динамическую память и т.д. Деструктор по умолчанию вызывает
деструкторы для членов данных класса.

2. Конструктор копирования и перемещения
IntHolder(const IntHolder& other);
IntHolder(IntHolder && other);
Вызываются при создании объекта из уже имеющегося объекта того же типа. Конструктор
копирования копирует данные старого объекта в новый, конструктор перемещения перемещает данные
из старого объекта в новый. Конструктор копирования будет вызван, если старый объект -
lvalue, конструктор перемещения - если старый объект rvalue.
Будут вызваны в следующих случаях:
  а) создание переменной
   IntHolder b = other; <- copy construct если other - lvalue, move construct если other - rvalue
   IntHolder c {other};
   IntHolder d {createObj(a,b);} <- move construct если createObj возвращает rvalue.
  б) передача в функцию параметра by-value
   void calc(IntHolder obj);
  в) возвращение из функции by-value
   IntHolder calc();

3. Операторы присваивания (копирующий и перемещающий)
IntHolder& operator= (const IntHolder & other);
IntHolder& operator= (IntHolder && other);
Вызываются при присваивании объектов, созданных ранее. lhs = rhs копирует данные
из rhs в lhs, используя копирующий оператор, если rhs - lvalue, и перемещающий -
если rhs - rvalue.

4. Для простых классов, агрегирующих простые типы данных, переопределять эти пять
функций не требуется.
Однако часто требуется переопределить эти функции, если класс делает что-то
нетривиальное. Правило здесь следующее:
если объявляешь одну из этих функций, то объявляй и остальные четыре. Так как
при объявлении любой из этих пяти функций компилятор перестает генерировать
остальные четыре.

Для чего переопределять: Предположим, в конструкторе класса создается динамический объект:*/
    int *value;
/*1. Конструктор: дефолтного конструктора уже недостаточно, так как память под переменную
value в дефолтном конструкторе выделена не будет. Мы должны сделать это сами:*/
public:
    IntHolder(int defaultValue = 0) {
      //value = new int{defaultValue};
      value = new int;
      *value = defaultValue;
    }
/*2. Теперь нам придется добавить деструктор, так как дефолтный деструктор лишь удалит
указатель, но не очистит выделенную память. Мы должны сделать это вручную:*/
    ~IntHolder() {delete value;}
/*3. Теперь при копировании созданного объекта копирующий конструктор и копирующий
оператор присваивания, созданные компилятором, скопируют указатель, но не содержимое
по адресу указателя - произойдет shallow copy, то есть две копии объекта будут указывать
на один и тот же value. Обычно при копировании объекта класса требуется выполнить полное копирование,
то есть deep copy - скопировать и указатель, и данные. Для этого нужно переопределить
копирующий конструктор и копирующий оператор присваивания.*/
    IntHolder(const IntHolder & other) {
        value = new int(*other.value);
    }
    IntHolder & operator= (const IntHolder & other) {
        if (this != &other)
            *value = *other.value;
        return *this;
    }

/*4. При этом компилятор перестает создавать и перемещающие конструктор и присваивание.
Поэтому нужно добавлять и их.*/
    IntHolder(IntHolder && other) : value(other.value) //копируем укзатель
    {
        other.value = nullptr; //обнуляем указатель на старый объект
    }
    IntHolder & operator=(IntHolder && other)
    {
        std::swap(value, other.value);
        return *this;
    }

/*Если вы переопределили, например, деструктор, но вас устраивает работа остальных
четырех функций, то можно их не переопределять, а воспользоваться словом default,
которое указывает компилятору сгенерировать их самостоятельно:
~Obj() {cout << "Invoking destructor"<<endl;}
Obj(const Obj& other) = default;
Obj(Obj && other) = default;
Obj& operator= (const Obj & other) = default;
Obj& operator= (Obj && other) = default;
*/
};

IntHolder getInt(int val);

void useInt()
{
  IntHolder a(20);
  IntHolder b = a;
  //IntHolder b(a); то же самое
  IntHolder c();
  c = b;
  c.operator=(b); //то же самое
  IntHolder d(std::move(b)); //функция std::move помечает объект b как уже не нужный,
                             //то есть такой, из которого можно забрать данные.
  IntHolder e(getInt(4));
}


class DynamicArray
{
private:
  int *_data = nullptr;
  int _size = 0;
public:
  DynamicArray() {}
  DynamicArray(int size) : _size(size)
  {
    _data = new int[_size];
  }
  ~DynamicArray() 
  {
    delete [] _data;
  }
  DynamicArray(const DynamicArray &other): _size(other.size)
  {
    _data = new int[_size];
    for (int i=0; i<_size; i++) {
      _data[i] = other._data[i];
    }
  }
  DynamicArray(DynamicArray && other)
  {
    _size = other.size;
    _data = other._data;
    other._data = nullptr;
  }
  DynamicArray & operator=(const DynamicArray &other)
  {
    if (this == &other) return *this;

    delete [] _data;
    _size = other._size;
    _data = new int[_size];
    for (int i=0; i<_size; i++) {
      _data[i] = other._data[i];
    }
    return *this;
  }
  DynamicArray & operator=(DynamicArray && other)
  {
    if (this == &other) return *this;
    delete [] _data;
    _size = other._size;
    _data = other._data;
    other._data = nullptr;
    return *this;
  }

  const int *getData() const
  {
    return _data;
  }
  int getSize() const
  {
    return _size;
  }
  //копирует данные
  void setData(int *other, int size)
  {
    delete [] _data;
    _size = size;
    _data = new int[_size];
    for (int i=0; i<_size; i++) {
      _data[i] = other[i];
    }
  }

  void acquireData(int *& other, int size)
  {
    delete [] _data;
    _size = size;
    _data = other;
    other = nullptr;
  }
}

void ttt()
{
  DynamicArray b();
  int s=10;
  int *a = new int[s];
  //...
  b.acquireData(a,s);
  cout << a;//0
}

#endif // BIGFIVE_C11_H
