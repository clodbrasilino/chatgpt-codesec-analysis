#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "([a-z0-9])([A-Z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char *result = malloc(input_len * 2 + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *remaining = input;

    while (src_pos < input_len && regexec(&regex, remaining, 2, matches, 0) == 0) {
        size_t match_end = matches[0].rm_eo;
        size_t first_end = matches[1].rm_eo;

        memcpy(result + dst_pos, remaining, first_end);
        dst_pos += first_end;
        result[dst_pos++] = '_';
        result[dst_pos++] = remaining[first_end] + ('a' - 'A');

        src_pos += match_end;
        remaining = input + src_pos;
    }

    if (src_pos < input_len) {
        memcpy(result + dst_pos, remaining, input_len - src_pos);
        dst_pos += input_len - src_pos;
    }

    result[dst_pos] = '\0';
    regfree(&regex);

    char *final_result = realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "thisIsATest",
        "already_snake",
        "with123Numbers",
        "UPPERCASE",
        "",
        "a",
        "A",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = camel_to_snake(test_cases[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}