#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

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

    if (src_pos < input_len && isupper((unsigned char)remaining[0])) {
        result[dst_pos++] = tolower((unsigned char)remaining[0]);
        src_pos++;
        remaining++;
    }

    while (src_pos < input_len && regexec(&regex, remaining, 2, matches, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;

        memcpy(result + dst_pos, remaining, match_start);
        dst_pos += match_start;

        result[dst_pos++] = tolower((unsigned char)remaining[matches[1].rm_so]);
        result[dst_pos++] = '_';
        result[dst_pos++] = tolower((unsigned char)remaining[matches[1].rm_eo]);

        src_pos += match_end;
        remaining += match_end;
    }

    if (src_pos < input_len) {
        memcpy(result + dst_pos, remaining, input_len - src_pos);
        dst_pos += input_len - src_pos;
    }

    result[dst_pos] = '\0';
    regfree(&regex);

    for (size_t i = 0; i < dst_pos; i++) {
        result[i] = tolower((unsigned char)result[i]);
    }

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
        "ABC",
        "aB",
        "helloWorld123",
        "GoogleAssistant",
        "ChromeCast",
        "QuadCore",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = camel_to_snake(test_cases[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> conversion failed\n", test_cases[i]);
        }
    }

    return 0;
}