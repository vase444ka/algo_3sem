#pragma once

#include "SplayTree.hpp"

namespace detail {

    template <typename T>
    auto find (Node<T>* node, const T& elem) noexcept -> Node<T>*
    {
        while (node) {
            if (node->data > elem) {
                node = node->left;
            }
            else if (node->data < elem) {
                node = node->right;
            }
            else {
                return node;
            }
        }
        return nullptr;
    }

    template <typename T>
    auto min (Node<T>* node) noexcept -> Node<T>*
    {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    template <typename T>
    auto max (Node<T>* node) noexcept -> Node<T>*
    {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    template <typename T>
    auto merge (Node<T>* lhs, Node<T>* rhs) noexcept -> Node<T>*
    {
        if (!lhs) {
            return rhs;
        }
        if (!rhs) {
            return lhs;
        }
        assert(max(lhs)->data < min(rhs)->data);
        auto lhs_root = splay(max(lhs));
        lhs_root->right = rhs;
        lhs_root->right->parent = lhs_root;
        return lhs_root;
    }

    template <typename T>
    auto split (Node<T>* tree, const T& elem) noexcept -> std::pair<Node<T>*, Node<T>*>
    {
        auto begin = SplayTree<T>::Iterator(min(tree));
        auto end = SplayTree<T>::Iterator(nullptr);

        T upper_bound = std::upper_bound(begin, end, elem);
        auto upper_bound_node = find(tree, elem);
        auto new_tree = splay(upper_bound_node);
        auto leftTree = new_tree->left;
        leftTree->parent = nullptr;
        new_tree->left = nullptr;
        return std::pair(leftTree, new_tree);
    }

    template <typename T>
    void deleteTree (Node<T>* node) {
        if (!node) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}
