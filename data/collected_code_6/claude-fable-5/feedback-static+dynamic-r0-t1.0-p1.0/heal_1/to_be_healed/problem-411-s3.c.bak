#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  */

char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t match[2];
    char *result;
    size_t len;
    size_t out_pos;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "_([a-zA-Z0-9])", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    cursor = input;
    out_pos = 0U;

    while (regexec(&regex, cursor, 2U, match, 0) == 0) {
        size_t prefix_len = (size_t)match[0].rm_so;

        memcpy(&result[out_pos], cursor, prefix_len);
        out_pos += prefix_len;

        result[out_pos] = (char)toupper((unsigned char)cursor[match[1].rm_so]);
        out_pos += 1U;

        cursor += match[0].rm_eo;
    }

    {
        size_t rest_len = strlen(cursor);
        memcpy(&result[out_pos], cursor, rest_len);
        out_pos += rest_len;
    }

    result[out_pos] = '\0';
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *tests[] = {
        "hello_world",
        "convert_snake_case_to_camel_case",
        "already",
        "multiple__underscores",
        "trailing_"
    };
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < count; i++) {
        char *converted = snake_to_camel(tests[i]);
        if (converted == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[i], converted);
        free(converted);
    }

    return EXIT_SUCCESS;
}