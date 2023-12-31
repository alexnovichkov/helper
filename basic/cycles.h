#ifndef CYCLES_H
#define CYCLES_H

#include <iostream>
#include <fstream>
#include <cmath>

//Цикл - это способ выполнить похожий код несколько раз подряд. В С++ есть три вида циклов,
//хотя с небольшими изменениями их все можно использовать для одинаковых задач.

void usingWhile()
{
    //Цикл while
    //предназначен для выполнения кода, пока выполняется некоторое условие

    int count = 4;
    while (count > 0) {//выполняем всё, что содержится в скобках, пока справедливо условие count>0
        std::cout << "Hello!"<<std::endl;
        count--; //уменьшаем значение count. Если этого не сделать, тело цикла будет выполняться бесконечно.
    }
    std::cout << "Enough!"<<std::endl;

    //Цикл while может не выполниться ни разу, если условие цикла сразу равно false.

    //Выполнение цикла можно прервать в любой момент, используя оператор break;
    //Его удобно использовать в тех случаях, когда условие цикла неизвестно заранее:
    while (1) {//выполняем тело цикла бесконечно

        int i = 0; //какое-то значение
        //инструкции, изменяющие переменную i

        if (i>=10) break; //при достижении i=10 прерываем выполнение цикла
    }
}

void usingDoWhile()
{
    //Цикл do while
    //используется в тех случаях, когда тело цикла должно выполниться хотя бы один раз
    char ans;
    do {
        std::cout << "Hello" << std::endl;
        std::cout << "Do you want another greeting?" << std::endl;
        std::cout << "Press y for yes, n for no\n"
                  "then press Return" << std::endl;
        std::cin >> ans;
    } while (ans=='Y' || ans=='y');

    //При использовании цикла do while следует также заботиться об отсутствии бесконечных циклов.
}

void usingFor()
{
    //Цикл for используется в случаях, когда нам известно количество повторений тела цикла
    for (int i=0; i<10; i++) {} //тело цикла выполнится ровно 10 раз

    //Общий вид оператора for:
    //for (инициализатор счетчика; условие; действие со счетчиком) {}
    //Оператор for можно развернуть в следующую последовательность операций:
    //1. Инициализация переменной счетчика
    //2. Проверка условия цикла.
    //3. Если условие равно true, то выполнение тела цикла
    //                               иначе прерывание цикла
    //4. Изменение счетчика
    //5. Возвращение к 2.

    //Счетчиком может быть любая переменная, объявленная как непосредственно в инициализаторе цикла,
    //так и вне цикла. Это может даже быть несколько переменных:
    for (int x=0, y = 10; x<10 && y>=0; x++, y--) {
        //итерируем сразу с начала и с конца, используя две переменные счетчика
    }
    //Инициализатор может быть пустым, если переменная счетчика объявлена вне цикла:
    int x = 0;
    for ( ; x<10; x++) {}

    //Условие в цикле for может быть сложным, или может вообще отсутствовать, если выход
    //из цикла обеспечивается оператором break
    for (int i=0; ; i++) {
        //какие-то действия
        if (i==10) break;
    }

    //Изменение счетчика может отсутствовать, если оно происходит в теле цикла
    for (int i=0; i<10; ) {
        //какие-то действия
        i++;
    }

    //Изменение счетчика может представлять собой любое вычислимое выражение:
    double y = 12.5;
    for (double x = pow(y,3.0); x>2.0; x = sqrt(x)) {
        std::cout << x << std::endl;
    }

    //В самом простом случае цикл for может быть записан как
    for ( ; ; ) {
        //тело цикла
    }
    //Эта запись - без счетчика, без условия - полностью эквивалентна бесконечному циклу while
    while (1) {}
}

//Задания:

//1. Что будет выведено на экран в следующих фрагментах?
//a)
int x = 10;
while (x>0) {std::cout << x << endl; x -= 3;}
//b)
int x=10;
do {std::cout << x << endl; x-=3;} while (x>0);
//c)
int x = -42;
do {std::cout << x << endl; x-=3;} while (x>0);
//d)
int x = 10;
while (x>0) {std::cout << x << endl; x+=3;}
//e)
int s=0, n=0;
while (s<125) {s += 8; n -= 2;}
std::cout << n << std::endl;
//f)
int count = 3;
while (count−− > 0) std::cout << count << " ";
//g)
int count = 3;
while (--count > 0) std::cout << count << " ";

//2. Перепишите следующие фрагменты кода, используя циклы for
//а.
int i = 1;
while (i <= 10)
{
    if (i < 5 && i != 2)
        cout << 'X';
    i++;
}
//b.
int i = 1;
while (i <= 10)
{
    cout << 'X';
    i = i + 3;
}
//c.
long m = 100;
do
{
    cout << 'X';
    m = m + 100;
} while (m < 1000);

//Проектирование циклов
void designingLoops()
{
    //Циклы для суммирования и умножения
    //----------------------------------
    //Часто возникает задача вычислить сумму последовательности неких чисел (общую сумму покупки,
    //общий нанесенный урон по персонажу, медианное значение набора статистических данных и т.д.
    //Эта задача легко решается, если вы знаете общее количество чисел - цикл for.
    //Предположим, числа считываются из консоли
    int sum = 0;
    int totalCount, x;
    std::cin >> totalCount;
    for (int count = 0; count < totalCount; ++count) {
        std::cin >> x;
        sum = sum + x;
    }
    //Заметьте, что начальное значение суммы должно быть известно на момент первого выполнения
    //тела цикла.

    //Произведение чисел реализуется так же легко:
    int product = ?;
    int y;
    std::cin >> totalCount;
    for (int count = 0; count < totalCount; ++count) {
        std::cin >> y;
        product = product * y;
    }
    //Какое начальное значение должна иметь переменная product?

    //Условие выхода из цикла
    //-----------------------
    //Если известно общее количество повторений тела цикла, то удобно использовать
    //цикл for, означающий 'повторить n раз'.
    //Если же общее количество повторений зависит от действий пользователя, то просто
    //спросите его, прервать ли цикл:
    sum = 0;
    int number;
    char ans;
    do
    {
        std::cout << "Введите число: ";
        std::cin >> number;
        sum = sum + number;
        std::cout << "В списке остались числа? Наберите\n"
                  << "Y, если остались, или N, если чисел больше нет, а затем нажмите Enter: ";
        std::cin >> ans;
    } while ((ans == 'Y') || (ans == 'y'));

    //Однако такой способ заставляет пользователя подтверждать ввод каждого числа, что
    //весьма утомительно.
    //Третий подход состоит в использовании значения-ограничителя. Это такое значение,
    //которое не может встретиться в последовательности, и его наличие означает, что
    //последовательность закончилась
    std::cout << "Ведите список неотрицательных целых чисел через пробел.\n"
         << "Последним числом в списке введите -1.\n";
    sum = 0;
    std::cin >> number;
    while (number >= 0)
    {
        sum = sum + number;
        std::cin >> number;
    }
    //Для такого фрагмента кода ввод может быть, например, таким:
    //>1 2 7 10 3 2 1 1 -1

    //Естественным ограничителем выступают также конец файла или конец буфера с данными.
    //При проектировании программ чтения файла обычным условием является проверка на
    //достижение конца файла вида
    std::ifstream file;
    while (!file.eof()) {
        //чтение файла
    }

    //Значение-ограничитель может использоваться не только при вводе элементов.
    //Следующий фрагмент кода определяет, может ли студент быть старостой группы,
    //на основе его оценок. Если студент набирает 90 или больше баллов из 100, то
    //он кандидат в старосты.
    int n = 1; //номер студента
    int grade = computeGrade(n); //вычисление баллов для студента
    while (grade < 90)
    {
        n++; //следующий студент
        grade = computeGrade(n);
    }
    std::cout << "Студент №" << n << " может стать старостой.\n"
         << "Он набрал " << grade << " баллов\n";
    //Переменная grade здесь выступает в качестве флага-ограничителя.

    //У этого кода есть серьезный недостаток. Что если ни один студент не наберет >90
    //баллов? Что будет, когда закончатся студенты? В обоих случаях возникает риск
    //бесконечного цикла.
    //Если вы видите, что ваш код может "зациклиться", то добавляйте дополнительное
    //условие, которое обеспечит выход из цикла при достижении некоторого максимального
    //количества повторений.
    int n = 1;
    grade = computeGrade(n);
    while ((grade < 90) && (n < numberOfStudents))
    {
        n++;
        grade = computeGrade(n);
    }
    if (grade >= 90)
        std::cout << "Студент №" << n << " может стать старостой.\n"
             << "Он набрал " << grade << " баллов\n";
    else
        std::cout << "Ни один студент не набрал достаточно баллов.";

}




//Задания ниже можно выполнить как с использованием циклов, так и выведя подходящую формулу.
//Найдите наилучшее решение.

//3. Напишите программу, которая выводит числа от 1 до N через пробел.
//4. Напишите программу, которая последовательно вычисляет квадратные корни числа, превышающие
//   заданное пороговое значение. Начальное число и пороговое значение считываются из консоли.
//5. На кредитной карте N рублей. Банк берет 3% за обслуживание кредита каждый месяц.
//   Сколько месяцев можно держать карту, не осуществляя выплаты, пока баланс не
//   достигнет лимита 2N рублей?
//6. Напишите программу, вычисляющую целую степень числа x. x - вещественное число,
//   n - целое положительное число.
//7. Перепишите программу 6 так, чтобы она вычисляла степень числа для любых
//   целочисленных значений n.
//8. Беговая дорожка показывает скорость в км/ч. Для скорости x км/ч посчитайте и выведите,
//   сколько секунд и минут понадобятся бегуну, чтобы пробежать 1 км.
//9. Магазин продает ковровые дорожки по 420 р за погонный метр. Если покупатель берет
//   больше 10 м, то он получает скидку 12% за каждый следующий метр. Напишите программу,
//   которая считает общую стоимость ковра в зависимости от его длины.
//10. Напишите программу, которая считывает последовательность целых положительных чисел
//   и выводит максимальное и минимальное число. Пользователь вводит числа одно за другим,
//   нажимая Enter после каждого числа, и заканчивает ввод нулем или отрицательным числом.

//Ниже представлены проектные задания, максимально приближенные к реальным задачам

//11.
//Зоологи контролируют численность вымирающего красношеего грифа на обширной территории.
//Каждому зоологу выделена область, на которой он ищет гнезда грифа и подсчитывает количество
//яиц в гнездах. Координатору проекта он сообщает количество яиц в каждом гнезде.
//Коодинатор проекта собирает данные от каждого зоолога и определяет общее количество яиц
//в области, а также общее количество яиц на всей подконтрольной территории.
//Напишите программу, которая реализует подсчет яиц.
//Количество гнезд может быть различным. Поэтому список от каждого зоолога должен
//заканчиваться отрицательным числом (можно ли использовать 0 в качестве флага-ограничителя?)
//Входные данные:
//- количество зоологов (подконтрольных областей)
//Выходные данные:
//- количество яиц в каждой области
//- общее количество яиц

//12.
//Напишите простую консольную игру в блэкджек (очко).
//Игрок получает от 2 до 5 карт. Цель игры - набрать 21 очко, добирая карты.
//При превышении 21 на руке игрок проигрывает.
//Карты от 2 до 10 считаются по номиналу. Валет, дама и король считаются по 10.
//Туз считается либо по 1, либо по 11, что выгоднее игроку.
//Входные данные: количество карт и обозначения каждой карты одним символом без пробелов:
//'2'-'9' для карт от двойки до девятки, 't' для десятки, 'j' для валета, 'q' для дамы,
//'k' для короля, 'a' для туза.
//Символы карт следует считывать в переменную типа char.
//Пример ввода:
//3
//3qa
//Выходные данные: фразы "Не добрал", "Выиграл" или "Перебор"

//13.
/*
Игрок участвует в следующей игре. Перед ним есть три двери. За одной - новый автомобиль.
За двумя другими - утешительные призы. Игрок выбирает одну из дверей. После этого
ведущий игры открывает одну из двух оставшихся дверей, за которой точно утешительный приз. Затем
ведущий спрашивает игрока, хочет ли тот изменить свой выбор. Игрок либо меняет выбор двери,
либо оставляет выбор как есть. После этого выбранная дверь открывается.
Напишите программу, которая вычисляет вероятность выиграть в такой игре (саму игру
эмулировать не надо). Реализуйте три сценария игры - игрок никогда не меняет выбор, игрок
всегда меняет выбор, игрок меняет выбор случайным образом. Прогоните алгоритм в цикле
из 10000 игр, и выведите в консоль веростности выиграть в каждом сценарии.
Выбор двери, за которой должна быть машина, а также вероятность сменить дверь в сценарии 3
реализуется через генерацию случайных чисел.
*/

//Генерация случайных чисел:
//этот заголовочный файл нужно подключить перед main
#include <random>

//эти строки позволят инициализировать генератор случайных чисел. Поместите их
//в самое начало функции main
std::random_device randomDevice;  //устройство для инициализации генератора случайных чисел
std::mt19937 generator(randomDevice()); //объявляем генератор случайных чисел
std::uniform_int_distribution<> distrib(m, n); //объявляем равномерное распределение в диапазоне [m; n]
//Далее везде, где требуется получить случайное целое число из диапазона [m; n],
//используйте функцию
int randomNumber = distrib(generator);

//Вероятность выиграть в сценарии - это просто отношение количества выигрышей в этом
//сценарии к общему количеству игр

//14. Игра "23" заключается в следующем: перед двумя игроками лежит кучка из 23 спичек.
//Каждый игрок поочередно вытаскивает на выбор 1, 2 или 3 спички. Проигрывает тот, кто вытаскивает
//последнюю спичку.
//Реализуйте игру "23" против компьютера.
//Пользователь всегда ходит первым. Он вводит число, равное количеству вытаскиваемых спичек.
//Добавьте проверку введенного числа - оно должно лежать в диапазоне [1,3] и не должно
//превышать оставшееся количество спичек.
//Компьютер должен ходить по следующему алгоритму:
//- если спичек осталось больше 4, то компьютер вытаскивает столько же, сколько вытащил пользователь
//на последнем своем ходу.
//- если спичек отсталось от 2 до 4, то компьютер вытаскивает ровно столько, чтобы осталась одна
//спичка.
//- если осталась 1 спичка, то компьютер проигрывает.


#endif // CYCLES_H
