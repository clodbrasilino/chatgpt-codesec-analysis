#include <stdbool.h>

bool checkValue(int value, int sequence[], int length) {
    for (int i = 0; i < length; i++) {
        if (sequence[i] == value) {
            return true;
        }
    }
    return false;
}