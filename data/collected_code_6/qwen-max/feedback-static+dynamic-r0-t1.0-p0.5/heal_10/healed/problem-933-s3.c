#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    size_t input_len = strlen(input);
    char *output = malloc(input_len * 2 + 1);
    if (output == NULL) return NULL;
    snprintf(output, input_len * 2 + 1, "%s", input);
    int offset = 0;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED)) {
        free(output);
        return NULL;
    }

    while (regexec(&regex, output + offset, 2, matches, 0) == 0) {
        size_t len = strlen(output + offset);
        memmove(output + matches[0].rm_so + 2 + offset, output + matches[0].rm_so + 1 + offset, len - (matches[0].rm_so + 1 + offset) + 1);
        output[matches[0].rm_so + 1 + offset] = '_';
        output[matches[0].rm_so + 2 + offset] = tolower((unsigned char)output[matches[0].rm_so + 2 + offset]);
        offset += 2 + (matches[1].rm_eo - matches[1].rm_so);
    }

    regfree(&regex);
    return output;
}

int main() {
    const char *test_cases[] = {"ThisIsCamelCase", "google_assistant", "chrome_cast", "quad_core"};
    const char *expected_outputs[] = {"this_is_camel_case", "google_assistant", "chrome_cast", "quad_core"};
    for (int i = 0; i < 4; ++i) {
        char *result = camel_to_snake(test_cases[i]);
        if (result != NULL) {
            if (strcmp(result, expected_outputs[i]) == 0) {
                printf("%s\n", result);
            } else {
                printf("Test case %d failed: expected '%s', got '%s'\n", i, expected_outputs[i], result);
            }
            free(result);
        } else {
            fprintf(stderr, "Error converting string.\n");
        }
    }
    return 0;
}