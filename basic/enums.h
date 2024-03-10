//enums.h

//В этом файле приведены примеры использования перечислений (enums) в c++.

//Базовые типы данных определены в c++ как часть ядра языка. Они доступны всегда,
//и не требуют дополнительных объявлений или включения дополнительных данных.
//Базовые типы данных включают простые типы - int, double, char и т.д.
//и составные типы - указатели, ссылки на простые типы, массивы элементов простого типа.

//Но что если этих типов данных недостаточно? Например, пусть программа работает
//с датами. Пусть месяц выражается целым числом в диапазоне [1; 12]. Тогда функция

int getDuration(int m1, int m2, int d1, int d2);

//могла бы например вычислять разницу между двумя датами. Но без подробной справки
//к функции программист легко может сделать ошибку:

int d = getDuration(2,14,5,26); //ошибочно передал значение месяца, выходящее за
//диапазон [1; 12].
int d1 = getDuration(2,5,14,26); //перепутал порядок аргументов.

//Если бы в c++ был отдельный тип данных, выражающий месяц, таких ошибок можно 
//было бы легко избежать. 

//Объявление собственных типов данных в c++ является его сильной стороной и 
//позволяет существенно расширить возможности программиста.

//Обычно объявление собственных типов данных выносят в отдельный заголовочный файл
//и затем включают этот файл директивой #include "---.h". Это позволяет вынести 
//всё специфичное в отдельный файл и не засорять код программы.


//Данный файл рассматривает такой пользовательский тип данных, как enum - перечисление.

//В c++ существует два типа перечислений - unscoped и scoped.

//Unscoped enums
//--------------

//Их еще называют нестрогими перечислениями. Они используются там, где логика 
//программы требует выбрать одно значение из конечного небольшого набора значений.
//Часто эти значения являются поименованными (стандартные цвета, названия месяцев
//или дней недели, названия пород собак и т.д.).

enum Month {
    Jan,
    Feb,
    Mar,
    Apr,
    May,
    //и т.д.
};
//Использование типа enum:
Month m = Apr;

//Отдельные значения объявленного перечисления неявно приводятся компилятором к 
//целому числу, причем первому значению будет соответствовать 0, второму 1, 
//третьему 2 и т.д. (Jan == 0, Feb == 1...)
//Вы можете задать требуемые значения каждому элементу enum в явном виде:

enum BetterMonth {
    January=1,
    February=2,
    March=3,
    April=4,
};

//Значения могут быть и непоследовательными, и отрицательными:
enum MyEnum {
    ONE = 17, //17
    TWO,      //18
    THREE = 0,//0
    FOUR = -3,//-3
    FIVE,      //-2
};

//Числовые значения enum можно использовать, например, для ввода-вывода:

BetterMonth month;
int val;
std::cin >> val;
//Оператор >> ничего не знает про тип данных BetterMonth, поэтому используем int:
month = static_cast<BetterMonth>(val); //static_cast преобразует значения из одного типа в другой



std::cout >> month; //выводим напрямую, здесь произойдёт неявное приведение типа

//Когда перечисление используется в качестве аргумента функции или с оператором,
//компилятор сначала старается найти функцию или оператор, которые соответствуют перечислению.
//Например, когда компилятор пытается скомпилировать std::cout >> month; , он сначала
//ищет, знает ли оператор >> как выводить значения типа BetterMonth. (Он не знает.)
//Если компилятор не находит соответствия, то неявно преобразует значение перечисления
//к его числовому значению. Так как оператор >> знает, как выводить значения типа int,
//в консоли окажется число, соответствующее значению val.

//Если нам требуется получить не числовые значения перечислений, а их имена, то
//единственное решение (без привлечения метапрограммирования) - это использовать
//конструкцию switch:

std::string monthName(BetterMonth month)
{
    switch (month) {
    case January: return "January";
    case February: return "February";
        //...
    default: break;
    }
    return "";
}

std::cout << monthName(month); //выведет строку

//Мы можем научить компилятор выводить значения перечисления, перегрузив оператор >>
//аналогично перегрузке функции:

std::ostream& operator<<(std::ostream& out, BetterMonth month)
{
    switch (month)
    {
    case January: return out << "January";
    case February:   return out << "February";
    //...
    default:    return out << "???";
    }
}

std::cout << month; //выведет строку, так как теперь знает, как выводить перечисление BetterMonth

// можно также научить компилятор вводить значения перечисления, перегрузив оператор >>

std::istream& operator>>(std::istream &in, BetterMonth &month)//month должен передаваться по ссылке
{
    int val;
    in >> val;
    month = static_cast<BetterMonth>(val);
    return in;
}


//Задание:
//6. Объявить enum Directions, в котором описать направления движения: влево, вправо, вверх, вниз,
//из консоли считать число, соответствующее направлению, и вывести в консоль словесное описание
//этого направления.

// Отступление: зачем действительно нужны перечисления и почему нельзя обойтись int

//Пусть мы пишем программу, в которой нужно указывать цвет яблок (красный, желтый
//или зеленый) и цвет рубашек (красный, зеленый, синий). Можно хранить цвет как
//целое число:

int main()
{
    int apple = 0; //яблоко красное
    int shirt = 1; //рубашка зеленая
    return 0;
}

//Но в числовых значениях легко запутаться. Попробуем использовать константы:

constexpr int red = 0;
constexpr int green = 1;
constexpr int blue = 2;

int main()
{
    int apple = red;
    int shirt = green;
}

//Уже лучше, но программист всё еще должен использовать только введенные константы,
//и ничто не запретит ему писать так:

int main()
{
    int apple = 0; //то же самое, что red, но менее интуитивно.
    int shirt = green;
}

// Конец отступления


// Почему перечисления, введённые словом enum, называются нестрогими (unscoped)?
// Рассмотрим пример:

enum ShirtColor
{
    red, 
    green, 
    blue, 
}; 

enum AppleColor
{
    green, 
    red, 
    yellow, 
};

//Значения нестрогих перечислений автоматически попадают в ту область видимости,
//в которой объявлены сами типы перечислений:

int main()
{
    AppleColor apple { red }; //используем red напрямую. Возникает неоднозначность.
    ShirtColor shirt { green }; //используем green напрямую. Возникает неоднозначность.
    ShirtColor tshirt { blue };  // OK 

    return 0;
}

//Такую неоднозначность невозможно исправить, не добавляя отдельное пространство имён:
namespace Apple {
    enum Color
    {
        green, 
        red, 
        yellow, 
    };
}

namespace Shirt {
    enum Color
    {
        red, 
        green, 
        blue, 
    }; 
}

int main()
{
    Apple::Color apple { Apple::red }; //OK
    Shirt::Color shirt { Shirt::green }; //OK
    Shirt::Color tshirt { Shirt::blue };  // OK 

    return 0;
}

//Еще один способ исключить неоднозначность - добавлять префиксы:
enum ShirtColor
{
    shirt_red, 
    shirt_green, 
    shirt_blue, 
}; 

enum AppleColor
{
    apple_green, 
    apple_red, 
    apple_yellow, 
};

int main()
{
    AppleColor apple { apple_red }; //OK
    ShirtColor shirt { shirt_green }; //OK
    ShirtColor tshirt { shirt_blue };  // OK 

    return 0;
}

//Ещё один недостаток нестрогих перечислений: в сравнениях компилятор использует
// только числовые значения перечислений:

int main()
{
    AppleColor apple { apple_red }; //OK
    ShirtColor shirt { shirt_green }; //OK
    if (apple == shirt) {
        //скомпилируется и будет равно true
    }

    return 0;
}

// Когда использовать перечисления?
// --------------------------------

//1. Там, где нужно вернуть один из немногих возможных исходов работы функции:

enum FileReadResult
{
    readResultSuccess,
    readResultErrorFileOpen,
    readResultErrorFileRead,
    readResultErrorFileParse,
};

FileReadResult readFileContents()
{
    if (!openFile())
        return readResultErrorFileOpen;
    if (!readFile())
        return readResultErrorFileRead;
    if (!parseFile())
        return readResultErrorFileParse;

    return readResultSuccess;
}

if (readFileContents() == readResultSuccess)
{
    // do something
}
else
{
    // print error message
}

//2. Там, где нужно создать в программе сущности разных типов 
//   (хотя классы для этого подходят лучше)

enum ItemType
{
    sword,
    torch,
    potion,
};

int main()
{
    ItemType holding{ torch };

    return 0;
}

//3. Когда необходимо дать пользователю выбор из нескольких альтернатив:

enum SortOrder
{
    alphabetical,
    alphabeticalReverse,
    numerical,
};

void sortData(SortOrder order)
{
    switch (order)
    {
        case alphabetical:
            // sort data in forwards alphabetical order
            break;
        case alphabeticalReverse:
            // sort data in backwards alphabetical order
            break;
        case numerical:
            // sort data numerically
            break;
    }
}

// Перечисления передаются в функции и возвращаются из функций по значению.


