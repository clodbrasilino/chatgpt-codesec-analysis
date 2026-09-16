#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    int is_space = 0;

    while (src_pos < len) {
        if (str[src_pos] == ' ') {
            if (!is_space) {
                result[dst_pos++] = ' ';
                is_space = 1;
            }
        } else {
            result[dst_pos++] = str[src_pos];
            is_space = 0;
        }
        src_pos++;
    }

    result[dst_pos] = '\0';

    char *shrunk_result = realloc(result, dst_pos + 1);
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "Google  Assistant",
        "Quad   Core",
        "ChromeCast  Built-in",
        "This   is  a    test   string."
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *output = remove_multiple_spaces(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}