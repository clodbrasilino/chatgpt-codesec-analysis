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

static char *snake_to_camel(const char *input)
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
        regoff_t start = match[0].rm_so;
        regoff_t char_pos = match[1].rm_so;

        if (start > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(&result[out_pos], cursor, (size_t)start);
            out_pos += (size_t)start;
        }

        result[out_pos] = (char)toupper((unsigned char)cursor[char_pos]);
        out_pos++;

        cursor += match[0].rm_eo;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(cursor);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(&result[out_pos], cursor, remaining);
        out_pos += remaining;
    }

    result[out_pos] = '\0';
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *tests[] = {
        "hello_world",
        "snake_case_string",
        "already",
        "multi_word_example_test"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    int status = EXIT_SUCCESS;

    for (i = 0U; i < count; i++) {
        char *converted = snake_to_camel(tests[i]);

        if (converted == NULL) {
            if (fprintf(stderr, "Conversion failed for: %s\n", tests[i]) < 0) {
                status = EXIT_FAILURE;
                break;
            }
            status = EXIT_FAILURE;
            continue;
        }

        if (printf("%s -> %s\n", tests[i], converted) < 0) {
            free(converted);
            status = EXIT_FAILURE;
            break;
        }

        free(converted);
    }

    return status;
}