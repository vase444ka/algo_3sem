#pragma once

#include <initializer_list>
#include <string_view>
#include <numeric>
#include <string>
#include <vector>

namespace lab {

    class File {
    public:
        explicit File() noexcept = default;
        explicit File(std::string_view name, unsigned size = 0) noexcept
                : m_name(name),
                  m_size(size)
        {}

        [[nodiscard]]
        auto name() const noexcept {
            return m_name;
        }

        [[nodiscard]]
        auto size() const noexcept {
            return m_size;
        }

    private:
        std::string m_name;
        unsigned m_size = 0;
    };

    class Directory {
    public:

        explicit Directory() noexcept = default;

        explicit Directory (std::string_view name,
                                      std::initializer_list<File> files) noexcept
                : m_name(name),
                  m_files(files)
        {}

        [[nodiscard]]
        auto name() const noexcept {
            return m_name;
        }

        [[nodiscard]]
        auto files() const noexcept {
            return m_files;
        }

        [[nodiscard]]
        auto size() const noexcept {
            return std::accumulate(m_files.begin(),
                                   m_files.end(), 0,
                                   [](auto sum, const auto& file) {
                                       return sum + file.size();
            });
        }

    private:
        std::vector<File> m_files;
        std::string_view m_name;
    };

    bool operator< (const Directory& lhs, const Directory& rhs) {
        return lhs.size() < rhs.size();
    }

    bool operator== (const Directory& lhs, const Directory& rhs) {
        return lhs.files() == rhs.files();
    }

    bool operator> (const Directory& lhs, const Directory& rhs) {
        return lhs.size() > rhs.size();
    }

    bool operator< (const File& lhs, const File& rhs) {
        return lhs.size() < rhs.size();
    }

    bool operator== (const File& lhs, const File& rhs) {
        return lhs.size() == rhs.size() && lhs.name() == rhs.name();
    }

    bool operator> (const File& lhs, const File& rhs) {
        return lhs.size() > rhs.size();
    }
}
