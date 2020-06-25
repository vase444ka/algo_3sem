#pragma once

#include "Splay.hpp"
#include "NodeTools.hpp"
#include "SplayTree.hpp"


namespace lab {

    template <typename T>
    auto SplayTree<T>::begin() const -> typename SplayTree<T>::Iterator {
        return Iterator{detail::min(m_root)};
    }

    template <typename T>
    auto SplayTree<T>::end() const -> typename SplayTree<T>::Iterator {
        return Iterator{nullptr};
    }

    template <typename T>
    auto SplayTree<T>::search (const T& key) noexcept -> bool
    {
       auto found = detail::find(m_root, key);
       if (found) {
           detail::splay(found);
           return true;
       }
       else
           return false;
    }

    template <typename T>
    void SplayTree<T>::insert (const T& key) {
        if (!m_root) {
            m_root = new detail::Node<T> {key};
            return;
        }
        auto temp = m_root;
        while (true) {
            if (temp->data > key) {
                if (!temp->left) {
                    temp->left = new detail::Node<T>{key, nullptr,
                                                     nullptr, temp};
                    temp = temp->left;
                    break;
                }
                temp = temp->left;
            }
            else if (temp->data < key) {
                if (!temp->right) {
                    temp->right = new detail::Node<T>{key, nullptr,
                                                      nullptr, temp};
                    temp = temp->right;
                    break;
                }
                temp = temp->right;
            }
            else return;
        }
        m_root = detail::splay(temp);
    }

    template <typename T>
    void SplayTree<T>::erase (const T& key) {
        auto found = detail::find(m_root, key);
        auto splayed = detail::splay(found);
        auto lhs_tree = splayed->left;
        auto rhs_tree = splayed->right;
        if (lhs_tree) {
            lhs_tree->parent = nullptr;
        }
        if (rhs_tree) {
            rhs_tree->parent = nullptr;
        }
        delete splayed;
        m_root = detail::merge(lhs_tree, rhs_tree);
    }

    template <typename T>
    SplayTree<T>::~SplayTree () {
        detail::deleteTree(m_root);
    }

    template <typename T>
    SplayTree<T>::SplayTree (std::initializer_list<T> elems) noexcept
            : m_root(nullptr)
    {
        for (const auto& elem : elems) {
            insert(elem);
        }
    }
}