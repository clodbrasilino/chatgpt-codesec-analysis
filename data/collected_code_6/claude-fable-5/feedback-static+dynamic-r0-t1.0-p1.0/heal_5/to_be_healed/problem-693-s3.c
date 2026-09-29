#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *remove_multiple_spaces(const char *input);
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  */

char *remove_multiple_spaces(const char *input)
{
    size_t input_len;
    size_t i;
    size_t pos;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    i = 0;

    while (i < input_len) {
        if (isspace((unsigned char)input[i])) {
            size_t start = i;

            while (i < input_len && isspace((unsigned char)input[i])) {
                i++;
            }

            if (pos >= input_len) {
                free(result);
                return NULL;
            }

            if (i - start > 1) {
                result[pos] = ' ';
            } else {
                result[pos] = input[start];
            }
            pos++;
        } else {
            if (pos >= input_len) {
                free(result);
                return NULL;
            }
            result[pos] = input[i];
            pos++;
            i++;
        }
    }

    result[pos] = '\0';
    return result;
}

int main(void)
{
    const char *tests[] = {
        "Google    Assistant",
        "Quad \t Core",
        "ChromeCast   Built-in",
        "Hello    world,   this  is    a     test."
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        char *cleaned = remove_multiple_spaces(tests[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string\n");
            return EXIT_FAILURE;
        }
        if (printf("Original: %s\n", tests[i]) < 0) {
            free(cleaned);
            return EXIT_FAILURE;
        }
        if (printf("Cleaned:  %s\n", cleaned) < 0) {
            free(cleaned);
            return EXIT_FAILURE;
        }
        free(cleaned);
    }

    return EXIT_SUCCESS;
}