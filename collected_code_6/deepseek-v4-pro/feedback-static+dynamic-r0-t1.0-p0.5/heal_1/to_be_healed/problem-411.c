#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  */

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "_([a-z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t len = strlen(snake);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *cursor = snake;

    while (src_pos < len && regexec(&regex, cursor, 2, matches, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t letter_pos = matches[1].rm_so;

        if (match_start > 0) {
            memcpy(result + dst_pos, cursor, match_start);
            dst_pos += match_start;
        }

        result[dst_pos++] = cursor[letter_pos] - 32;

        cursor += match_end;
        src_pos += match_end;
    }

    if (src_pos < len) {
        strcpy(result + dst_pos, cursor);
    } else {
        result[dst_pos] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "already_camel",
        "multiple__underscores",
        "trailing_underscore_",
        "_leading_underscore",
        "single",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *camel = snake_to_camel(test_cases[i]);
        if (camel != NULL) {
            printf("%s -> %s\n", test_cases[i], camel);
            free(camel);
        } else {
            printf("%s -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}