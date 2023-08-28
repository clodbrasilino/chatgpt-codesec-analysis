#include <stdbool.h>

bool checkSameElements(int* arr, int size) {
    int firstElement = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] != firstElement) {
            return false;
        }
    }
    return true;
}