#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    char *output = strdup(input);
    int offset = 0;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(output);
        return NULL;
    }

    while (regexec(&regex, output + offset, 2, matches, 0) == 0) {
        memmove(output + matches[1].rm_so + 2 + offset, output + matches[1].rm_so + 1 + offset, strlen(output + matches[1].rm_so + 1 + offset) + 1);
        output[matches[1].rm_so + 1 + offset] = '_';
        output[matches[1].rm_so + 2 + offset] = tolower(output[matches[1].rm_so + 2 + offset]);
        offset += 2;
    }

    int len = strlen(output);
    for (int i = 0; i < len; ++i) {
        if (output[i] == '_' && (i == 0 || output[i-1] == '_')) {
            memmove(output + i, output + i + 1, strlen(output + i + 1) + 1);
            --len;
            --i;
        }
    }

    regfree(&regex);
    return output;
}

int main() {
    const char *test_cases[] = {"ThisIsCamelCase", "chrome_cast", "quad_core", "google_assistant"};
    const char *expected[] = {"this_is_camel_case", "chrome_cast", "quad_core", "google_assistant"};

    for (int i = 0; i < 4; i++) {
        char *result = camel_to_snake(test_cases[i]);
        if (result != NULL) {
            if (strcmp(result, expected[i]) == 0) {
                printf("%s\n", result);
            } else {
                fprintf(stderr, "Test case %d failed: expected '%s', got '%s'\n", i, expected[i], result);
            }
            free(result);
        } else {
            fprintf(stderr, "Error converting string.\n");
        }
    }
    return 0;
}