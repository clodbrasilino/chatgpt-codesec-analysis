#include <stdbool.h>

bool checkValue(int value, const int sequence[], int length) {
    for (int i = 0; i < length; i++) {
        if (sequence[i] == value) {
            return true;
        }
    }
    return false;
}


int main() {
    const int sequence[] = {1, 2, 3, 4, 5};
    int value = 3;
    int length = sizeof(sequence)/sizeof(sequence[0]);
    bool result = checkValue(value, sequence, length);
    return 0;
}