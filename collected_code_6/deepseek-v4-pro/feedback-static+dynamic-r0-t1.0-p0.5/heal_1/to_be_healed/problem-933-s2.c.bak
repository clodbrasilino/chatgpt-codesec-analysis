#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  */

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
        /* Possible weaknesses found:
         *  Value stored to 'first_end' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'first_end' is assigned a value that is never used. [unreadVariable]
         */
        size_t first_end = matches[1].rm_eo;

        memcpy(result + dst_pos, remaining, match_start);
        dst_pos += match_start;

        result[dst_pos++] = remaining[matches[1].rm_so];
        result[dst_pos++] = '_';
        /* Possible weaknesses found:
         *  Array 'matches[2]' accessed at index 2, which is out of bounds. [arrayIndexOutOfBounds]
         */
        result[dst_pos++] = remaining[matches[2].rm_so] + 32;

        src_pos += match_end;
        remaining += match_end;
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
        "ABC",
        "aB",
        "helloWorld123",
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