#include "avl.h"

#include <cassert>
#include <cmath>
#include <corecrt_math.h>
#include <iostream>
#include <string>
#include <vcruntime.h>
#include <vector>

int MemoryTree::SetBalance(Node *node) {
    if (!node)
        return 0; // node is null?!
    int leftHeight = GetHeight(node->left);
    int rightHeight = GetHeight(node->right);
    node->balance = rightHeight - leftHeight;
    return node->balance;
}

int MemoryTree::GetHeight(Node *node) const {
    if (!node)
        return -1;
    return 1 + fmax(GetHeight(node->left), GetHeight(node->right));
}

void MemoryTree::Rebalance(Node *node) {
    while (node) {
        SetBalance(node);
        if (node->balance >= 2 || node->balance <= -2)
            Rotate(node);
        node = node->parent;
    }
}

void MemoryTree::Rotate(Node *node) {
    Node *child;
    if (node->balance < -1) {
        child = node->left;
        SetBalance(child);
        if (child->balance == 1)
            LRR(node, child, child->right);
        else
            LLR(node, child);
    } else {
        child = node->right;
        SetBalance(child);
        if (child->balance == -1)
            RLR(node, child, child->left);
        else
            RRR(node, child);
    }
}

void MemoryTree::LLR(Node *parent, Node *node) {
    Node *grandParent = parent->parent;
    node->parent = grandParent;
    Node *nodeRight = node->right;
    if (nodeRight)
        nodeRight->parent = parent;
    node->right = parent;
    parent->parent = node;
    parent->left = nodeRight;
    if (!grandParent)
        m_root = node;
    else if (grandParent->left == parent)
        grandParent->left = node;
    else
        grandParent->right = node;
}

void MemoryTree::RRR(Node *parent, Node *node) {
    Node *grandParent = parent->parent;
    node->parent = grandParent;
    Node *nodeLeft = node->left;
    if (nodeLeft)
        nodeLeft->parent = parent;
    node->left = parent;
    parent->parent = node;
    parent->right = nodeLeft;
    if (!grandParent)
        m_root = node;
    else if (grandParent->left == parent)
        grandParent->left = node;
    else
        grandParent->right = node;
}

void MemoryTree::LRR(Node *parent, Node *node, Node *child) {
    RRR(node, child);
    LLR(parent, child);
}

void MemoryTree::RLR(Node *parent, Node *node, Node *child) {
    LLR(node, child);
    RRR(parent, child);
}

void MemoryTree::Remove(Node *node) {
    if (node == nullptr)
        return;
    if (m_root == nullptr)
        return;

    Node *parent = node->parent;
    if (node->left == nullptr && node->right == nullptr) {
        if (parent == nullptr)
            m_root = nullptr;
        else if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        m_pool.RemoveNode(node);
        Rebalance(parent);
        m_size--;
    } else if (node->right == nullptr) {
        if (parent == nullptr) {
            m_root = node->left;
            m_root->parent = nullptr;
        } else if (parent->left == node) {
            parent->left = node->left;
            node->left->parent = parent;
        } else {
            parent->right = node->left;
            node->left->parent = parent;
        }
        m_pool.RemoveNode(node);
        Rebalance(parent);
        m_size--;
    } else if (node->left == nullptr) {
        if (parent == nullptr) {
            m_root = node->right;
            m_root->parent = nullptr;
        } else if (parent->left == node) {
            parent->left = node->right;
            node->right->parent = parent;
        } else {
            parent->right = node->right;
            node->right->parent = parent;
        }
        m_pool.RemoveNode(node);
        Rebalance(parent);
        m_size--;
    } else {
        Node *temp = node->right;
        while (temp->left != nullptr)
            temp = temp->left;
        node->key = temp->key;
        node->size = temp->size;
        Remove(temp);
    }
}

void MemoryTree::Insert(size_t key, size_t l_size) {
    if (m_root == nullptr) {
        m_root = m_pool.GetNewNode();
        m_root->key = key;
        m_root->size = l_size;
        return;
    }
    Node *curr = m_root;
    Node *prev = curr;
    while (curr != nullptr) {
        prev = curr;
        if (key < curr->key)
            curr = curr->left;
        else if (key > curr->key)
            curr = curr->right;
        else
            return;
    }
    m_size++;
    Node *newNode = m_pool.GetNewNode();
    newNode->parent = prev;
    newNode->key = key;
    newNode->size = l_size;
    if (key < prev->key)
        prev->left = newNode;
    else
        prev->right = newNode;

    Rebalance(newNode);
}

Node *MemoryTree::FindNode(size_t key) {
    Node *temp = m_root;
    while (temp) {
        if (temp->key == key)
            return temp;
        temp = temp->key < key ? temp->right : temp->left;
    }
    return nullptr;
}

void *MemoryTree::Search(size_t size) {
    LNR lnr(m_root);
    Node *first = lnr.next();
    size_t check_size = 1; // for assertion check. remove later
    while (Node *second = lnr.next()) {
        assert(first->key < second->key);
        check_size++;
        if (second->key + second->size - first->key >= size)
            return (void *)(second->key + second->size + 1);
        first = second;
    }
    assert(check_size == m_size);
    return (void *)(0);
}

void MemoryTree::PrintTree() const {
    std::cout << std::endl;
    PrintTree(m_root);
    std::cout << std::endl;
}

void MemoryTree::PrintTree(Node *node) const {
    static std::vector<bool> levels; //
    if (!levels.empty()) {
        std::cout << " ";
        for (unsigned int i = 0; i < levels.size() - 1; ++i)
            std::cout << (levels.at(i) ? "  " : "| ");
        std::cout << (levels.back() ? "\\" : "+"); // хвост строки
    }
    std::cout << "-" << node->key << ":" << node->size << std::endl;
    if (node->left || node->right) {
        levels.emplace_back(); // добавить уроввень
        if (node->left) {
            levels.back() = !(node->right);
            PrintTree(node->left);
        }
        if (node->right) {
            levels.back() = true;
            PrintTree(node->right);
        }
        levels.pop_back(); // по окончании печати дочерних элементов необходимо
                           // удалить уровень
    }
}