#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'I%20love%20Coding', got <no output>
  *  test case 1 failed: expected 'I%20am%20a%20Programmer', got <no output>
  *  test case 0 failed: expected 'My%20Name%20is%20Dawood', got <no output>
  */

char *replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t space_count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);

    for (size_t i = 0; i < length; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
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
    const char *test_string = "Hello World from C";
    char *replaced = replace_spaces(test_string);

    if (replaced != NULL) {
        printf("Original: %s\n", test_string);
        printf("Replaced: %s\n", replaced);
        free(replaced);
    } else {
        printf("Memory allocation failed or input string is NULL\n");
    }

    return 0;
}