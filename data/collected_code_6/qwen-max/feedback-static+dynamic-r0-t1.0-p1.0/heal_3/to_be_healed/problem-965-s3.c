#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  */

char *camel_to_snake(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = (char *)malloc(len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (size_t i = 0; i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (j > 0) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)str[i]);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char *str = (char *)malloc(256 * sizeof(char));
    if (str == NULL) {
        return 1;
    }
    printf("Enter a camel case string: ");
    if (fgets(str, 256, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        char *snake_case_str = camel_to_snake(str);
        if (snake_case_str != NULL) {
            printf("Snake case: %s\n", snake_case_str);
            free(snake_case_str);
        } else {
            printf("Error converting string.\n");
        }
    } else {
        printf("Error reading input.\n");
    }
    free(str);
    return 0;
}