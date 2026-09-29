#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);
    
    size_t space_count = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    if (space_count == 0) {
        char *result = (char *)malloc((length + 1) * sizeof(char));
        if (result == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, str, length + 1);
        return result;
    }

    size_t new_length = length + (space_count * 2);
    char *result = (char *)malloc((new_length + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = str[i];
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "My Name is Dawood",
        "I am a Programmer",
        "I love Coding"
    };
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; i++) {
        char *replaced = replace_spaces(test_strings[i]);
        if (replaced != NULL) {
            printf("%s\n", replaced);
            free(replaced);
        }
    }

    return 0;
}