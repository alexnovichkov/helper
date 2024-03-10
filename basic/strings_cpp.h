#ifndef STRINGS_CPP_H
#define STRINGS_CPP_H

#include <string> //для строк C++
#include <cstring> //для строк C
#include <iostream>
#include <cctype>

#include <locale>
#include <windows.h>
/**
 * @brief fromOEM конвертирует строку, полученную из консоли, в кодировку системы
 * @param str - строка, прочитанная из cin
 * @return строку в кодировке системы
 */
std::string fromOEM(std::string str)
{
    char buf[256];
    OemToCharA(str.c_str(), buf);
    return std::string(buf);
}

/**
 * @brief cstrings - примеры работы со строками C
 */
void cstrings() {
// C-strings - это массивы символов char, заканчивающиеся нулевым символом \0

//Объявление
    char str[10];
    //char bad_str[]; <- запрещено - требуется указать размер строки

//Инициализация
    char str1[] {"abcde"}; //без явного указания длины, добавляет \0 в конец строки
    char str2[20] {"abcde"}; //с указанием максимальной длины, добавляет \0 в конец строки
    char str3[] {'a', 'b', 'c', 'd', 'e'}; //задание списком символов, не добавляет \0 в конец строки

//Присвоение
    //Так как С-строка - это массив, то обычное присвоение невозможно:
    char str4[6];
    //str4 = "fgh"; <- запрещено

    //Требуется использовать функцию strcpy или strncpy
    strcpy(str4, "fgh"); //не проверяет на превышение длины str4
    strncpy(str4, "fgh", 5); //копируем максимум 5 символов, оставляя место под \0

    char anotherStr[] {"01234567"}; //длина anotherStr = 9
    strcpy(str4, anotherStr); //ошибка! str4 короче чем anotherStr
    strncpy(str4, anotherStr, 5); //OK, копируем максимум 5 символов

//Сравнение строк
    //Так как С-строка - это массив, то обычное сравнение невозможно:
    bool equal = str1==str2; //вернет false, хотя содержимое одинаково
    //Требуется использовать функцию strcmp
    //возвращает 0, если строки одинаковы
    //           отриц.число, если первая строка меньше второй
    //           полож.число, если первая строка больше второй
    int compareResult = strcmp(str1, str2); //вернет 0
    compareResult = strcmp("abc", "abd"); //вернет -1
    //Правильное использование strcmp в условиях:
    if (strcmp(str1, str2)==0) {//если строки равны
    }

//Другие функции для работы с C-строками:

//Конкатенация строк
    //добавляет строку src в конец строки dest и возвращает указатель на dest
    //не осуществляет никаких проверок - небезопасна
    //char* strcat(char* dest, char* src)
    //добавляет максимум n символов строки src в конец строки dest и возвращает указатель на dest
    //char* strncat(char* dest, char* src, size_t n)
    //
    char str5[10] {"abc"}; //str5 = {'a','b','c','\0',? ,? ,?, ?, ?, ?}

    char str6[] {"def"}; //str6 = {'d','e','f','\0'}
    strcat(str5, str6); //str5 = {'a','b','c','d','e','f','\0', ?, ?, ?}
    //strcat(str5, "ghij"); //ошибка! нет места для завершающего \0
    strncat(str5, "ghij", 10-strlen(str5)-1); //безопасно, присоединяем максимум 3 символа

//Определение длины строки
    //size_t strlen(char* str); - возвращает длину строки, не включая конечный \0
    //                            небезопасна, если в строке нет конечного \0
    strlen(str5) == 9;
    strlen(str6) == 3;
    strlen(str3) == 5; //не гарантировано, может выдать всё, что угодно

    //size_t strnlen(char* str, size_t max_count); - возвращает длину строки, но не
    //                                               более max_count

    strnlen(str3, 5) == 5; //возвращает true

//Поиск в строке
    //char* strchr(const char *s, int val)
    //возвращает указатель на первое вхождение символа val в строку s
    //или нулевой указатель

    //char* strrchr(const char *s, int val)
    //возвращает указатель на последнее вхождение символа val в строку s
    //или нулевой указатель

    //size_t strcspn(const char *s, const char *c)
    //возвращает длину подстроки s (с начала строки), в которой не встречается ни
    //один символ, входящий в c

    //char * strpbrk(const char *s, const char *c)
    //возвращает указатель на первое вхождение любого символа из строки c внутри строки s
    //или нулевой указатель, если вхождение отсутствует

    //size_t strspn(const char *s, const char *c)
    //возвращает длину подстроки s (с начала строки), которая состоит только из символов
    //входящих в с

    //char * strstr(const char *str, const char *substr)
    //возвращает указатель на первое вхождение подстроки substr в строку str
    //или нулевой указатель

    //char * strtok(char * str,const char * delim)
    //возвращает указатель на следующую лексему в строке str, отделенную от предыдущей
    //лексемы любым из символов, содержащихся в строке delim
    //или нулевой указатель, если лексемы закончились
    char line[] = "One, two, and three";
    char *p = strtok(line, ",. ");
    printf(p); //p=="One"
    do {
        p = strtok(0, ",. "); //первым параметром передаем 0, чтобы продолжать итерировать
                              //с того места, где остановились
        if (p) printf("|%s",p);
    } while (p);
    //One|two|and|three

//Передача в функцию
    //Строка C передается в функцию через указатель на первый символ (или не первый символ,
    //а тот, с которого требуется обработать строку)
    //Если строка гарантированно включает нулевой символ, то можно передать только указатель
    // int countLetters(char *str) {
    //      int result = 0;
    //      while (str) {
    //         if (isalpha(*str)) result++;
    //         str++; //передвигаем указатель на следующий символ
    //      }
    //      return result;
    // }

    //Но безопаснее передавать также длину строки
    // int countLetters(char *str, int len) {
    //      int result = 0;
    //      char *s = str; //запоминаем указатель на первый символ
    //      while (str && (str-s < len)) {
    //         if (isalpha(*str)) result++;
    //         str++; //передвигаем указатель на следующий символ
    //      }
    //      return result;
    // }
//Возвращение из функции
    //Аналогично возвращению динамического массива
}

/**
 * @brief cppstrings - примеры работы с классом std::string
 */
void cppstrings()
{
    //C++ строки - это экземпляры класса std::string
    //Их использование позволяет решить множество проблем, возникающих с обычными 
    //символьными массивами (копирование, уничтожение, определение длины, передача 
    //в функцию и т.д.). Основные преимущества использования строк std::string: 
    //1. Переменные типа std::string автоматически уничтожаются (освобождают память)
    //   при выходе из области видимости. Это позволяет забыть о ручном управлении
    //   памятью. 
    //2. Для переменных std::string переопределены операторы >>, <<, +, >, <, ==, 
    //   позволяющие легко соединять строки в одну длинную и использовать строки 
    //   со стандартными потоками ввода/вывода.
    //3. Класс std::string с небольшими изменениями легко приспособить к эффективной
    //   работе с мультибайтными кодировками (для многоязыковой программы), что в 
    //   случае использования строк C потребовало бы значительных усилий.
    //4. 


    //Для использования строк std::string в программе необходимо подключить заголовочный
    //файл <string>.



    //Объявление, инициализация и присвоение
    //--------------------------------------
    //Для объявления строки достаточно указать тип переменной std::string:

    std::string s; //пустая строка
    std::string s1 {"abc"}; //строка с начальным значением
    std::string s2 = "abc"; //то же, что и выше

    //Строки очень легко копировать между собой:

    std::string s3 = s1; //объявление строки s3 и инициализация строкой s1

    //Чтобы скопировать одну строку в другую, просто используйте оператор присваивания:
    s = s1; //копирование строк

    //Работа с отдельными символами
    //-----------------------------

    //Строки всё ещё можно рассматривать как контейнер (массив) символов. Индексация
    //символов начинается с 0. Тип отдельного элемента строки - char.

    //Для обращения к отдельным символам строки используйте оператор []

    s[0] = 'A'; //s="Abc", не проверяет выход за границы

    //или метод at() (теоретическая вставка про методы)

    s.at(0) = 'A'; //то же самое, но сгенерирует исключение при попытке обратиться к символу
                   //за границами строки (теоретическая вставка про обработку ошибок)
    //Работать с методом at() следует так:
    try {
        s.at(3) = 'x';
    }
    catch (std::out_of_range const& exc) {//перехватываем исключение, если строка s имеет длину
                                          //меньше 4 
        std::cout << "Error! " << exc.what() << '\n';
    }
    //Если вы используете оператор [], проверка выхода за границы строки не производится,
    //поэтому проверку следует проводить до вызова оператора:
    if (s.length()>=4) 
        s[3] = 'x';
    else {
        std::cout << "Error! " << '\n';
    }

    //Оператор [] и метод at() позволяют как читать значение отдельного символа, так
    //и менять его, так как они оба возвращают ссылку на i-й символ строки.

    //Конкатенация строк
    //------------------

    //Конкатенация строк - это сцепление строк в одну длинную.

    //Оператор + позволяет соединять вместе строковые переменные, а также строки со
    //строковыми литералами.
    s2 = "def";
    s = s1+s2; //s="abcdef"
    s = "ABC"+s+"DEF"; //s="ABCabcdefDEF"

    //Оператором + можно соединять также строки и отдельные символы:
    s += 'g'; //s="ABCabcdefDEFg"
    s += s2[0]; //s="ABCabcdefDEFgd"

    //При использовании оператора + можно не беспокоиться о том, что в целевой строке 
    //не хватит выделенного места под все символы, так как класс std::string сам
    //выделяет и освобождает память.

    //Сравнение строк
    //---------------

    //Для класса std::string переопределены все булевы операторы сравнения: == != < > <= >=
    //Это позволяет эффективно использовать строки в условиях.
    bool equal = s1==s2; //false
    equal = s1==s3; //true

    //Неравенство строк определяется лексикографически: 
    std::string("A") < std::string("B"); //алфавитный порядок
    std::string("B") < std::string("b"); //символ 'B' имеет меньший код
    std::string("a") < std::string("aa"); //менее длинная строка считается меньшей


    //Чтение строки из потока
    //-----------------------

    //Переопределенный оператор >> прочитает все символы из потока ввода до первого
    //попавшегося пробельного символа (пробела, табуляции, перевода строки) и остановится.
    //Поэтому он не годится, если требуется поместить в переменную типа std::string
    //строку из нескольких слов:

    //Для строки "Mary ate an apple", введенной без кавычек в консоль, выражение
    std::string s;
    std::cin >> s; 
    //поместит в переменную s только первое слово (s == "Mary"). 

    //Поэтому для чтения всей строки из потока ввода необходимо использовать функцию

    getline(std::cin, s); //прочитает всю строку до символа перевода строки, включая 
                          //все пробелы и перевод строки
    //Первый аргумент функции - поток ввода, из которого нужно прочитать строку,
    //второй аргумент - переменная, в которую нужно поместить результат.
    //Если в функцию getline() передать третий аргумент lim типа char, то getline()
    //прочитает все символы вплоть до символа lim. По умолчанию lim=='\n'. 

    //Заметьте также, что с помощью >> невозможно прочитать из потока пробельный символ,
    //так как он просто будет проигнорирован. То есть, если необходимо проигнорировать
    //перевод строки, то придется прибегать к ухищрениям:

    void newLine()
    {
        using namespace  std;
     
        char nextChar;
        do {
            cin.get(nextChar);
        } while (nextChar != '\n');
    }

    int main( )
    {
        using namespace std;
     
        string firstName, lastName, recordName;
        string motto = "Your records are our records.";
        cout << "Enter your first and last name:\n";
        cin >> firstName >> lastName;
        newLine();
        recordName = lastName + ", " + firstName;
        cout << "Your name in our records is: ";
        cout << recordName << endl;
        cout << "Our motto is\n"
             << motto << endl;
        cout << "Please suggest a better (one-line) motto:\n";
        getline(cin, motto);
        cout << "Our new motto will be:\n";
        cout << motto <<endl;
        return 0;
    }

    //Зметьте, что после чтения имени и фамилии cin >> firstName >> lastName; нам 
    //пришлось вызвать функцию newLine(), чтобы убрать ("проглотить", пропустить) 
    //перевод строки. Если мы этого не сделаем, то следующее чтение из потока
    //начнется прямо перед переводом строки, а так как далее мы вызываем функцию
    //getline(), то она вернет пустую строку. Попробуйте вставить две функции выше
    //в пустой проект и запустите программу. Затем удалите вызов newLine() и еще
    //раз запустите программу. 


    //Запись строки в поток:
    //----------------------

    //Запись строк в поток проста и не имеет подводных камней:

    std::cout << s;


    //Манипуляции со строками производятся с помощью методов класса string
    //--------------------------------------------------------------------
    
    //Длину строки можно узнать с помощью метода length(), возвращающего целое беззнаковое
    //число типа size_t (то же, что unsigned int)
    size_t len = s.length();         // Длина строки, len=12

    //Подстроку можно извлечь методом substr. Первый аргумент - индекс символа,
    //второй аргумент - количество символов (длина подстроки)
    std::string sub = s.substr(1, 4); //sub = "BCab";

    //Проверить является ли строка пустой:
    bool isEmpty = sub.empty(); //false

    //Вставить подстроку в нужное место строки - метод insert(pos, s). Первый аргумент - 
    //индекс вставки, второй - строка, которую нужно вставить.
    sub.insert(4, "123"); //sub = "BCab123";

    //Удалить часть строки: erase(size_type index, size_type count)
    sub.erase(5, 1); //sub = "BCab13"; удален 1 символ начиная с позиции 5

    //Поиск в строке искомой подстроки
    int pos = s.find(sub); //pos=
    //Метод find() вернет -1, если подстрока sub не найдена, или индекс символа, с которого
    //подстрока начинается в строке.

    //Метод rfind() позволяет осуществлять поиск подстроки, двигаясь от конца строки к началу:
    std::string text = "123 abc 321";
    int firstIndex = text.find("3"); //firstIndex == 2
    int lastIndex = text.rfind("3"); //lastIndex == 8

    //Поиск в строке любого символа из подстроки, первым встретившегося в строке
    pos = s.find_first_of(sub); //pos = 1 - найден символ 'B'

    //Конвертация в числа и обратно:
    s = "  123  ";
    int i = std::stoi(s); //пропускает все начальные пробелы, ищет число в строке и игнорирует
                        //все символы после числа
    long int li = std::stol(s); //также stoul
    long long int lli = std::stoll(s); //также stoull
    float f = std::stof(s);
    double d = std::stod(s);
    long double ld = std::stold(s);
    
    //Расширенные версии функций позволяют определять, где мы остановились после конвертации
    size_t *badChar = nullptr;
    s = " 123d   ";
    i = std::stoi(s, badChar); //
    if (badChar)
        std::cout << "Not a number at "<<(*badChar)<<" in "<<s;
    else
        std::cout << s <<" "<<i<<std::endl;

    //При попытке сконвертировать не число будет сгенерировано исключение, которое необходимо перехватить,
    //иначе программа завершится аварийно
    std::string badString = " _78";
    try {
        i = std::stoi(badString);
    } catch (const std::invalid_argument &arg) {
        std::cout <<arg.what()<<std::endl; //выведет "stoi"
    }
    //обратно:
    std::string sFloat = std::to_string(123.45e-4);


    //Альтернативный способ конвертации строки в число - это использование строкового
    //потока stringstream:
    #include <sstream>
    std::stringstream convert{s};
    int i=0;
    if (!(convert >> i)) {
        //сигнализируем, что конвертация не удалась
    }

    //При конвертации строки в число с помощью stringstream действуют все правила
    //работы с потоками.


    //Вывод русских символов в консоль:
    setlocale(0, ""); //в начале main
    std::wcout << L"Введите количество товаров: ";

    //Чтение русских символов из консоли
    std::string rusStr;
    std::cin >> rusStr;
    rusStr = fromOEM(rusStr);

    //Использование переменных std::string в функциях
    //-----------------------------------------------

    //Переменные типа std::string можно свободно передавать в функции как по значению,
    //так и по ссылке. При этом действуют все соответствующие механизмы:
    //- при передаче строки в функцию по значению в функции оказывается копия исходной
    //  строки.
    //- при передаче строки в функцию по ссылке в функцию передается исходная строка.

    //Возврат переменной из функции по значению также подчиняется общим правилам.
}

//Задания для проверки:
//1. При выполнении следующего кода:
    string s1, s2;
    cout << "Enter a line of input:\n";
    cin >> s1 >> s2;
    cout << s1 << "*" << s2 << "<END OF OUTPUT";

//При вводе строки  "A string is a joy forever!" 
//какой окажется следующая строка вывода?

//2. При выполнении следующего кода:
    string s;
    cout << "Enter a line of input:\n";
    getline(cin, s);
    cout << s << "<END OF OUTPUT";

//При вводе строки  "A string is a joy forever!" 
//какой окажется следующая строка вывода?

//3.  При выполнении следующего кода:
    string s1, s2("Hello");
    cout << "Enter a line of input:\n";
    cin >> s1;
    if (s1 == s2)
        cout << "Equal\n";
    else  
        cout << "Not equal\n";

//При вводе строки  "Hello friend!" 
//какой окажется следующая строка вывода?

//4.  Что выведет следующий код?
    string s1, s2("Hello");
    s1 = s2;
    s2[0] = 'J';
    cout << s1 << " " << s2;



//Задания:
//5. Напишите функцию, заменяющую каждый n-й символ в строке s на символ ch.
//6. Напишите функцию, преобразующую целое положительное число x в строку s, представляющую
//   бинарную запись этого числа.
//   Дополнительно: Напишите обратную функцию.
//7. Напишите функцию, преобразующую строку вида "1234+56" в результат выполнения 
//   сложения. Числа в строке должны быть целые, пробелы в строке должны пропускаться.
//   Дополнительно: напишите функцию, которая понимает не только сложение, но и все
//   остальные арифметические операторы. 
//8. В классе std::string нет функции, приводящей строку к нижнему или верхнему регистру.
//    Напишите функцию toLower, возвращающую строку, приведенную к нижнему регистру.
//    Для перевода к нижнему регистру отдельных символов используйте функцию
//         int tolower(int) <- возвращает не char, а int
//9. Написать функцию, определяющую, является ли строка палиндромом. Строка должна
//   рассматриваться "как есть", то есть палиндромность определяется с учетом всех     
//   пробельных и пунктуационных символов, и с учетом регистра алфавитных символов.

//   Дополнительно: переписать функцию таким образом, чтобы она не учитывала наличие
//   пробельных и пунктуационных символов, а также игнорировала регистр букв.    
//10. Написать функцию, проверяющую, являются ли две строки анаграммами друг друга.
//   Две строки являются анаграммами, если вторую строку можно получить перестановкой 
//   букв первой.
//11. Написать функцию, разбивающую данную строку на отдельные слова. Строка вводится 
//    в консоли целиком, затем отдельные слова выводятся каждое с новой строки.    

//    Дополнительно: Класс std::vector является безопасным аналогом обычных массивов.
//    Для его использования подключите заголовочный файл <vector>. Создать вектор строк
//    очень просто: необходимо явно указать в типе переменной, что вы хотите хранить
//    строки:
    std::vector<std::string> words;
//    Добавить элемент к вектору можно с помощью метода push_back()
    words.push_back("first");
//    Используя знания о классе std::vector, перепишите функцию задания 11 таким образом,
//    чтобы она не выводила в консоль отдельные слова, а возвращала вектор этих слов.

//12. Напишите функцию, принимающую время в формате "hh:mm:ss PM/AM" (12-часовой формат)
//    и возвращающую время в формате  "hh:mm:ss" (24-часовой формат)
//    Пробел перед PM или AM может отсутствовать, а сами буквы могут быть строчные.
//    Пример: строка "01:04:13 PM" должна преобразовываться в "13:04:13", а строка
//    "01:04:13am" должна преобразовываться в "01:04:13"   
//13. Напишите функции, возвращающие первое слово в строке и последнее слово в строке.
//    Все пробельные символы и пунктуация должны игнорироваться. 
//14. Напишите функцию, которая нормализует регистр фразы. Слова после .?! должны
//    начинаться с заглавной буквы, все остальные буквы должны быть строчные. 
//    Игнорируйте имена.
//15. Напишите функцию, возвращающую количество вхождений подстроки в строку.

#endif // STRINGS_CPP_H
