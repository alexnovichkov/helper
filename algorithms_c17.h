#ifndef ALGORITHMS_C17_H
#define ALGORITHMS_C17_H

#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>

// копирование содержимого контейнера в поток вывода
void print()
{
//    auto shell_it(std::ostream_iterator<std::pair<int, std::string>>{std::cout, ", "});

//    std::map<int, std::string> container;

//    std::copy(begin(container), end(container), shell_it);
}

// копирование данных из вектора в map
void copyToMap()
{
    std::map<int, std::string> container;
    std::vector<std::pair<int, std::string>> vec;

    std::copy(begin(vec), end(vec), std::inserter(container, begin(container)));
}

#endif // ALGORITHMS_C17_H
