#include <concepts>
#include <random>


const auto& rng = []() -> std::mt19937& {
    static std::mt19937 rng{std::random_device{}()};
    return rng;
};

template<std::integral T>
inline T dice(T min, T max) {
    std::uniform_int_distribution<T> uid(min, max);
    return uid(rng());
}

template<std::floating_point T>
inline T dice(T min, T max) {
    std::uniform_real_distribution<T> uid(min, max);
    return uid(rng());
}