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
    for (int i = 1; i <= 1 + 600; i += 4) {
        tree->remove(i);
    }
//    for (int i = 2 + 600; i >= 0; i -= 4) {
//        tree->remove(i);
//    }
    for (int i = 3 + 600; i >= 0; i -= 4) {
        tree->remove(i);
    }
    for (int i = 20; i <= 0 + 600; i += 4) {
        tree->remove(i);
    }
    tree->toString();
    return 0;
}
