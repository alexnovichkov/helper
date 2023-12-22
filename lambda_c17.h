#ifndef LAMBDA_C17_H
#define LAMBDA_C17_H

#include <iostream>

//синтаксис:
//    [capture](parameters)
//            mutable
//            constexpr
//            -> T
//    {
//        body
//    }


/**
 * конкатенатор лямбда-функций
 * возвращает f(g(h(params))), params передаются извне
 */
template <typename T, typename...Ts>
auto concat(T t, Ts...ts)
{
    if constexpr (sizeof...(ts)>0) {
        return [=](auto ...params) {
            return t(concat(ts...)(params...));
        };
    }
    else {
        return [=](auto ...params) {
            return t(params...);
        };
    }
}

//использование конкатенатора функций
void useConcat()
{
    //три унарные лямбда-функции
    auto twice ([](int i){return i*2;});
    auto thrice([](int i){return i*3;});
    auto tenTimes([](int i){return i*10;});

    //вспомогательная функция, комбинирующая наши
    auto combined (concat(twice, thrice, tenTimes));

    std::cout<<combined(1)<<std::endl; // = 1*10*3*2 = 60

    //без вспомогательной функции:
    std::cout<<concat(twice, thrice, tenTimes)(1)<<std::endl;
}

/**
 *  for_each применяет функцию f ко всем аргументам
 */
template<typename F, typename ...Xs>
auto for_each(F f, Xs ...xs)
{
    (void)std::initializer_list<int> {
        ((void)f(xs), 0)...
    };
}

/**
 * multicall вызывает все переданные функции по очереди и применяет их к внешнему аргументу
 */
template<typename ...Ts>
auto multicall(Ts...functions)
{
    return [=](auto x) {
        (void)std::initializer_list<int>{
            ((void)functions(x), 0)...
        };
    };
}


void lambda()
{
    //создание счетчика
    auto counter ([count=0]() mutable {
        return ++count;
    });

    counter(); //1
    counter(); //2
    counter(); //3

    for_each([](auto x){std::cout<<x<<std::endl;}, 1,2,3,4,5,6);

    auto square([](auto x){std::cout<< x*x<<std::endl;});
    auto makeDouble([](auto x){std::cout<< x*2<<std::endl;});

    for_each(multicall(square, makeDouble), 1,2,3);

}

#endif // LAMBDA_C17_H
