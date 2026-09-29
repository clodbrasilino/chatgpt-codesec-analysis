#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'PythoN', got <no output>
  *  test case 2 failed: expected 'HadooP', got <no output>
  *  test case 1 failed: expected 'BigdatA', got <no output>
  */

char *capitalize_first_last(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strnlen(str, SIZE_MAX);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, str, len + 1);

    if (len == 0) {
        return result;
    }

    size_t i = 0;
    while (i < len) {
        while (i < len && isspace((unsigned char)result[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }
        size_t start = i;
        while (i < len && !isspace((unsigned char)result[i])) {
            i++;
        }
        size_t end = i - 1;

        if (isalpha((unsigned char)result[start])) {
            result[start] = (char)toupper((unsigned char)result[start]);
        }
        if (start != end && isalpha((unsigned char)result[end])) {
            result[end] = (char)toupper((unsigned char)result[end]);
        }
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {"Python", "Bigdata", "Hadoop"};
    for (size_t i = 0; i < 3; i++) {
        char *output = capitalize_first_last(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }
    return 0;
}