#ifndef FILESTREAMS_H
#define FILESTREAMS_H

/**
  Этот файл описывает работу с файловыми потоками в C++
  */

#include <iostream>
#include <fstream> //<- нужен для открытия файлов
#include <iomanip> //<- нужен для форматирования потока вывода

void useFiles() {
    //За чтение файла отвечает класс ifstream - файловый поток чтения
    //За запись в файл отвечает класс ofstream - файловый поток записи
    //Если файл требуется и читать, и писать, то нужно использовать класс fstream

    //Открытие файла - это создание переменной типа [i|o]fstream
    std::ifstream myFile;
    //и вызов метода open
    myFile.open("file name with file path");

    //Отступление: что такое классы и методы

    //Эти две строки можно объединить в одну:
    std::ifstream myOtherFile("file name with path");
    //В этой строке объявляется переменная и сразу открывается файл.

    //Первый вариант удобно использовать, если при объявлении переменной myFile
    //вы еще не знаете, какой файл будете открывать.

    //Проверить, открыт ли файл, можно с помощью метода
    if (myFile.is_open()) {}

    //При использовании класса fstream мы должны явно указать, какую операцию мы будем
    //делать с файлом - чтение или запись. Для этого в метод open вторым аргументом нужно
    //передать требуемые флаги
    std::fstream fileToReadAndWrite;
    fileToReadAndWrite.open("file name", std::ios::in | std::ios::out);
    std::fstream fileToRead;
    fileToRead.open("file name", std::ios::in );
    std::fstream fileToWrite;
    fileToWrite.open("text.txt", std::ios::out);
    fileToWrite << "aaaaaa"; //в файле 6 символов 'a'

    //После окончания работы с файлом его необходимо закрыть:
    myOtherFile.close();
    myFile.close();
    //Этого можно и не делать, так как деструктор файловых потоков при выходе переменной
    //из области видимости автоматически закрывает файл.

    //Файл, который вы открываете для чтения, должен существовать, иначе сгенерируется ошибка.
    //Файл для записи существовать не обязан. При обращении к файлу он будет создан на жестком диске.
    //При открытии файла, если есть подозрение, что он не существует, используйте следующий код:
    std::string fileName {"file name with path"};
    std::fstream fs(fileName); //По умолчанию файл открывается и на чтение, и на запись
    if (fs.fail()) {//проверяем, открылся ли файл. Если не открылся, открываем его только на запись
        fs.clear(); //сбрасываем состояние ошибки
        fs.open(fileName, std::ios::out); //создаем новый файл
        fs.close(); //сразу закрываем его
        fs.open(fileName, std::ios::out | std::ios::in); //переоткрываем файл
    }

    //Для открытия файла, имя которого содержит не только латинские символы, необходимо имя
    //файла передавать как "широкую" строку типа wstring
    std::wstring russianName = L"файл.txt";
    fs.close();
    fs.open(russianName);
    //Это можно сделать, только если вы компилируете программу компилятором VC++ (то есть в Visual Studio)
    //Еще один способ - использовать класс filesystem, который имеет функцию, перекодирующую
    //путь к файлу в кодировку операционной системы.
    //#include <filesystem> //<- этот файл нужно подключить
//    std::string name = u8"текст.txt";
//    fs.close();
//    fs.open(std::filesystem::u8path(name), std::ios::out);
    //Всё это можно не делать, если название файла содержит только русские и латинские символы и
    //файл cpp, в котором вводится имя файла, сохранен в кодировке Windows-1251.

    //Если операция с файловым потоком завершилась неудачей, то проверить состояние потока можно
    //следующими функциями:
    fs.good(); //быстрая проверка состояния потока, если true, то можно работать дальше
    fs.eof(); //достигли конца файла
    fs.bad(); //поток в состоянии ошибки
    fs.fail(); //операция чтения/записи с потоком не удалась


    //По умолчанию файл открывается в текстовом формате. Это значит, что при чтении концов строк
    //из файла или при записи концов строк символы \n будут преобразованы к типу, специфическому
    //для операционной системы. Если это не требуется, и файл должен быть прочитан
    //в точности как есть, то при открытии файла можно добавить параметр для окрытия файла
    //в бинарном формате:
    myFile.open("filename with file path", std::ios::binary);
    //Теперь файл будет читаться в точности так, как записан на жестком диске.

    //Как прочитать из файла все данные, если неизвестно, сколько этих данных в файле?
    //Используйте следующую конструкцию:
    //1. Если в файле записаны однородные данные, то используйте оператор >>, возвращающий false,
    //если достигли конца файла
    int a;
    while (myFile >> a) { } //чтение файла будет продолжаться, пока данные доступны
    //2. Если в файле записаны разнородные данные, то используйте метод класса fstream eof
    while (!myFile.eof()) { } //eof вернет true, если достигли конца файла
    //Примеры:
    //1. В файле в каждой строке записано одно целое число. Количество строк неизвестно.
    //Требуется найти сумму этих чисел.
    int sum=0;
    while (myFile >> a) {sum += a;}
    //2. В файле в каждой строке записано одно вещественное и одно целое число. Требуется
    //найти сумму вещественных чисел в степени, выражаемой целым числом.
    double Sum=0;
    double x;
    int n;
    while (!myFile.eof()) {
        myFile >> x >> n;
        Sum += std::pow(x, n);
    }

    //При открытии файла только на запись файловый поток по умолчанию встает на начало файла
    //и уничтожает содержимое файла.
    //Чтобы иметь возможность дописывать данные в конец файла, мы должны
    //открыть его с флагом ios::app. При этом мы автоматически оказываемся в конце файла.
    fileToWrite.close();
    fileToWrite.open("file name", std::ios::out | std::ios::app);
    fileToWrite << "b"; //в файле символы "aaaaaab"
    //Чтобы иметь возможность писать данные в любое место файла (перезаписывать данные)
    //необходимо открыть файл и на чтение, и на запись
    fileToWrite.close();
    fileToWrite.open("file name", std::ios::out | std::ios::in);
    fileToWrite << "b"; //в файле символы "baaaaab"

    //Кроме того, вы можете явно указать, что содержимое файла нужно удалить при открытии
    fileToWrite.close();
    fileToWrite.open("file name", std::ios::out | std::ios::in | std::ios::trunc);
    fileToWrite << "b"; //в файле символы "b"


    //Навигация по файлу

    //Текущее положение в файле можно получить функцией tellg (или tellp для выходных потоков).
    long long position = fileToWrite.tellg();


    //Для перехода в определенную позицию в файле есть функция seekg (или seekp для выходных потоков).
    //Она принимает дополнительный параметр, который обозначает, как именно нужно сместиться в файле
    fileToWrite.seekg(position); //переходит в позицию pos относительно начала файла
    long long offset = 10;
    fileToWrite.seekg(offset, std::ios::beg); //переходит в позицию offset относительно начала файла
    fileToWrite.seekg(-offset, std::ios::end); //переходит в позицию -offset относительно конца файла
    //то есть отсчитывает offset символов влево от конца файла
    fileToWrite.seekg(offset, std::ios::cur); //переходит в позицию offset относительно
    //текущего положения в файле,
    //то есть отсчитывает offset символов вправо от текущего положения

    //Если вы превысите размер файла, то при записи данных файл будет дополнен нулевыми символами \0.
    //Если вы выйдете за границу начала файла, то операция чтения/записи не сработает.

    //ОПЕРАЦИИ ЧТЕНИЯ ИЗ ФАЙЛОВОГО ПОТОКА

    //1. Оператор >>
    //Позволяет прочитать из файла данные определенного заранее известного типа.

    //2. Методы классов ifstream и fstream
    //get(char* buffer, long long count [, char delim]); читает count символов до разделителя delim
    //       (по умолчанию - символ '\n') и помещает в буфер buffer достаточной длины. Чтение
    //       останавливается перед разделителем.

    //get(char &с); читает один символ и помещает его в переменную c.

    //int get(); то же самое, но возвращает прочитанный символ.

    //Особенности использования get:
    //Метод get читает все символы потока, включая символы перевода строки. Поэтому следует
    //обращать особое внимание на вызовы get, так как они вернут в точности то, что
    //записано в потоке.
    //Пример: требуется прочитать из консоли целое число и символ. Написан следующий код:
    std::cout << "Enter a number:\n";
    int number;
    std::cin >> number;
    std::cout << "Now enter a letter:\n";
    char symbol;
    std::cin.get(symbol);
    //Программист ожидает, что он будет работать так:
    //Enter a number:
    //21
    //Now enter a letter:
    //А
    //
    //и переменная number имеет значение 21, а переменная symbol - значение 'A'.
    //Однако в поток были отправлены следующие символы: 21\nA\n. Это значит, что
    //после чтения number поток остановился в позиции после 21, но не перед A, то есть
    //следующий символ потока равен '\n'. Поэтому в итоге в переменной symbol окажется
    //символ '\n'.
    //Как решить эту проблему:
    //1. Можно просто не использовать оператор >> и метод get вместе.
    std::cout << "Enter a number:\n";
    std::cin >> number;
    std::cout << "Now enter a letter:\n";
    std::cin >> symbol;
    //2. Можно пропускать все символы до конца строки включительно следующей командой:
    std::cout << "Enter a number:\n";
    std::cin >> number;
    newLine();
    std::cout << "Now enter a letter:\n";
    std::cin.get(symbol);

    //где newLine() - вспомогательная функция со следующим кодом:
    void newLine(std::istream &stream = std::cin)
    {
        char symbol;
        do {
           stream.get(symbol);
        } while (symbol != '\n');
    }

    //getline(char* buffer, long long count [, char delim]); читает count символов до разделителя delim
    //       (по умолчанию - символ '\n') и помещает в буфер buffer достаточной длины. Чтение
    //       останавливается после разделителя

    //Вместо метода getline, который должен первым параметром принимать указатель на
    //буфер достаточной длины, удобнее использовать функцию getline, объявленную в заголовочном
    //файле <string>. Она принимает вторым параметром переменную типа std::string.

    //read(char *buffer, long long count); читает count символов и помещает в буфер,
    //не добавляя к буферу конечный '\0'. Этот метод удобно использовать при чтении
    //бинарных, а не текстовых, файлов.

    //int peek(); читает один символ и возвращает его, но не сдвигает позицию в потоке.
    //Последующее чтение из файла вернет тот же символ.

    //ignore([long long count [, char delim]]); пропускает count (по умолчанию 1)
    //символов вплоть до первого delim (по умолчанию std::ios::eof), включая delim.
    //Этот метод удобно использовать для пропуска остатка строки в файле:
    fileToRead.ignore(200, '\n');

    //Как прочитать весь файл и сохранить содержимое в строку?
    if(std::ifstream is{"test.txt", std::ios::binary | std::ios::ate}) {//открыли файл и перешли в его конец
        auto size = is.tellg(); //tellg вернёт размер файла
        std::string str(size, '\0'); // создаем строку длиной, равной размеру файла
        is.seekg(0); //переходим в начало файла
        is.read(&str[0], size);
    }

    //Как прочитать одну строку файла?
    if(std::ifstream is{"test.txt"}) {
        std::string str;
        std::getline(is, str, '\n'); // в строке str - ровно одна строка из файла,
                                     // позиция чтения переместилась на начало след. строки
    }


    //ОПЕРАЦИИ ЗАПИСИ В ФАЙЛОВЫЙ ПОТОК

    //1. Оператор <<
    //2. Методы классов ofstream и fstream
    //put(char c); записывает в поток один символ
    //write(const char *buffer, long long n); записывает в поток n символов из буфера

    //Кроме того, можно использовать следующие манипуляторы:
    //std::endl - записывает в поток символ перевода строки
    //std::ends - записывает в поток нулевой символ '\0'

    //Кроме того, при записи в поток доступны все обычные манипуляторы форматированного
    //вывода: left, right, setw, scietifix/fixed/defaultfloat, dec/oct/hex,
    //setprecision, showpoint/noshowpoint, showpos/noshowpos
}

//Функции, принимающие поток аргументом
//
//Предположим, мы пишем программу, в которой каждое действие пользователя должно сохраняться
//в некотором журнале действий. Предположим, мы должны дать пользователю выбор - сохранять
//его действия в отдельный файл журнала или выводить на экран. Как реализовать этот выбор?
//Предположим, у нас есть функция подключения к базе данных, и мы логируем действия
//пользователя. Пусть она выводит лог на экран (в консоль)
bool connectToDatabase(std::string &name, std::string &password)
{
    //действия, осуществляющие подключение
    if (connectTo(name, password)) {
        std::cout << "User "<<name<<" connected\n";
        return true;
    }

    std::cout << "Failed to connect for user "<<name<<"\n";
    return false;
}
//Для вывода лога в файл нам придется продублировать эту функцию следующим образом:
bool connectToDatabaseFile(std::string &name, std::string &password)
{
    std::ofstream f("database-log.txt", std::ios::ate);
    //действия, осуществляющие подключение
    if (connectTo(name, password)) {
        f << "User "<<name<<" connected\n";
        return true;
    }

    f << "Failed to connect for user "<<name<<"\n";
    return false;
}
//Мы лишь незначительно изменили код функции, но теперь у нас две функции, делающие
//одно и то же. При их использовании где-то еще мы должны делать выбор, какую функцию
//вызвать:
int getDataFromDatabase()
{
    //получаем текущие настройки логирования
    bool logToFile = getLoggingOption();
    //подключаемся к базе данных
    if (logToFile && connectToDatabaseFile("John Smith", "12345")) {
        return dataBase.getParameter("parameterName");
    }
    if (!logToFile && connectToDatabase("John Smith", "12345")) {
        return dataBase.getParameter("parameterName");
    }
}
//Налицо значительное дублирование кода. Весь этот код можно сократить, если написать
//функцию connectToDatabase таким образом, чтобы она ничего не знала, в какой поток
//требуется отправлять лог. Для этого она дополнительным аргументом будет принимать
//поток вывода:
bool connectToDatabase(std::string &name, std::string &password, std::ostream &out)
{
    //действия, осуществляющие подключение
    if (connectTo(name, password)) {
        out << "User "<<name<<" connected\n";
        return true;
    }

    out << "Failed to connect for user "<<name<<"\n";
    return false;
}
//а создание потока логирования осуществляется в другом месте
int getDataFromDatabase1()
{
    //получаем текущие настройки логирования
    bool logToFile = getLoggingOption();
    //переменная f - это глобальная переменная типа std::ofstream, создаваемая где-то еще
    if (connectToDatabaseFile("John Smith", "12345", logToFile ? f : std::cout))
        return dataBase.getParameter("parameterName");
}

//Наиболее общий класс для всех потоков вывода - это класс std::ofstream. Этот тип должен
//быть указан в сигнатуре функции, принимающей поток. Кроме того, поток всегда передается
//в функцию по ссылке.
//Наиболее общий класс для всех потоков ввода - это класс std::ifstream. Этот тип должен
//быть указан в сигнатуре функции, принимающей поток. Кроме того, поток всегда передается
//в функцию по ссылке.



//Задания на функции:
//1. Напишите функцию copyChar, которая принимает один аргумент - поток ввода
//   и из этого потока читает один символ и отправляет этот символ в консоль.
//2. Напишите функцию copyLine, которая принимает один аргумент - поток ввода
//   и из этого потока читает одну строку и отправляет эту строку в консоль.
//3. Напишите функцию sendLine, которая принимает один аргумент - поток вывода,
//   читает из консоли строку символов и отправляет эту строку в поток вывода.
//4. Напишите функцию с двумя аргументами - названиями входного и выходного
//   текстовых файлов. Функция должна копировать содержимое входного файла
//   в выходной файл, заменяя все гласные 'aeiou' на подчеркивания '_'.



//Форматирование потока
//-------------------

void useFormatting()
{
    //Для задания форматирования используется функция setf(), для отмены опции - 
    //unsetf().
    auto &out = std::cout;

    //1. При выводе вещественных чисел удобно задавать:
    //- количество знаков после запятой:
    out.precision(2); //2 знака после запятой (в некоторых компиляторах две значащие цифры в числе)
    //- формат вывода числа:
    out.setf(std::ios::fixed); //вывод чисел в "фиксированном" формате (2.21 или 0.00032)
    out.setf(std::ios::scientific); //вывод чисел в "экспоненциальном" формате (2.21e0 или 3.2e-2)
    //- вывод разделительной точки
    out.setf(std::ios::showpoint); //всегда выводить точку, даже если нет дробной части (2.)
    out.unsetf(std::ios::showpoint); //не выводить точку у чисел без дробной части (2)
    //- вывод плюса
    out.setf(std::ios::showpos); //всегда выводить +, даже если число положительное (+2.21)
    out.unsetf(std::ios::showpos); //выводить только минус у отрицательных чисел (-2.21)

    //2. При вводе/выводе целых чисел можно задать:
    //- основание счисления для числа
    out.setf(std::ios::dec, std::ios::basefield); //следующее число/числа будут прочитаны/записаны в десятичной системе счисления
    out.setf(std::ios::hex, std::ios::basefield); //следующее число/числа будут прочитаны/записаны в 16-ричной системе счисления
    out.setf(std::ios::oct, std::ios::basefield); //следующее число/числа будут прочитаны/записаны в 8-ричной системе счисления
    //- вывод плюса
    out.setf(std::ios::showpos); //всегда выводить +, даже если число положительное (+221)

    //3. Можно задавать количество символов, отводимое под содержимое переменной:
    out.width(5); //под следующую переменную будет выделено 5 символов.
    out << 2; //в потоке вывода окажется строка "     2";
    //Замечание: метод width действует только на одну команду вывода. Следующее число будет
    //выведено уже по общим настройкам

    //- выравнивание вывода
    out.setf(std::ios::left); //задаёт выравнивание по левому краю
    out.setf(std::ios::right); //задаёт выравнивание по правому краю

    //- изменение символа-заполнителя (по умолчанию используется пробел)
    out.width(4); out << 2; //будет выведена строка "   2"
    out.fill('0'); out.width(4); out << 2; //будет выведена строка "0002";
    out.fill('0'); out.width(4); out.setf(std::ios::left); out << 2; //будет выведена строка "2000";


    //Любой флаг можно отключить методом unsetf:
    out.unsetf(std::ios::oct);

    //Отступление: почему "флаг" и как они задаются
}

//Манипуляторы потока
//------------------

//Манипуляторы потока облегчают задание форматирования, так как манипуляторы
//"встраиваются" в поток и не требуют запоминания названия флагов.
//Чтобы использовать манипуляторы потока, подключите заголовочный файл <iomanip>

void useManip()
{
    auto &out = std::cout;

    //Манипулятор - это специальный объект, отправляемый в поток ввода или вывода,
    //который используется только для настройки формата ввода/вывода. Манипуляторы
    //добавляют возможности форматирования и дополняют флаги и методы потока.

    //Манипулятор ширины поля
    out << std::setw(4) << 3 << 4 << 5;
    //Манипулятор количества знаков после запятой
    out << std::setprecision(2) << 21.2;
    //Манипулятор системы счисления
    out << std::setbase(10) << 20 << std::setbase(16) << 20 << std::setbase(8) << 20;
    out << std::hex << 20 << std::oct << 20 << std::dec << 20;
    //Манипулятор, изменяющий символ-заполнитель
    out << std::setfill('_') << std::setw(4) << 2; //будет выведена строка символов "___2"
    //Манипулятор отображения знака числа
    out << std::showpos << 27; // +27
    out << std::noshowpos << 27; //27
    //Манипулятор использования верхнего регистра
    out << std::hex << std::uppercase << 27; //выведет 1B
    out << std::hex << std::nouppercase << 27; //выведет 1b
    //Манипуляторы выравнивания
    out << std::left << std::setw(10) << -124; //выведет "-124      "
    out << std::right << std::setw(10) << -124; //выведет "      -124"
    out << std::internal << std::setw(10) << -124; //выведет "-      124"
}

//Задания:
//5. Напишите программу, которая читает текстовый файл, содержащий вещественные числа
//   (разделенные пробелами или разрывами строк) и выводит в консоль среднее арифметическое
//   чисел, стандартное отклонение, а также минимальное и максимальное значения.
//   стандартное отклонение - это квадратный корень из среднего следующих величин:
//   (x1-a)^2, (x2-a)^2, (x3-a)^2..., где а - среднее арифметическое.
//6. Напишите программу, которая выдает в консоль случайные цитаты. Цитаты сохранены
//   в отдельном текстовом файле. При запуске программы пользователю задается вопрос
//   - показать ли еще цитату? Если пользователь вводит Y или y или Yes или yes,
//   то в консоль выводится цитата из случайной строки файла. Если пользователь вводит
//   что угодно другое, то программа завершается.
//7. Написать программу, которая при каждом запуске добавляет в файл новую строку
//   с увеличивающимся на 1 числом-счетчиком. Начальное значение счетчика - число 0
//8. Напишите программу, которая читает текстовый файл и выводит в терминал встречаемость
//каждого слова.
//9. Напишите программу, которая читает из файла список вещественных чисел и выводит
//   их в консоль в одну колонку с выравниванием по точке. Например, если в файле записаны числа
//   -2 34.56 0.004 10004.012
//   то в консоль они должны быть выведены как
//   -2.00
//   34.56
//    0.00
//10004.01
//   Программа должна спрашивать, сколько знаков после запятой выводить и нужно ли всегда
//   выводить знак числа.

//Проекты

//1. Напишите программу, которая генерирует спам. В отдельном текстовом файле содержится текст
//   письма. В тексте письма символами #N# обозначено имя получателя письма. Напишите программу,
//   которая:
//   а) считывает из консоли список имен (и фамилий) людей, которым будет разослан спам
//   б) для каждого ФИО создает отдельный текстовый файл (название может быть произвольным),
//   текст которого берется из шаблона, но символы #N# заменены на имя и фамилию человека.

//2. Часто используемая команда more позволяет пользователям Linux выводить в консоль
//   файл небольшими порциями. Напишите программу, которая выводит первые 10 строк файла
//   и запрос пользователю продолжить вывод следующей порции.
//   При запуске программа должна спрашивать название файла.
//   Второй вариант программы - использовать аргументы запуска программы.  См. файл main.h

//3. Напишите программу, которая нумерует строки текстового файла. Перед каждой строкой
//   файла добавьте ее номер (начиная с 1) и как минимум один пробел. Ширина вставляемого
//   текста должна быть постоянной для всего файла. Это значит, что если в файле не более 9
//   строк, то к каждой строке добавляется ровно два символа - номер строки и пробел.
//   Если количество строк не превышает 99, то добавляется три символа - число и пробел.
//   И т.д.

//4. Напишите программу, которая создает диаграммы в формате svg на основе числовых данных из файла.
//   В текстовом файле записаны не более 10 вещественных чисел. Требуется для этих чисел
//   создать столбчатую диаграмму следующего вида:
//   - ширина и высота равны 400 px,
//   - высота столбцов диаграммы должна быть масштабирована, чтобы не превысить высоту в 400 px
//   - на диаграмме должны быть нарисованы оси координат простыми линиями без стрелок.
//   - все столбцы должны иметь одинаковую ширину и полностью заполнять ширину рисунка в 400 px
//   - между столбцами диаграммы должен быть промежуток, равный половине ширины столбца.
/*
Файл svg - это текстовый формат, в котором командами рисования записан векторный рисунок.
Самый простой файл svg выглядит так:
<svg viewBox="0 0 400 400">
  <rect x="20" y="20" width="50" height="250" style="fill:blue"/>
  <rect x="75" y="100" width="150" height="50" style="fill:red"/>
  <line x1="0" y1="0" x2="300" y2="300" style="stroke:purple;stroke-width:2"/>
</svg>
Этот код задает канву рисунка размером 400 на 400 с началом координат в точке (0,0).
Тег rect используется для рисования прямоугольников. Для прямоугольника задается
левый верхний угол, ширина и высота, а также стиль (в данном случае - заливка синим).
Тег line используется для рисования прямых линий. Для них задаются начальная и конечная точки
и стиль (в данном случае - цвет линии пурпурный и ширина линии 2).
*/

#endif // FILESTREAMS_H
