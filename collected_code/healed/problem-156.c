#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void convertTupleOfStringToInt(const char *input[], int size, int output[]) {
    for (int i = 0; i < size; i++) {
        long long num = atoll(input[i]);
        if (num > INT_MAX || num < INT_MIN) {
            fprintf(stderr, "Input number out of range");
            exit(EXIT_FAILURE);
        }
        output[i] = (int)num;
    }
}

int main() {
    const char *input[] = {"1", "2", "3"};
    int size = sizeof(input) / sizeof(input[0]);
    int output[size];

    convertTupleOfStringToInt(input, size, output);

    for (int i = 0; i < size; i++) {
        printf("%d ", output[i]);
    }

    return 0;
}