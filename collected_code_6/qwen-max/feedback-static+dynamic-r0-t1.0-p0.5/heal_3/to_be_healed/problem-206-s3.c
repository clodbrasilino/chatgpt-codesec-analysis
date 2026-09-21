#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_a = a ? strlen(a) : 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_b = b ? strlen(b) : 0;
    char *result = (char *)malloc(len_a + len_b + 1);
    if (result == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    if (len_a > 0) memcpy(result, a, len_a);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    if (len_b > 0) memcpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';
    return result;
}

void process_tuples(const char **tuples, int n, char ***output, int *output_size) {
    *output_size = n - 1;
    *output = (char **)malloc((*output_size) * sizeof(char *));
    if (*output == NULL) return;
    for (int i = 0; i < *output_size; ++i) {
        (*output)[i] = concatenate(tuples[i], tuples[i + 1]);
        if ((*output)[i] == NULL) {
            for (int j = 0; j < i; ++j) free((*output)[j]);
            free(*output);
            *output = NULL;
            *output_size = 0;
            return;
        }
    }
}

int main() {
    const char *tuples[] = {"hello", "world", "foo", "bar"};
    int n = 4;
    char **output;
    int output_size;

    process_tuples(tuples, n, &output, &output_size);

    for (int i = 0; i < output_size; ++i) {
        printf("%s\n", output[i]);
        free(output[i]);
    }
    free(output);

    return 0;
}