#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t left = 0;
    size_t right = len > 0 ? len - 1 : 0;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i]);
    }
}

int main(void) {
    const char *original_strings[] = {"hello", "world", "C", "programming"};
    size_t count = sizeof(original_strings) / sizeof(original_strings[0]);
    char **strings = malloc(count * sizeof(char *));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }
    size_t allocated_count = 0;
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        strings[i] = malloc(strlen(original_strings[i]) + 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < allocated_count; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(strings[i], original_strings[i]);
        allocated_count++;
    }
    reverse_strings(strings, count);
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }
    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
    return EXIT_SUCCESS;
}