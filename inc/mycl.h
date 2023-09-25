#pragma once
#include <iostream>
#include <concepts>
#include <functional>


struct A{

    bool isAlive = true;

    int x = 0;

    A(int i) : x(i) {
        std::cout << "constr int: " << x << " - " << __LINE__ << " " << __FILE__ << std::endl;
    }

    A(){
        std::cout << "constr: def" << __LINE__ << " " << __FILE__ << std::endl;
    }
    A(const A& a) : x(a.x) {
        std::cout << "copy: " << x << " - " << __LINE__ << " " << __FILE__ << std::endl;
    }
    A(A&& a): x(a.x){
        a.x = 0;
        std::cout << "move: " << x << " - " << __LINE__ << " " << __FILE__ << std::endl;

    }

    virtual ~A(){
        std::cout << "destr: " << x << " - " << __LINE__ << " " << __FILE__ << std::endl;
        isAlive = false;
    }

    virtual void f(){

    }
    //decltype(auto) operator<=>(const A<T>&) const = default;
    

    operator float() const{
        return x;
    }

};





// template<class... T>
// requires ((std::signed_integral<T> || std::floating_point<T>) && ...)
// static bool f(const std::array<T, 3>&... arr) {
//     return ((std::abs(arr[0]) > 1024) || ...);
// }

// template <class T>
// requires std::derived_from<typename T::type, A<typename T::type>>
// void print(T& o){
//    std::invoke(&T::print, o);
// }