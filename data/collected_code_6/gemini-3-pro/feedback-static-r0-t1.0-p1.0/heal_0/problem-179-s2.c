#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isKeithNumber(int n) {
    if (n < 0) {
        return false;
    }

    int temp = n;
    int numDigits = 0;

    while (temp > 0) {
        numDigits++;
        temp /= 10;
    }

    if (numDigits == 0) {
        return false;
    }

    int *terms = (int *)malloc(numDigits * sizeof(int));
    if (terms == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    temp = n;
    for (int i = numDigits - 1; i >= 0; i--) {
        terms[i] = temp % 10;
        temp /= 10;
    }

    int nextTerm = 0;
    int insertIndex = 0;

    while (nextTerm < n) {
        nextTerm = 0;
        for (int i = 0; i < numDigits; i++) {
            nextTerm += terms[i];
        }

        if (nextTerm == n) {
            free(terms);
            return true;
        }

        terms[insertIndex] = nextTerm;
        insertIndex = (insertIndex + 1) % numDigits;
    }

    free(terms);
    return false;
}

int main(void) {
    int num;
    
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (isKeithNumber(num)) {
        printf("%d is a Keith number.\n", num);
    } else {
        printf("%d is not a Keith number.\n", num);
    }

    return EXIT_SUCCESS;
}