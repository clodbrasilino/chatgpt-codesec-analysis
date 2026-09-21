#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int* generate_initial_terms(int n, int *len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s[21];
    snprintf(s, sizeof(s), "%d", n);
    *len = strnlen(s, sizeof(s));
    int* terms = (int*)malloc(*len * sizeof(int));
    for (int i = 0; i < *len; i++) {
        terms[i] = s[i] - '0';
    }
    return terms;
}

bool is_keith_number(int n) {
    if (n < 10) {
        return false;
    }
    int len;
    int* terms = generate_initial_terms(n, &len);

    while (1) {
        int sum = 0;
        for (int i = 0; i < len; i++) {
            sum += terms[i];
        }
        if (sum > n) {
            free(terms);
            return false;
        } else if (sum == n) {
            free(terms);
            return true;
        }
        for (int i = 0; i < len - 1; ++i) {
            terms[i] = terms[i + 1];
        }
        terms[len - 1] = sum;
    }
    free(terms);
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return 1;
    }
    if (is_keith_number(num)) {
        printf("%d is a Keith Number.\n", num);
    } else {
        printf("%d is not a Keith Number.\n", num);
    }
    return 0;
}