#include <stdbool.h>

int countTrueBooleans(const bool list[], int size);

int main() {
    bool array[] = { true, false, true, false, true };
    int size = sizeof(array) / sizeof(array[0]);
    int count = countTrueBooleans(array, size);
    return 0;
}

int countTrueBooleans(const bool list[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i]) {
            count++;
        }
    }
    return count;
}