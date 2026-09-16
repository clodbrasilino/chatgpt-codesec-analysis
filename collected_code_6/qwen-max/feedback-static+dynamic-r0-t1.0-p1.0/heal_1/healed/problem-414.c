#include <stdio.h>
#include <stdbool.h>

bool is_value_in_sequence(const int *sequence, int length, int value) {
    for (int i = 0; i < length; ++i) {
        if (sequence[i] == value) {
            return true;
        }
    }
    return false;
}

int main() {
    int sequence[] = {1, 2, 3, 4, 5};
    int length = sizeof(sequence) / sizeof(sequence[0]);
    int value = 3;

    if (is_value_in_sequence(sequence, length, value)) {
        printf("Value found in sequence.\n");
    } else {
        printf("Value not found in sequence.\n");
    }

    return 0;
}