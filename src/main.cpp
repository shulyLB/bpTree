#include <vector>
#include "header/IBpTree.h"
#include <iostream>
int main() {
    try {
        auto *tree = new IBpTree(10);
        for (int i = 0; i <= 0 + 600; i += 4) {
            tree->put(i);
        }
        for (int i = 1; i <= 1 + 600; i += 4) {
            tree->put(i);
        }
        for (int i = 2 + 600; i >= 0; i -= 4) {
            tree->put(i);
        }
        for (int i = 3 + 600; i >= 0; i -= 4) {
            tree->put(i);
        }
        for (int i = 1; i <= 1 + 600; i += 4) {
            tree->remove(i);
        }
        for (int i = 2 + 600; i >= 0; i -= 4) {
            tree->remove(i);
        }
        for (int i = 3 + 600; i >= 0; i -= 8) {
            tree->remove(i);
        }
        for (int i = 4; i <= 0 + 600; i += 4) {
            tree->remove(i);
        }
        tree->remove(0);
        tree->toString();
        std::cout << tree->contain(23) << std::endl;
    } catch (IException & err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}
