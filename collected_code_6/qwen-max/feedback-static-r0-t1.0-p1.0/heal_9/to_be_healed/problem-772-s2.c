#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(const char *str, int k) {
    if (str == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str), pos = 0, i = 0, start = 0;
    char *result = malloc(1);
    if (result == NULL) exit(1);
    result[0] = '\0';

    while (i <= length) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (i - start != k && i - start > 0) {
                size_t to_copy = i - start;
                char *temp = realloc(result, pos + to_copy + 1);
                if (temp == NULL) exit(1);
                result = temp;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + pos, str + start, to_copy);
                pos += to_copy;
            }
            start = i + 1;
        }
        i++;
    }

    result = realloc(result, pos + 1);
    if (result == NULL) exit(1);
    result[pos] = '\0';
    return result;
}

int main() {
    const char str[] = "This is a test string with some words of different lengths";
    int k = 4;

    char *new_str = remove_k_length_words(str, k);
    printf("Original String: %s\n", str);
    printf("Modified String: %s\n", new_str);

    free(new_str);
    return 0;
}