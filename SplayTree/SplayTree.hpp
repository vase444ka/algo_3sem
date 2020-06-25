#pragma once

#include "SplayTreeNode.hpp"

#include <iterator>
#include <cstddef>

namespace lab {

    template <typename T>
    class SplayTree {
    public:

        class Iterator {
        public:
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::forward_iterator_tag;

            explicit Iterator (detail::Node<T>* root) noexcept;

            const T& operator*() noexcept ;

            bool operator!= (const Iterator& other) noexcept;

            bool operator== (const Iterator& other) noexcept;

            Iterator& operator++() noexcept ;

            Iterator operator+ (int n) const noexcept ;

        private:
            detail::Node<T>* m_curr;
        };

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = Iterator;
        using const_iterator = Iterator;

        explicit SplayTree() noexcept = default;

        SplayTree(std::initializer_list<T> elems) noexcept;

        bool search (const T& key) noexcept;
        void insert (const T& key);
        void erase (const T& key);

        Iterator begin() const;
        Iterator end() const;

        ~SplayTree ();

    private:
        using NodePtr = detail::Node<T>*;
        NodePtr m_root = nullptr;
    };
}

#include "SplayTreeIterator.tpp"
#include "SplayTree.tpp"