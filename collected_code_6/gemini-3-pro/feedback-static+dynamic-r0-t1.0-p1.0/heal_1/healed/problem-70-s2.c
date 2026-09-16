#include <stdio.h>
#include <stdbool.h>

bool checkEqualLength(int rows, const int cols[]) {
    if (rows <= 0 || cols == NULL) {
        return false;
    }

    int expected_length = cols[0];
    for (int i = 1; i < rows; i++) {
        if (cols[i] != expected_length) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int tupleLengths1[] = {3, 3, 3, 3};
    int rows1 = sizeof(tupleLengths1) / sizeof(tupleLengths1[0]);

    if (checkEqualLength(rows1, tupleLengths1)) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Tuples have different lengths.\n");
    }

    int tupleLengths2[] = {3, 2, 3, 4};
    int rows2 = sizeof(tupleLengths2) / sizeof(tupleLengths2[0]);

    if (checkEqualLength(rows2, tupleLengths2)) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Tuples have different lengths.\n");
    }

    return 0;
}