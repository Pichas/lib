#include "settings.h"
#include <gtest/gtest.h>

struct Sky {
    int color;
    Sky() : color(0) {}
    Sky(int color) : color(color) {
        std::cout << "***********************************constr int: "
                  << __LINE__ << " " << __FILE__ << std::endl;
    }
    Sky(const Sky &color) : color(color.color) {
        std::cout << "***********************************copy: " << __LINE__
                  << " " << __FILE__ << std::endl;
    }
    Sky(Sky &&color) : color(std::move(color.color)) {
        std::cout << "***********************************move: " << __LINE__
                  << " " << __FILE__ << std::endl;
    }
};

struct Fog {
    Fog(int val) : color(val) {}
    int color;
};

TEST(ent, createDefault) {
    Entity s;
    s.createComponent<Fog>(12);
    s.createComponent<Sky>();

    auto f = s.getComponent<Fog>();
    f.color = 22;

    s.getComponent<Sky>().color = 42;

    {
        const auto &fog = s.getComponent<Fog>();
        const auto &sky = s.getComponent<Sky>();

        ASSERT_EQ(fog.color, 12);
        ASSERT_EQ(sky.color, 42);
    }

    {
        const auto &sky = s.getComponent<Sky>();
        s.createComponent<Sky>();
        const auto &sky2 = s.getComponent<Sky>();

        ASSERT_EQ(&sky, &sky2);
    }
}

TEST(ent, createWithParam) {
    Entity s;
    Sky sky(42);
    s.createComponent<Sky>(sky);

    {
        auto sky = s.getComponent<Sky>();
        ASSERT_EQ(sky.color, 42);
    }
}