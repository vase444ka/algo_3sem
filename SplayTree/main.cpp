#include "Filesystem.hpp"
#include "SplayTree.hpp"

#include <iostream>

int main() {

    using namespace lab;
    SplayTree<File> tree;

    std::array dirs = {Directory{"Photos",
                                 {File{"a.jpg", 5},
                                  File{"f.jpg", 4},
                                  File{"z.jpg", 2}}},
                       Directory{"Videos",
                                 {File{"a.mp4", 1000},
                                  File{"f.mp4", 200}}},
                       Directory{"Other files",
                                 {File{"some.thing", 233}}}
    };

    std::cout << "File to insert: \n";

    for (const auto& dir : dirs) {
        for (const auto& file : dir.files()) {
            std::cout << file.name() << ' '
                      << "size: " << file.size() << std::endl;
            tree.insert(file);
        }
    }

    std::cout << "\n\nIterating in tree after insertion :\n";
    for (const auto& i : tree) {
        std::cout << i.name() << ' '
                  << "size: " << i.size() << std::endl;
    }

    std::cout << "\n\nErasing file " << dirs[0].files()[0].name() << "\n";

    tree.erase(dirs[0].files()[0]);

    std::cout << "\nIterating in tree after erasing :\n";
    for (const auto& i : tree) {
        std::cout << i.name() << ' '
                  << "size: " << i.size() << std::endl;
    }
    return 0;
}
