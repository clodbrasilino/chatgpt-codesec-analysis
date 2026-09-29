#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* find_demlo_number(int n) {
    if (n <= 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        if (!result) return NULL;
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int capacity = 2 * n + 2;
    char* result = (char*)malloc(capacity * sizeof(char));
    if (!result) return NULL;

    int idx = 0;
    for (int i = 1; i <= n; i++) {
        result[idx++] = '0' + i;
    }
    for (int i = n - 1; i >= 1; i--) {
        result[idx++] = '0' + i;
    }
    result[idx] = '\0';
    return result;
}

int main(void) {
    int test_cases[] = {1, 2, 3, 4, 5, 9, 10, 15};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        char* demlo = find_demlo_number(test_cases[i]);
        if (demlo) {
            printf("Demlo number for n=%d: %s\n", test_cases[i], demlo);
            free(demlo);
        } else {
            printf("Memory allocation failed for n=%d\n", test_cases[i]);
        }
    }

    return 0;
}