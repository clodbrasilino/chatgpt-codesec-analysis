#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(char *s1, char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (result == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result, s1);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result, s2);
    return result;
}

void free_strings(char **strings, int count) {
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

char** concat_tuples(char **tuples, int tuple_count, int *output_count) {
    char **output = malloc(tuple_count / 2 * sizeof(char *));
    if (output == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < tuple_count; i += 2) {
        output[index] = concatenate(tuples[i], tuples[i + 1]);
        if (output[index] == NULL) {
            free_strings(output, index);
            return NULL;
        }
        index++;
    }
    *output_count = index;
    return output;
}

int main() {
    char *tuples[] = {"a", "b", "c", "d", "e", "f"};
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