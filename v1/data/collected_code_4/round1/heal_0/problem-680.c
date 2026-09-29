#include <stdbool.h>
#include <stdio.h>

bool is_increasing(int* sequence, int length) {
    int current = sequence[0];
    
    for (int i = 1; i < length; i++) {
        if (sequence[i] > current) {
            current = sequence[i];
        } else {
            return false;
        }
    }

    return true;
}

int main() {
    int sequence1[] = {1, 2, 3, 4, 5};
    int sequence2[] = {1, 3, 2, 4, 5};

    printf("Is the sequence1 increasing: %d\n", is_increasing(sequence1, 5));
    printf("Is the sequence2 increasing: %d\n", is_increasing(sequence2, 5));

    return 0;
}