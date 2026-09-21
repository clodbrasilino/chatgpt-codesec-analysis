#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  */

char *camel_to_snake(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    output = malloc((len * 2U) + 1U);
    if (output == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (isupper(c) != 0) {
            if (i > 0U) {
                output[j] = '_';
                j++;
            }
            output[j] = (char)tolower(c);
            j++;
        } else {
            output[j] = (char)c;
            j++;
        }
    }
    output[j] = '\0';

    return output;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "helloWorld",
        "alreadylower",
        "XMLParser",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    int status = EXIT_SUCCESS;

    for (i = 0U; i < count; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result == NULL) {
            (void)fprintf(stderr, "Conversion failed for input: %s\n", tests[i]);
            status = EXIT_FAILURE;
        } else {
            if (printf("%s -> %s\n", tests[i], result) < 0) {
                status = EXIT_FAILURE;
            }
            free(result);
        }
    }

    return status;
}