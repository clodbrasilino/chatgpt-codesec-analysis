#include <stdbool.h>
#include <stdlib.h>

bool oneDistinctElement(int* array, size_t size) {
    if (size == 0 || array == NULL) {
        return false;
    }

    int firstElement = array[0];

    for (size_t i = 1; i < size; ++i) {
        if (array[i] != firstElement) {
            return false;
        }
    }

    return true;
}

int main() {
    int array[4] = {1, 1, 1, 1};

    if (oneDistinctElement(array, 4)) {
        return 0;
    } else {
        return 1;
    }
}