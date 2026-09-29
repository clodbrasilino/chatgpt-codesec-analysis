#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int* generate_initial_terms(int n, int *len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s[21];
    snprintf(s, sizeof(s), "%d", n);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    *len = strlen(s);
    int* terms = (int*)malloc(*len * sizeof(int));
    for (int i = 0; i < *len; i++) {
        terms[i] = s[i] - '0';
    }
    return terms;
}

bool is_keith_number(int n) {
    int len;
    int* terms = generate_initial_terms(n, &len);
    if (n < 10) {
        free(terms);
        return false;
    }

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
    scanf("%d", &num);
    if (is_keith_number(num)) {
        printf("%d is a Keith Number.\n", num);
    } else {
        printf("%d is not a Keith Number.\n", num);
    }
    return 0;
}