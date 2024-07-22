#include "header/IBpTree.h"
#include <vector>

int main() {

    auto *tree = new IBpTree(9);
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
    tree->remove(1);
    tree->remove(0);
    tree->remove(6);
    tree->remove(9);

    tree->toString();
    return 0;
}
