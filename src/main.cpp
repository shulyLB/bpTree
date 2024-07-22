#include "header/IBpTree.h"
#include <vector>

int main() {

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
    tree->remove(1);
    tree->remove(0);
    tree->remove(6);
    tree->remove(8);
    tree->remove(3);
    tree->remove(2);
    tree->remove(5);
    tree->remove(11);
    tree->toString();
    return 0;
}
