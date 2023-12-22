#ifndef IFS_H
#define IFS_H

#include <iostream>

using namespace std;



void ifExample1()
{
    //Использование зарезервированного слова if позволяет реализовать ветвление.
    //Если выполняется условие - сделай то, иначе - сделай это.

    //Для конструирования условий обычно используют булевы операторы
    // >, >=
    // <, <=
    // !=
    // ==

    int x = 10;

    if (x > 0) {
        cout << "число положительное";
    }
    else if (x<0) {
        cout << "число отрицательное";
    }
    else {
        cout << "число равно нулю";
    }

    //Веток else в условии может и не быть:
    if (x==0) {
        x=1;
    }

    //Если в ветке выполняется всего одна инструкция, то фигурные скобки можно опустить:
    if (x>0) x= -x;
    else x = 10;

    //Такое условие можно также переписать с помощью тернарного оператора сравнения ?:
    x = x>0 ? -x : 10;
    //Тернарный оператор сравнения можно использовать и в более сложных  выражениях:
    int y = 20 * (x>0 ? -x : 10);
    //что равнозначно следующей более понятной, но более длинной записи:
    int z = 20;
    if (x > 0) z*= -x;
    else z *= 10;

    //Условие можно вычислить заранее. Все условия представляют собой выражения типа bool
    bool condition = x>0;
    if (condition) {
        x=-x;
    }

    //Если в качестве условия передать число, целое или вещественное, то оно
    //будет приведено к значению bool следующим образом:
    //- число, отличное от 0, даст true
    //- нуль даст false

    x=1;
    if (x) { //x == true
        //выполнится эта ветка
    }
    else {
        //эта ветка будет пропущена
    }

    //Указатели также можно привести к типу bool: Нулевой указатель - всегда false,
    //ненулевой указатель = true.

    //Условие может представлять собой сложное арифметическое выражение:
    if (x % 2) {//остаток от деления на 2. Здесь выполняется проверка на нечетность.
        //выполнить действие
    }
    //Но обычно такие условия записывают явно:
    if (x % 2 !=0) {
        //выполнить действие
    }
}

//Задачи:
//1. Написать программу, выводящую в консоль большее из двух чисел, введенных пользователем.
//2. Написать программу, выводящую в консоль четность числа, введенного пользователем.

void ifExample2()
{
    //Условия можут быть сложными. Так как условия представляют собой булевы выражения,
    //то простые условия можно комбинировать, используя булевы операторы:
    // ! - отрицание:    !(x<0) равно x>=0
    // && - булево И:    (x>0) && (x<10) дает попадание в интервал (0, 10).
    // || - булево ИЛИ:  (x>10) || (x<0) дает НЕПОПАДАНИЕ в интервал (0, 10).

    int month = 3;
    if (month==1 || month==2) {
        //если январь или февраль
    }
    if (month >= 1 && month <= 3) { 
        //если 1-й квартал
    }
    if (!month) {
        //передан неверный месяц
    }

    //Частичное вычисление условий
    //----------------------------
    //Если в условии два простых условия соединены булевым И или булевым ИЛИ, то компилятор
    //оптимизирует такие условия:
    //1. Если используется булево И, то, так как a&&b истинно только тогда, когда истинны
    //   оба аргумента, то компилятор не проверяет значение b, если a ложно:
    if (month==1 && month/0>-6) {
        //второе условие не будет вычисляться, так как первое условие ложно
    }
    //2. Если используется булево ИЛИ, то, так как a||b ложно только тогда, когда ложны
    //   оба аргумента, то компилятор не проверяет значение b, если a истинно:
    if (month==3 || month/0>-6) {
        //второе условие не будет вычисляться, так как первое условие истинно
    }
    //Таким образом, компилятор ограничивается проверкой только первого условия, если этого
    //достаточно для определения истинности или ложности всего условия целиком.

    //Более того, если условия представляют собой вызовы функций, возвращающих булевы значения,
    //то вторая функция даже не будет вызвана:

    auto isFirstQuarter = [](int month){
        return (month>=1 && month <=3);
    };
    auto divisionByZero = [](int month) {
        return month/0 == 0;
    };

    if (isFirstQuarter(month) || divisionByZero(month)) {
        //функция divisionByZero не будет вызвана, значение всего условия известно по
        //первому подусловию (isFirstQuarter(month) вернет true), так что такое условие безопасно.
    }
}

//Задача:
//3. Дана прямоугольная область на плоскости, заданная левым нижним (x1,y1) и правым верхним (x2, y2) углом.
//   Пользователь вводит координаты углов, а затем координаты точки (x,y).
//   Проверить попадание точки в эту область.
//3.1. Дана область на плоскости, ограниченная окружностью
//     (x-a)^2 + (y-b)^2 = c
//     Пользователь вводит коэффициенты a,b,c, а затем координаты точки (x,y). Проверить попадание
//     точки внутрь окружности.

void ifExample3()
{
    //При использовании оператора == следует особо внимательно записывать условия с ним,
    //так как его легко можно спутать с оператором присвоения =
    int x=1;
    if (x==2) {//в условии записано сравнение x с 2

    }
    if (x=2) {//в условии мы присвоили переменной x значение 2, ни с чем не сравнивая
              //полученное число, то есть это условие всегда вернет true.
    }

    //Таким образом, в условии можно использовать оператор присвоения,
    //но смысл у такого условия будет совершенно отличным от оператора сравнения ==.
    //Если в результате присваивания получится 0 или величина, приводимая к 0, то условие всегда
    //будет ложным.
    //Если в результате присваивания получится величина, не приводимая к 0, то условие всегда
    //будет истинным.


    //Однако присваивание внутри условия можно использовать в таком виде:
    if (int y = getYValue(); y>0) { //вычисляем значение переменной y
        std::cout << y << "y is valid";
        //do something if y is valid
    }
    else {
        std::cout << y << "y isn't valid";
        //do something if y isn't valid
    }
    //Здесь переменная y нужна только для последующей проверки и ветвления кода.
    //Она не используется нигде вне условия, то есть выносить ее перед условием не нужно.
    //Такая запись позволяет ограничить область видимости переменной y локальной областью
    //видимости условия.

    //Можно записать то же самое условие в другом, более явном виде:
    int y = getYValue();
    if (y>0) { //вычисляем значение переменной y
        std::cout << "y is valid";
        //do something if y is valid
    }
    else {
        std::cout << "y isn't valid";
        //do something if y isn't valid
    }
    //однако теперь переменная y определена и видна везде ниже в этой функции

    //если значение переменной, объявляемой в условии if, не требуется в теле условия,
    //то можно и вовсе не создавать эту переменную:
    if (getYValue()>0) { //вычисляем значение
        //do something
    }
    else {
        //do something
    }
}



/*Задача:
4. Что будет выведено на экран при выполнении следующих фрагментов:
int x=0;
int y=5;
if (x==y%2)  std::cout<<"условие 1 - 1"<<endl;
else    std::cout<<"условие 1-2"<<endl;

if (x=y%2) std::cout<<"условие 2 - 1"<<endl;
else std::cout<<"условие 2-2"<<endl;
*/

void ifExample4()
{
    //С помощью добавления ветвей else можно конструировать цепочки условий:
    int x=1;
    if (x==1) std::cout<<"январь";
    else if (x==2) std::cout<<"февраль";
    else if (x==3) std::cout<<"март";
    else if (x==4) std::cout<<"апрель";
    //...

    //Но если нам требуется перебрать значения какой-нибудь переменной, проще это записать с помощью
    //оператора switch, который предоставляет удобный выбор из множества альтернатив

    switch(x) {
        case 1: std::cout<<"январь"; break;
        case 2: std::cout<<"февраль"; break;
        case 3: std::cout<<"март"; break;
        case 4: std::cout<<"апрель"; break;
        default: std::cout<<"другой месяц"; break;
    }

    //Если в каждой ветви switch нужно записать несколько инструкций, то можно использовать
    //фигурные скобки
    int quarter=0;
    switch(x) {
        case 1: {
            std::cout<<"январь";
            quarter=1; //первый квартал
            break;
        }
        case 2: {
            bool c = false;
            std::cout<<"февраль";
            quarter=1;
            break;
        }
        case 3: {
            std::cout<<"март";
            quarter=1;
            break;
        }
        case 4: {
            std::cout<<"апрель";
            quarter=2; //второй квартал
            break;
        }
        default: std::cout<<"другой месяц"; break;
    }

    //Но можно заметить, что мы продублировали одну и ту же инструкцию три раза: quarter=1;
    //Если воспользоваться т.н. "проваливанием сквозь условия" и вынести эту инструкцию в отдельный
    //оператор switch, то можно сократить код:

    switch (x) {
        case 1:
        case 2:
        case 3:
            quarter=1; break;
        case 4:
        case 5:
        case 6:
            quarter=2; break;
            //и так далее.
    }

    //Запомните: если мы пропустим оператор break в одной из ветвей, то сразу начнут
    //выполняться инструкции из следующей ветви - это и есть "проваливание".
}

/*Задание:
5. Что будет выведено в консоль при выполнении этого кода и почему?
int x;
switch (x) {
    case 0: std::cout<<"неправильный месяц"<<std::endl; break;
    case 1: std::cout<<"январь"<<std::endl; break;
    case 2: std::cout<<"февраль"<<std::endl; break;
    case 3: std::cout<<"март"<<std::endl;
    case 4: std::cout<<"апрель"<<std::endl; break;
    default: std::cout<<"другой месяц"<<std::endl;
}
при значениях переменной x 0, 1, 2, 3, 4, -1
*/

//В качестве условия в операторе switch можно использовать переменные перечислимых типов:
//- целочисленные переменные: char, short int, int, long int, long long int, все их варианты с unsigned
//- тип bool
//- перечисления enum.
//- переопределения целочисленных типов с помощью typedef и using

//Перечисления enum - это способ явного создания нового целочисленного типа данных с помощью перечисления
//его значений через запятую. Он используется, если все возможные значения переменной нам известны и
//их можно поименовать. Пример - названия месяцев

enum Month {
    Jan,
    Feb,
    Mar,
    Apr,
    May
    //и т.д.
};
//Использование типа enum:
Month m = Apr;

//Отдельные значения объявленного перечисления неявно приводятся компилятором к целому числу, причем
//первому значению будет соответствовать 0, второму 1, третьему 2 и т.д. (Jan == 0, Feb == 1...)
//Вы можете задать требуемые значения каждому элементу enum в явном виде:

enum BetterMonth {
    January=1,
    February=2,
    March=3,
    April=4
};

//Значения могут быть и непоследовательными, и отрицательными:
enum MyEnum {
    ONE = 17, //17
    TWO,      //18
    THREE = 0,//0
    FOUR = -3,//-3
    FIVE      //-2
};

//Задание:
//6. Объявить enum Directions, в котором описать направления движения: влево, вправо, вверх, вниз,
//из консоли считать число, соответствующее направлению, и вывести в консоль словесное описание
//этого направления.


//- Дополнения -
//--------------

//Как было упомянуто выше, любое значение enum неявно приводится к целому числу.
//Поэтому допустимы такие записи:
int x = ONE;   //значение ONE типа MyEnum поместили в переменную типа int
MyEnum e = MyEnum(x);  //преобразовали обратно из int в MyEnum

//Если это неявное приведение требуется заблокировать, то можно использовать т.н. "строгие перечисления",
//которые работают как отдельный тип данных, никак не связанный с числами:
enum class MouseKey {
    Left,
    Middle,
    Right
};

//Использование строгого перечисления требует явно указывать тип переменной:
MouseKey key = MouseKey::Left;
//Неявное приведение к числу уже не скомпилируется:
int badKey = MouseKey::Left;
//Чтобы добиться желаемого, необходимо уже явно использовать оператор приведения
int badKey1 = static_cast<int>(key);

#endif // IFS_H
