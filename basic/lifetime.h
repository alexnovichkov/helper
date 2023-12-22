#ifndef LIFETIME_H
#define LIFETIME_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>

void lifetime()
{
/*

ВРЕМЯ  ЖИЗНИ ОБЪЕКТОВ

Каждый объект (включая ссылки) имеет конечное время жизни при выполнении программы:
для любого объекта существует точка в выполнении программы, в которой объект появляется,
и точка, в которой объект уничтожается.

Объект создается, когда выделено место в памяти для объекта и это место инициализировано значением.
Под инициализацией понимается инициализация значением по умолчанию, выполнение конструктора
объекта или тривиального конструктора объекта (об этом см. structs_classes.h).
*/
int i; //объявлена, но не инициализирована. Типы int, double, char, bool не имеют значения
       //по умолчанию. Поэтому здесь переменная может принять любое значение.
int j=3; //объявлена и инициализирована, при выполнении этой строчки под переменную
         //выделяется память и туда записывается значение. Переменная создана.
i=3; //записали значение. Теперь переменная создана.
std::string s; //строки инициализируются значением по умолчанию - пустой строкой - s создана
std::string ss = "abcde"; //строка создана и инициализирована строкой - переменная ss создана

/*
Время жизни объекта заканчивается, когда

- объект выходит из области видимости (если это не объект класса)
- вызывается деструктор объекта (если это объект класса)
- уничтожается хранилище, в котором расположен объект (об этом см. structs_classes.h)

Время жизни объекта не превышает времени жизни его хранилища.

Время жизни ссылки начинается с момента инициализации ссылки и заканчивается по общим правилам.
Однако время жизни объекта, на который ссылается ссылка, может закончиться раньше,
чем время жизни ссылки, тогда образуется т.н. "висячая ссылка" (dangling reference).
Висячая ссылка указывает на уже уничтоженный объект, поэтому ее использование приводит
к падению программы.
*/

//Пример висячей ссылки:
//Функция возвращает ссылку - return-by-reference
double & referenceToObject(double x)
{
    double z = std::pow(x, 2);
    return &z;
}
double &y = referenceToObject(6);
/*Объект z создан внутри тела функции, то есть имеет локальную для функции область видимости.
Он будет уничтожен сразу после окончания выполнения функции. Однако мы возвращаем из
функции ссылку на него. Ссылка будет существовать, пока существует объект y. Но объект
z, на который ссылается y, уже уничтожен - имеем висячую ссылку. При попытке ее использовать
программа упадет:*/
std::cout << y; //Ошибка!

/*
Запомните: всегда проверяйте, что время жизни ссылки не превышает времени жизни объекта,
на который она ссылается.

Всё сказанное выше применимо также и к указателю, возвращаемому из функции.

Временные объекты
-----------------

Временные объекты создаются в момент окончания вычисления выражения и уничтожаются в момент
перехода к следующему выражению в коде программы.
*/

int x=4;
int y=x+4;
//x+4 - временный объект, вычисляемый при выполнении строки 76. После полного выполнения
//строки 76 (после присвоения значения объекта x+4 переменной y) он уничтожается.
x+4; //создается новый временный объект и сразу уничтожается.

/*
Возвращение объекта из функции по значению (return-by-reference) также возвращает временный
объект:*/

double z = std::pow(x,5); //std::pow(x,5) возвращает временный объект, который уничтожается
                          //после присвоения его значения переменной z
std::pow(z,-2); //объект создан и сразу уничтожен.


//Существуют средства продлить время жизни временного объекта - r-value ссылки
}
#endif // LIFETIME_H
