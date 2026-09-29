#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    size_t len_a = strnlen(a, 256);
    size_t len_b = strnlen(b, 256);
    char *result = (char *)malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(result, a, len_a);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';
    return result;
}

void processTuples(const char *tuples[], int length, char **output) {
    for (int i = 0; i < length - 1; i++) {
        output[i] = concatenate(tuples[i], tuples[i + 1]);
    }
    output[length - 1] = NULL;
}

int main() {
    const char *tuples[] = {"hello", "world", "foo", "bar"};
    int length = sizeof(tuples) / sizeof(tuples[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *output[length];

    processTuples(tuples, length, output);

    for (int i = 0; i < length - 1; i++) {
        printf("%s\n", output[i]);
        free(output[i]);
    }

    return 0;
}