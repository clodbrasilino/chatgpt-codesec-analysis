#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *camel_to_snake(const char *str) {
    if (str == NULL) return NULL;
    size_t len = strnlen(str, 1024);
    char *result = (char *)malloc((len * 2 + 1) * sizeof(char));
    if (result == NULL) return NULL;
    int i, j = 0;
    for (i = 0; str[i]; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && str[i-1] != '_') {
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
    const char *test_cases[] = {"python_language", "programming_language", "python_program", "ThisIsCamelCase"};
    const char *expected_results[] = {"python_language", "programming_language", "python_program", "this_is_camel_case"};
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int k = 0; k < num_test_cases; ++k) {
        char *output = camel_to_snake(test_cases[k]);
        if (output) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }
    return 0;
}