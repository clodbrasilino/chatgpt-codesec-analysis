#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *s1, const char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (result == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, s1, len1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

void free_strings(char **strings, int count) {
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

char** concat_tuples(const char **tuples, int tuple_count, int *output_count) {
    char **output = malloc((tuple_count / 2) * sizeof(char *));
    if (output == NULL) return NULL;

    *output_count = 0;
    for (int i = 0; i < tuple_count; i += 2) {
        output[(*output_count)] = concatenate(tuples[i], tuples[i + 1]);
        if (output[(*output_count)] == NULL) {
            free_strings(output, *output_count);
            return NULL;
        }
        (*output_count)++;
    }

    return output;
}

int main() {
    const char *tuples[] = {"a", "b", "c", "d", "e", "f"};
    int tuple_count = 6;
    int output_count = 0;
    char **result = concat_tuples(tuples, tuple_count, &output_count);

    if (result != NULL) {
        for (int i = 0; i < output_count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}