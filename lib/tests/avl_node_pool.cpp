#include "avl.h"
#include <exception>
#include <gtest/gtest.h>

class AvlNodePoolFixture : public ::testing::Test {
  public:
    AvlNodePoolFixture() { size = sizeof(Node) * count; }

    void SetUp() override {
        addr = malloc(size);
        np = new NodePool(addr, size);
    }

    void TearDown() override {
        delete np;
        free(addr);
    }

    ~AvlNodePoolFixture() override {}

    void *addr = nullptr;
    size_t count = 1024;
    NodePool *np;

  private:
    size_t size;
};

TEST_F(AvlNodePoolFixture, create) {
    auto node_1 = np->GetNewNode();

    ASSERT_EQ((Node *)addr, node_1)
        << "first node should have the first addr of memory";

    auto node_2 = np->GetNewNode();

    ASSERT_EQ((Node *)addr + 1, node_2)
        << "second node should have start the second addr of memory";

    auto node_3 = np->GetNewNode();

    ASSERT_EQ((Node *)addr + 2, node_3)
        << "second node should have start the second addr of memory";
}

TEST_F(AvlNodePoolFixture, remove) {
    auto node_1 = np->GetNewNode();
    auto node_2 = np->GetNewNode();

    np->RemoveNode(node_1);
    auto node_3 = np->GetNewNode();

    ASSERT_EQ((Node *)addr, node_3)
        << "third node should have the first  addr of memory";
}

TEST_F(AvlNodePoolFixture, out_of_memory) {
    for (size_t i = 0; i < count; ++i) {
        np->GetNewNode();
    }
    try {
        np->GetNewNode();
        FAIL() << "Expected std::out_of_range";
    } catch (std::out_of_range const &err) {
        EXPECT_EQ(
            err.what(),
            std::string("Node pool is FULL -> OUT OF MEMORY, buy MORE MEMORY"));
    } catch (...) {
        FAIL() << "Expected std::out_of_range";
    }
}