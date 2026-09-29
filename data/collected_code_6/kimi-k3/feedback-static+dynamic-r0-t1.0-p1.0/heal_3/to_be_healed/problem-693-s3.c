#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  */

char *remove_multiple_spaces(const char *input)
{
    char *result;
    size_t input_len;
    size_t pos = 0;
    size_t i;
    int in_space = 0;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, 4096);
    if (input_len == 0) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        if (input[i] == ' ') {
            if (!in_space) {
                result[pos++] = ' ';
                in_space = 1;
            }
        } else {
            result[pos++] = input[i];
            in_space = 0;
        }
    }

    result[pos] = '\0';
    return result;
}

int main(void)
{
    const char *test_string = "This   is    a   test    string  with   multiple    spaces.";
    char *cleaned;

    cleaned = remove_multiple_spaces(test_string);
    if (cleaned == NULL) {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}