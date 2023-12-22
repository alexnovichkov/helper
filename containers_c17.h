#ifndef CONTAINERS_C17_H
#define CONTAINERS_C17_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/**
 * @brief eraseRemove
 * Правильное удаление элементов из вектора
 */
void eraseRemove()
{
    vector<int> v{1,2,3,4,2,5,6,7,2,8};

    //удаляем двойки из вектора
    const auto newEnd (remove(begin(v), end(v), 2)); //<- newEnd указывает на новый конец вектора
                                                     //   но элементы физически не удалились

    //укорачиваем вектор
    v.erase(newEnd, end(v));

    //уменьшаем емкость вектора
    v.shrink_to_fit();

    //или можно за один шаг: удаление нечетных элементов:
    v.erase(remove_if(begin(v), end(v), [](int i){ return i%2 !=0;}), end(v));
}

/**
 * @brief filterDuplicates
 * Отсеиваем повторяющиеся элементы из ввода пользователя
 */
#include <set>
#include <iterator>
void filterDuplicates()
{
    set<string> s;
    istream_iterator<string> it{cin};
    istream_iterator<string> end;

    copy(it, end, inserter(s, s.end()));

    for (const auto word : s) cout << word <<" ";
}


/**
 * @brief frequency
 * Частота встречаемости слов из текста
 */
#include <iomanip>

string removePunctuation(const string &s)
{
    const char *forbidden {".,:; \'\"[]{}()"};
    const auto idx_start (s.find_first_not_of(forbidden));
    const auto idx_end (s.find_last_not_of(forbidden));
    return s.substr(idx_start, idx_end - idx_start + 1);
}

void frequency()
{
    map<string, size_t> words;

    string s;
    while(cin >> s) {
        auto filtered (removePunctuation(s));
        ++words[filtered];
    }
    cout<<endl;
    for (auto &[word, count]: words) cout << word<<" "<<count<<endl;
    cout<<endl;
}


/**
 * @brief changeMapKeys
 * Изменение ключей элементов map без лишнего копирования и выделения памяти
 */
void changeMapKeys()
{
    map<int, string> m;

    //заполнение m

    //извлекаем элемент с ключом 3 без выделения памяти
    auto a (m.extract(3));

    //проверяем, что такой элемент был в мапе:
    if (!a.empty()) {
        //меняем значение ключа
        a.key() = 2;
        //вставляем обратно в мапу без выделения памяти
        m.insert(move(a));
    }
    else {
        cout <<"Trying to change non-existent element";
    }
}

#endif // CONTAINERS_C17_H
