#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'quad_core', got <no output>
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 0 failed: expected 'google_assistant', got <no output>
  */

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t output_len = input_len + 1;
    size_t i, j;

    for (i = 0; i < input_len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0 && (islower((unsigned char)input[i - 1]) || isdigit((unsigned char)input[i - 1]))) {
                output_len++;
            }
            if (i > 0 && isupper((unsigned char)input[i - 1]) && i + 1 < input_len && islower((unsigned char)input[i + 1])) {
                output_len++;
            }
        }
    }

    char *output = (char *)malloc(output_len);
    if (output == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < input_len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0 && (islower((unsigned char)input[i - 1]) || isdigit((unsigned char)input[i - 1]))) {
                output[j++] = '_';
            }
            if (i > 0 && isupper((unsigned char)input[i - 1]) && i + 1 < input_len && islower((unsigned char)input[i + 1])) {
                output[j++] = '_';
            }
            output[j++] = tolower((unsigned char)input[i]);
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';

    return output;
}

int main(void) {
    const char *tests[] = {
        "camelCase",
        "helloWorld",
        "thisIsATest",
        "already_snake",
        "mixedCase_WithSnake",
        "UPPERCASE",
        "camel123Case",
        "c",
        "quadCore",
        "chromeCast",
        "googleAssistant"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result != NULL) {
            printf("%s -> %s\n", tests[i], result);
            free(result);
        } else {
            printf("%s -> (conversion failed)\n", tests[i]);
        }
    }

    return 0;
}