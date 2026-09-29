#include <stdbool.h>

bool checkArrPattern(int arr[], int size, int patterns[], int patternSize) {
    int patternIndex = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == patterns[patternIndex]) {
            patternIndex++;
        }
        if (patternIndex == patternSize) {
            return true;
        }
    }
    return false;
}