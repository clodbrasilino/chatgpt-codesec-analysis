#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(char *a, char *b) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_a = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_b = strlen(b);
    char *result = (char *)malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result, a);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result, b);
    return result;
}

void processTuples(char *tuples[], int length, char **output) {
    for (int i = 0; i < length - 1; i++) {
        output[i] = concatenate(tuples[i], tuples[i + 1]);
    }
    output[length - 1] = NULL;
}

int main() {
    char *tuples[] = {"hello", "world", "foo", "bar"};
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