#pragma once

#include "Splay.hpp"

namespace detail {

    template <typename T>
    struct Node {

        T data;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        [[nodiscard]]
        bool isLeftSon () const noexcept {
            if (!parent) {
                return false;
            }
            if (!parent->left) {
                return false;
            }
            return parent->left == &*this;
        }

        [[nodiscard]]
        bool isRightSon () const noexcept {
            if (!parent) {
                return false;
            }
            if (!parent->right) {
                return false;
            }
            return parent->right == &*this;
        }
    };


    /**
     *  @brief Assign var to value, setting var's parent new_parent
     */
    template <typename T>
    void set (Node<T>*& var, Node<T>* value, Node<T>* new_parent = nullptr) {
        var = value;
        if (var) {
            var->parent = new_parent;
        }
    }
}