#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_adjacent(const char *a, const char *b) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(b);
    char *result = (char *)malloc(len1 + len2 + 1);
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

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as const array [constParameter]
 */
void process_tuples(char *tuples[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        char *concatenated = concatenate_adjacent(tuples[i], tuples[i + 1]);
        if (concatenated != NULL) {
            printf("%s\n", concatenated);
            free(concatenated);
        }
    }
}

int main() {
    char *tuples[] = {"hello", "world", "foo", "bar"};
    int count = sizeof(tuples) / sizeof(tuples[0]);
    process_tuples(tuples, count);
    return 0;
}