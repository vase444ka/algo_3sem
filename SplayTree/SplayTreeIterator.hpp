#pragma once

#include "SplayTree.hpp"

template<typename T>
bool SplayTree<T>::Iterator::operator!=(const SplayTree::Iterator &other) noexcept {
    return m_curr != other.m_curr;
}

template<typename T>
bool SplayTree<T>::Iterator::operator==(const SplayTree::Iterator &other) noexcept {
    return m_curr == other.m_curr;
}

template<typename T>
auto SplayTree<T>::Iterator::operator++() noexcept -> typename SplayTree<T>::Iterator & {
    if (m_curr->right) {
        auto s = m_curr->right->data;
        auto temp = m_curr->right;
        while (temp->left) {
            temp = temp->left;
        }
        m_curr = temp;
        return *this;
    }

    while (true) {
        if (!m_curr->parent) {
            m_curr = nullptr;
            return *this;
        }
        if (m_curr->isLeftSon()) {
            m_curr = m_curr->parent;
            return *this;
        }
        m_curr = m_curr->parent;
    }
}

template<typename T>
auto SplayTree<T>::Iterator::operator*() noexcept -> const T & {
    return m_curr->data;
}

template<typename T>
SplayTree<T>::Iterator::Iterator(SplayTree::NodePtr root) noexcept
        : m_curr(root) {}

template<typename T>
auto SplayTree<T>::Iterator::operator+(int n) const noexcept -> typename SplayTree<T>::Iterator {
    SplayTree<T>::Iterator temp(*this);
    for (int i = 0; i < n; ++i) {
        ++temp;
    }
    return temp;
}

