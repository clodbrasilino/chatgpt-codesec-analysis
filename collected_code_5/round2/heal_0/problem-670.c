#include <stdbool.h>
#include <stdio.h>

bool check_decreasing_trend(int* sequence, int length) {
    if(sequence == NULL || length <= 0) {
        return false;
    }
    for(int i = 0; i < length - 1; i++) {
        if(sequence[i] <= sequence[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int sequence1[] = {10, 9, 8, 7, 6};
    int sequence2[] = {5, 4, 5, 2, 1};

    if(check_decreasing_trend(sequence1, 5)) {
        printf("sequence1 has a decreasing trend\n");
    } else {
        printf("sequence1 does not have a decreasing trend\n");
    }

    if(check_decreasing_trend(sequence2, 5)) {
        printf("sequence2 has a decreasing trend\n");
    } else {
        printf("sequence2 does not have a decreasing trend\n");
    }

    return 0;
}