#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple concatenate_tuples(const StringTuple *t1, const StringTuple *t2) {
    StringTuple result = {NULL, NULL};

    if (t1 == NULL || t2 == NULL || t1->first == NULL || t1->second == NULL || t2->first == NULL || t2->second == NULL) {
        return result;
    }

    size_t len1_first = strnlen(t1->first, SIZE_MAX);
    size_t len1_second = strnlen(t1->second, SIZE_MAX);
    size_t len2_first = strnlen(t2->first, SIZE_MAX);
    size_t len2_second = strnlen(t2->second, SIZE_MAX);

    if (len1_first > SIZE_MAX - len2_first - 1 || len1_second > SIZE_MAX - len2_second - 1) {
        return result;
    }

    size_t total_first = len1_first + len2_first + 1;
    size_t total_second = len1_second + len2_second + 1;

    result.first = (char *)malloc(total_first);
    result.second = (char *)malloc(total_second);

    if (result.first == NULL || result.second == NULL) {
        free(result.first);
        free(result.second);
        result.first = NULL;
        result.second = NULL;
        return result;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result.first, t1->first, len1_first);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result.first + len1_first, t2->first, len2_first);
    result.first[total_first - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result.second, t1->second, len1_second);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result.second + len1_second, t2->second, len2_second);
    result.second[total_second - 1] = '\0';

    return result;
}

int main(void) {
    StringTuple t1 = {"Hello, ", "Good "};
    StringTuple t2 = {"World!", "Morning!"};

    StringTuple res = concatenate_tuples(&t1, &t2);

    if (res.first != NULL && res.second != NULL) {
        printf("First: %s\n", res.first);
        printf("Second: %s\n", res.second);
        free(res.first);
        free(res.second);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        free(res.first);
        free(res.second);
    }

    return 0;
}