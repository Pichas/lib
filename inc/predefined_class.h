#pragma once
#include <concepts>
#include <functional>
#include <iostream>


struct A {

    bool is_alive = true;

    int x = 0;

    A(int i) : x(i) {
        std::cout << "constr int: " << x << " - " << __LINE__ << " " << __FILE__ << std::endl;
    }

    A() {
        std::cout << "constr: def" << __LINE__ << " " << __FILE__ << std::endl;
    }
    A(const A& a) : x(a.x) {
        std::cout << "copy: " << x << " - " << __LINE__ << " " << __FILE__ << std::endl;
    }
    A(A&& a) : x(a.x) {
        a.x = 0;
        std::cout << "move: " << x << " - " << __LINE__ << " " << __FILE__ << std::endl;
    }

    virtual ~A() {
        std::cout << "destr: " << x << " - " << __LINE__ << " " << __FILE__ << std::endl;
        is_alive = false;
    }

    operator float() const {
        return x;
    }
};
