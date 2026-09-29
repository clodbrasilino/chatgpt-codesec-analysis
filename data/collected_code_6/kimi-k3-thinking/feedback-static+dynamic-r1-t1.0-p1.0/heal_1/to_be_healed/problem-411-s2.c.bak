#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  */

char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t match[2];
    char *result;
    const char *cursor;
    size_t len;
    size_t ri;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "_([a-zA-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    len = strlen(input);
    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    ri = 0;
    cursor = input;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 2, match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strlen(cursor);
            memcpy(result + ri, cursor, remaining);
            ri += remaining;
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        memcpy(result + ri, cursor, (size_t)match[0].rm_so);
        ri += (size_t)match[0].rm_so;
        result[ri++] = (char)toupper((unsigned char)cursor[match[1].rm_so]);
        cursor += match[0].rm_eo;
    }

    result[ri] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *tests[] = {
        "convert_this_snake_case_string",
        "hello_world_example",
        "another_test_case",
        "nounderscores",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *camel = snake_to_camel(tests[i]);
        if (camel == NULL) {
            fprintf(stderr, "Conversion failed for input: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[i], camel);
        free(camel);
    }

    return EXIT_SUCCESS;
}