#pragma once

#include <gtest/gtest.h>

#include "memory_tree.h"

namespace detail
{

class AvlTreeFixture : public ::testing::Test {
public:
    AvlTreeFixture() {
        m_size = CHUNK_SIZE;
    }

    void SetUp() override {
        addr = malloc(m_size);
        tree = new MemoryTree((size_t)addr);
        tree->assignTest(100, 93);
        tree->assignTest(600, 10);
        tree->assignTest(300, 3);
        tree->assignTest(700, 42);
        tree->assignTest(200, 42);
        tree->assignTest(400, 40);
        tree->assignTest(900, 42);
    }

    void TearDown() override {
        delete tree;
        free(addr);
    }

    ~AvlTreeFixture() override {
    }

    void* addr = nullptr;
    MemoryTree* tree;

private:
    size_t m_size;
    size_t m_count = POOL_SIZE;
};

TEST_F(AvlTreeFixture, create) {

    while (tree->root()) {
        printf("%zu\n", tree->root()->key);
        tree->free(tree->root()->key);
    }

    ASSERT_EQ(tree->size(), 0);

    tree->assignTest(1, 93);
    tree->assignTest(2, 10);
    tree->assignTest(3, 3);
    tree->assignTest(4, 42);
    tree->assignTest(5, 42);
    tree->assignTest(6, 40);
    tree->assignTest(7, 42);
    tree->assignTest(8, 8);
    tree->assignTest(9, 23);
    tree->assignTest(10, 235);

    ASSERT_EQ(tree->root()->key, 4);
    ASSERT_EQ(tree->root()->left->key, 2);
    ASSERT_EQ(tree->root()->left->left->key, 1);
    ASSERT_EQ(tree->root()->left->right->key, 3);
    ASSERT_EQ(tree->root()->right->key, 8);
    ASSERT_EQ(tree->root()->right->left->key, 6);
    ASSERT_EQ(tree->root()->right->left->left->key, 5);
    ASSERT_EQ(tree->root()->right->left->right->key, 7);
    ASSERT_EQ(tree->root()->right->right->key, 9);
    ASSERT_EQ(tree->root()->right->right->right->key, 10);
}

TEST_F(AvlTreeFixture, remove) {
    ASSERT_EQ(tree->size(), 7);

    tree->free(600);
    ASSERT_EQ(tree->size(), 6);

    auto root = tree->get(700);
    ASSERT_EQ(root->key, 700);
    ASSERT_EQ(root->size, 42);
    ASSERT_EQ(root->parent, tree->get(300));
    ASSERT_EQ(root->left, tree->get(400));
    ASSERT_EQ(root->right, tree->get(900));

    tree->free(700);
    ASSERT_EQ(tree->size(), 5);
}

} // namespace detail