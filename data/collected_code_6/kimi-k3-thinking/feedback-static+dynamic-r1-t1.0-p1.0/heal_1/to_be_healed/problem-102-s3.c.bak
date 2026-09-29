#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  */

char *snake_to_camel(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    int upper_next;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    upper_next = 0;
    for (i = 0; i < len; i++) {
        if (input[i] == '_') {
            if (j > 0) {
                upper_next = 1;
            }
        } else if (upper_next) {
            result[j++] = (char)toupper((unsigned char)input[i]);
            upper_next = 0;
        } else {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *tests[] = {
        "hello_world",
        "convert_snake_case_to_camel_case",
        "single",
        "",
        "already_mixed_CASE_string"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t k;

    for (k = 0; k < num_tests; k++) {
        char *camel = snake_to_camel(tests[k]);
        if (camel == NULL) {
            fprintf(stderr, "Error: failed to convert \"%s\"\n", tests[k]);
            return EXIT_FAILURE;
        }
        printf("snake: %s -> camel: %s\n", tests[k], camel);
        free(camel);
        camel = NULL;
    }

    return EXIT_SUCCESS;
}