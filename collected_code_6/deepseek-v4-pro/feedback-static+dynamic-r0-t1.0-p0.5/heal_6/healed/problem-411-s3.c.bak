#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "_([a-zA-Z])";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *cursor = input;

    while (src_pos < len && regexec(&regex, cursor, 2, matches, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t char_pos = matches[1].rm_so;

        if (match_start > 0) {
            memcpy(result + dst_pos, cursor, match_start);
            dst_pos += match_start;
        }

        if (char_pos < match_end) {
            if (dst_pos == 0) {
                result[dst_pos++] = tolower((unsigned char)cursor[char_pos]);
            } else {
                result[dst_pos++] = toupper((unsigned char)cursor[char_pos]);
            }
        }

        cursor += match_end;
        src_pos += match_end;
    }

    if (src_pos < len) {
        size_t remaining = len - src_pos;
        memcpy(result + dst_pos, cursor, remaining);
        dst_pos += remaining;
    }

    result[dst_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "alreadyCamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "with_1_number_2",
        "",
        "a",
        "_",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted != NULL) {
            printf("\"%s\" -> \"%s\"\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("\"%s\" -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}