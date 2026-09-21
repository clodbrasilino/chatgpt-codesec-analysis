#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_adjacent(const char *a, const char *b) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = a ? strlen(a) : 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = b ? strlen(b) : 0;
    char *result = (char *)malloc(len1 + len2 + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, a, len1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + len1, b, len2);
    result[len1 + len2] = '\0';
    return result;
}

void process_tuples(const char *tuples[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        char *concatenated = concatenate_adjacent(tuples[i], tuples[i + 1]);
        if (concatenated != NULL) {
            printf("%s\n", concatenated);
            free(concatenated);
        }
    }
}

int main() {
    const char *tuples[] = {"hello", "world", "foo", "bar"};
    int count = sizeof(tuples) / sizeof(tuples[0]);
    process_tuples(tuples, count);
    return 0;
}