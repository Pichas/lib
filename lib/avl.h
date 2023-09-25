#pragma once

#include <exception>
#include <iostream>
#include <stdexcept>
#include <vcruntime.h>

struct Node final {
    Node() = delete;
    Node(const Node &) = delete;
    Node(Node &&) = delete;
    Node operator=(const Node &) = delete;
    Node operator=(Node &&) = delete;

    Node *left = nullptr;
    Node *right = nullptr;
    union {
        Node *parent = nullptr;
        Node *next;
    };

    size_t key = 0;
    size_t size = 0;
    int balance = 0;

  private:
    friend class NodePool;
    void reset(Node *n) {
        left = nullptr;
        right = nullptr;
        next = n;
        key = 0;
        size = 0;
        balance = 0;
    }
};

struct NodePool final {

    NodePool(void *memoryLocation, size_t memorySize)
        : m_nodes(static_cast<Node *>(memoryLocation)),
          memoryMaxSize(memorySize), m_next_free(m_nodes) {
        size_t i;
        for (i = 0; i < (memoryMaxSize / sizeof(Node)) - 1; ++i) {
            m_nodes[i].reset(&m_nodes[i + 1]);
        }
        m_nodes[i].reset(nullptr);
    }

    Node *GetNewNode() {
        if (!m_next_free)
            throw std::out_of_range(
                "Node pool is FULL -> OUT OF MEMORY, buy MORE MEMORY");
        auto cur = m_next_free;
        m_next_free = m_next_free->next;
        cur->reset(nullptr);
        return cur;
    }

    void RemoveNode(Node *node) {
        node->reset(m_next_free);
        m_next_free = node;
    }

  private:
    size_t memoryMaxSize = 0;
    Node *m_nodes = nullptr;
    Node *m_next_free = nullptr;
};

class MemoryTree final { // AvlReference;
  public:
    MemoryTree() : m_pool(NodePool((void *)1, 1)), m_root(nullptr) {
        Insert(0x01000000, 0); // start address
        Insert(0x01FFFFFF, 0); // end address //TODO: get max address
    }

    MemoryTree(void *memoryLocation, size_t memorySize)
        : m_pool(NodePool(memoryLocation, memorySize)), m_root(nullptr) {}

    void Insert(size_t key, size_t size); // malloc
    Node *GetNode(size_t key) { return FindNode(key); };
    void DelNode(size_t key) { Remove(FindNode(key)); }; // free
    void *Search(size_t size); // first address with requested size

    void PrintTree() const;

  private:
    int SetBalance(Node *node);
    int GetHeight(Node *node) const;
    void Rebalance(Node *node);
    void Rotate(Node *node);
    void LLR(Node *parent, Node *node);
    void LRR(Node *patent, Node *node, Node *child);
    void RRR(Node *parent, Node *node);
    void RLR(Node *patent, Node *node, Node *child);
    void Remove(Node *node);
    Node *FindNode(size_t key);
    void PrintTree(Node *node) const;

    class LNR {
        size_t counter = 0;
        size_t current = 0;
        Node *root = nullptr;

        Node *recursiveSearch(Node *node) {
            Node *result = nullptr;
            if (node->left)
                result = recursiveSearch(node->left);
            if (result)
                return result;
            if (counter == current)
                return node;
            counter++;
            if (node->right)
                result = recursiveSearch(node->right);
            return result;
        }

      public:
        LNR(Node *root) : root(root) {}
        Node *next() {
            counter = 0;
            auto result = recursiveSearch(root);
            current++;

            return result;
        }
    };

    NodePool m_pool;
    Node *m_root;
    int m_size;
};