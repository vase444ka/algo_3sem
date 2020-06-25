#pragma once

#include "SplayTreeNode.hpp"

namespace detail {

    template <typename T>
    Splayer<T>::Splayer (Node<T>*node)
            : m_node(node)
    {}

    template <typename T>
    auto Splayer<T>::splay() noexcept -> Node<T>*
    {
        while (m_node->parent) {
            if ((m_node->isRightSon() && m_node->parent->isLeftSon()) ||
                (m_node->isLeftSon() && m_node->parent->isRightSon())) {
                zigzag();
            }
            else if ((m_node->isLeftSon() && m_node->parent->isLeftSon()) ||
                     (m_node->isRightSon() && m_node->parent->isRightSon())) {
                zigzig();
            }
            else {
                zig();
                return m_node;
            }
        }
        return m_node;
    }

    template <typename T>
    void Splayer<T>::zig() noexcept
    {
        auto& parent = m_node->parent;
        if (m_node->isLeftSon()) {
            set(parent->left, m_node->right, parent);
            set(m_node->right, parent, m_node);
        }
        else if (m_node->isRightSon()) {
            set(parent->right, m_node->left, parent);
            set(m_node->left, parent, m_node);
        }
        parent = nullptr;
    }

    template <typename T>
    void Splayer<T>::zigzig() noexcept
    {
        auto mostParent = m_node->parent->parent->parent;
        auto grandparent = m_node->parent->parent;
        if (grandparent->isLeftSon()) {
            mostParent->left = m_node;
        }
        else if (grandparent->isRightSon()){
            mostParent->right = m_node;
        }
        auto parent = m_node->parent;

        if (m_node->isLeftSon() && parent->isLeftSon()) {
            set(grandparent->left, parent->right, grandparent);
            set(parent->right, grandparent, parent);
            set(parent->left, m_node->right, parent);
            set(m_node->right, parent, m_node);
        }

        else if (m_node->isRightSon() && parent->isRightSon()) {
            set(grandparent->right, parent->left, grandparent);
            set(parent->left, grandparent, parent);
            set(parent->right, m_node->left, parent);
            set(m_node->left, parent, m_node);
        }
        m_node->parent = mostParent;
    }

    template <typename T>
    void Splayer<T>::zigzag() noexcept
    {
        auto mostParent = m_node->parent->parent->parent;
        auto grandparent = m_node->parent->parent;
        if (grandparent->isLeftSon()) {
            mostParent->left = m_node;
        }
        else if (grandparent->isRightSon()){
            mostParent->right = m_node;
        }
        auto parent = m_node->parent;

        if (m_node->isRightSon() && parent->isLeftSon()) {
            set(grandparent->left, m_node->right, grandparent);
            set(parent->right, m_node->left, parent);

            set(m_node->left, parent, m_node);
            set(m_node->right, grandparent, m_node);
        }
        else if (m_node->isLeftSon() && parent->isRightSon()){
            set(grandparent->right, m_node->left, grandparent);
            set(parent->left, m_node->right, parent);

            set(m_node->right, parent, m_node);
            set(m_node->left, grandparent, m_node);
        }
        m_node->parent = mostParent;
    }
}