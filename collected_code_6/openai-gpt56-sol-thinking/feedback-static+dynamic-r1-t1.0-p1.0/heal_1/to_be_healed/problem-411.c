#include <ctype.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  */

char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    char *output;
    size_t input_length;
    size_t remaining;
    size_t written = 0;
    int result;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        return NULL;
    }

    result = regcomp(&regex, "_+([[:alnum:]])", REG_EXTENDED);
    if (result != 0) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    remaining = input_length;

    for (;;) {
        size_t match_start;
        size_t match_end;
        size_t capture_start;
        size_t capture_end;

        result = regexec(&regex, cursor, 2, matches, 0);
        if (result == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + written, cursor, remaining);
            written += remaining;
            break;
        }

        if (result != 0 ||
            matches[0].rm_so < 0 ||
            matches[0].rm_eo < 0 ||
            matches[1].rm_so < 0 ||
            matches[1].rm_eo < 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        match_start = (size_t)matches[0].rm_so;
        match_end = (size_t)matches[0].rm_eo;
        capture_start = (size_t)matches[1].rm_so;
        capture_end = (size_t)matches[1].rm_eo;

        if (match_start > match_end ||
            match_end > remaining ||
            capture_start < match_start ||
            capture_end > match_end ||
            capture_end - capture_start != 1 ||
            match_start > input_length - written ||
            written + match_start >= input_length) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + written, cursor, match_start);
        written += match_start;
        output[written++] = (char)toupper((unsigned char)cursor[capture_start]);

        cursor += match_end;
        remaining -= match_end;
    }

    output[written] = '\0';
    regfree(&regex);
    return output;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *camel_case;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1]);
    if (camel_case == NULL) {
        if (fputs("Conversion failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (fputs(camel_case, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}