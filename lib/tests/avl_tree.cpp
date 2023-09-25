#include "avl.h"
#include <cstddef>
#include <exception>
#include <gtest/gtest.h>

class AvlTreeFixture : public ::testing::Test {
  public:
    AvlTreeFixture() { size = sizeof(Node) * count; }

    void SetUp() override {
        addr = malloc(size);
        tree = new MemoryTree(addr, size);
        tree->Insert(100, 93);
        tree->Insert(600, 10);
        tree->Insert(300, 3);
        tree->Insert(700, 42);
        tree->Insert(200, 42);
        tree->Insert(400, 90);
        tree->Insert(900, 42);
    }

    void TearDown() override {
        delete tree;
        free(addr);
    }

    ~AvlTreeFixture() override {}

    void *addr = nullptr;
    MemoryTree *tree;

  private:
    size_t size;
    size_t count = 1024;
};

TEST_F(AvlTreeFixture, create) {

    auto root = tree->GetNode(300);
    ASSERT_EQ(root->key, 300);
    // ASSERT_EQ(root->size, 3);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->left, tree->GetNode(100));
    ASSERT_EQ(root->right, tree->GetNode(600));

    auto tail = tree->GetNode(900);
    ASSERT_EQ(tail->key, 900);
    // ASSERT_EQ(tail->size, 42);
    ASSERT_EQ(tail->parent, tree->GetNode(700));
    ASSERT_EQ(tail->left, nullptr);
    ASSERT_EQ(tail->right, nullptr);
}

TEST_F(AvlTreeFixture, remove) {
    tree->DelNode(600);
    auto root = tree->GetNode(700);
    ASSERT_EQ(root->key, 700);
    // ASSERT_EQ(root->size, 42);
    ASSERT_EQ(root->parent, tree->GetNode(300));
    ASSERT_EQ(root->left, tree->GetNode(400));
    ASSERT_EQ(root->right, tree->GetNode(900));
}
