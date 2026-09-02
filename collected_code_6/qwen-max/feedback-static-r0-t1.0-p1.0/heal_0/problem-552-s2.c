#include <stdio.h>
#include <stdbool.h>

bool is_linear(int *sequence, int size) {
    if (size < 2) return true;
    int diff = sequence[1] - sequence[0];
    for (int i = 2; i < size; ++i) {
        if (sequence[i] - sequence[i-1] != diff) {
            return false;
        }
    }
    return true;
}

int main() {
    int sequence[] = {2, 4, 6, 8, 10};
    int size = sizeof(sequence) / sizeof(sequence[0]);
    if (is_linear(sequence, size)) {
        printf("The sequence is linear.\n");
    } else {
        printf("The sequence is not linear.\n");
    }
    return 0;
}