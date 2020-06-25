#pragma once

#include <algorithm>
#include <utility>
#include <cassert>

namespace detail {

    template <typename T>
    struct Node;

    template <typename T>
    class Splayer {
    public:
        explicit Splayer(Node<T>* node);

        Node<T>* splay() noexcept;

    private:
        void zig() noexcept;
        void zigzig() noexcept;
        void zigzag() noexcept;

    private:
        Node<T>* m_node;
    };

    template <typename T>
    inline auto splay (Node<T>* node) noexcept -> Node<T>*
    {
        return Splayer{node}.splay();
    }
}

#include "Splay.tpp"