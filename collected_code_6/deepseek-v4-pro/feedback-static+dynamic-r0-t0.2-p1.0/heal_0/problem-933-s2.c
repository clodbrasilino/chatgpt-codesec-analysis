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
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        
        memcpy(result + dst_pos, remaining, match_start + 1);
        dst_pos += match_start + 1;
        
        result[dst_pos++] = '_';
        result[dst_pos++] = remaining[match_start + 1] + 32;
        
        src_pos += match_end;
        remaining += match_end;
    }

    if (src_pos < input_len) {
        size_t remaining_len = input_len - src_pos;
        memcpy(result + dst_pos, remaining, remaining_len);
        dst_pos += remaining_len;
    }

    result[dst_pos] = '\0';
    regfree(&regex);

    char *final_result = malloc(dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }
    
    memcpy(final_result, result, dst_pos + 1);
    free(result);
    
    return final_result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "snakeCaseTest",
        "already_snake",
        "UPPERCASE",
        "mixedCASEString",
        "with123Numbers",
        "a",
        "",
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