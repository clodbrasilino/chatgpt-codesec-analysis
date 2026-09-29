#include <stdbool.h>

bool checkTuple(int tuple[], int size) {
    for (int i = 0; i < size; i++) {
        if (tuple[i] < 0) {
            return false;
        }
    }
    return true;
}