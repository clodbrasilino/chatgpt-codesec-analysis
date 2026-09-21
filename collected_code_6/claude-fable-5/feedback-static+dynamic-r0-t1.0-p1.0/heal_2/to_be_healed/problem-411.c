#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  */

char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    const char *cursor;
    size_t out_pos;
    size_t len;
    size_t capacity;
    size_t remaining;
    int status;

    if (input == NULL) {
        return NULL;
    }

    status = regcomp(&regex, "_([a-zA-Z])", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    capacity = len + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    out_pos = 0U;
    cursor = input;

    while (regexec(&regex, cursor, 1U, &match, 0) == 0) {
        if (match.rm_so > 0) {
            if (out_pos + (size_t)match.rm_so >= capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out_pos, cursor, (size_t)match.rm_so);
            out_pos += (size_t)match.rm_so;
        }
        if (out_pos + 1U >= capacity) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result[out_pos] = (char)toupper((unsigned char)cursor[match.rm_so + 1]);
        out_pos++;
        cursor += match.rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    remaining = strlen(cursor);
    if (out_pos + remaining >= capacity) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + out_pos, cursor, remaining);
    out_pos += remaining;
    result[out_pos] = '\0';

    if (out_pos > 0U) {
        result[0] = (char)toupper((unsigned char)result[0]);
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *tests[] = {
        "hello_world_example",
        "convert_this_snake_case",
        "single",
        "a_b_c_d"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        char *camel = snake_to_camel(tests[i]);
        if (camel == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (printf("%s -> %s\n", tests[i], camel) < 0) {
            free(camel);
            return EXIT_FAILURE;
        }
        free(camel);
    }

    return EXIT_SUCCESS;
}