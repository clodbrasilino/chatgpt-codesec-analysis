#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple concatenate_tuples(const StringTuple *a, const StringTuple *b) {
    StringTuple result = {NULL, NULL};

    if (a == NULL || b == NULL) {
        return result;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_a1 = a->first ? strlen(a->first) : 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_a2 = a->second ? strlen(a->second) : 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_b1 = b->first ? strlen(b->first) : 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_b2 = b->second ? strlen(b->second) : 0;

    if (len_a1 > SIZE_MAX - len_b1 - 1 || len_a2 > SIZE_MAX - len_b2 - 1) {
        return result;
    }

    size_t total_len1 = len_a1 + len_b1 + 1;
    size_t total_len2 = len_a2 + len_b2 + 1;

    result.first = (char *)malloc(total_len1);
    if (result.first != NULL) {
        if (len_a1 > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result.first, a->first, len_a1);
        }
        if (len_b1 > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result.first + len_a1, b->first, len_b1);
        }
        result.first[len_a1 + len_b1] = '\0';
    }

    result.second = (char *)malloc(total_len2);
    if (result.second != NULL) {
        if (len_a2 > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result.second, a->second, len_a2);
        }
        if (len_b2 > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result.second + len_a2, b->second, len_b2);
        }
        result.second[len_a2 + len_b2] = '\0';
    }

    if (result.first == NULL || result.second == NULL) {
        free(result.first);
        free(result.second);
        result.first = NULL;
        result.second = NULL;
    }

    return result;
}

int main(void) {
    StringTuple t1 = {"Hello, ", "C "};
    StringTuple t2 = {"World!", "Developer"};

    StringTuple res = concatenate_tuples(&t1, &t2);

    if (res.first != NULL && res.second != NULL) {
        printf("First: %s\n", res.first);
        printf("Second: %s\n", res.second);
    } else {
        printf("Allocation failed\n");
        return 1;
    }

    free(res.first);
    free(res.second);

    return 0;
}