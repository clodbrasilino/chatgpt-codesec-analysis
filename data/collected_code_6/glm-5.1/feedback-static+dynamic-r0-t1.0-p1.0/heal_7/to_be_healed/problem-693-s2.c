#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(str);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    const char *cursor = str;

    while (*cursor != '\0') {
        if (*cursor == ' ') {
            result[result_index++] = ' ';
            while (*cursor == ' ') {
                cursor++;
            }
        } else {
            result[result_index++] = *cursor++;
        }
    }

    result[result_index] = '\0';

    char *shrunk_result = (char *)realloc(result, result_index + 1);
    if (shrunk_result != NULL) {
        return shrunk_result;
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "Google  Assistant",
        "Quad   Core",
        "ChromeCast  Built-in",
        "This   is   a  test   string.",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *output = remove_multiple_spaces(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }
    
    return 0;
}