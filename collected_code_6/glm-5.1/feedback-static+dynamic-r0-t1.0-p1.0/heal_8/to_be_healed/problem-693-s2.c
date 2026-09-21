#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  */

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t max_len = 0;
    while (str[max_len] != '\0') {
        max_len++;
    }

    char *result = (char *)malloc(max_len + 1);
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