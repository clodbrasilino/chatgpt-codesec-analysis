#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int extract_quoted_values(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    int count = 0;
    int result;

    if (input == NULL) {
        return -1;
    }

    result = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    cursor = input;

    while ((result = regexec(&regex, cursor, 2, matches, 0)) == 0) {
        regoff_t match_start = matches[1].rm_so;
        regoff_t match_end = matches[1].rm_eo;
        regoff_t full_match_end = matches[0].rm_eo;
        size_t cursor_length;
        size_t start;
        size_t end;
        size_t advance;
        size_t length;
        char *value;

        /* Possible weaknesses found:
         *  Assuming that condition 'match_end<match_start' is not redundant
         */
        if (match_start < 0 || match_end < match_start ||
            full_match_end <= 0 || matches[0].rm_so < 0) {
            regfree(&regex);
            return -1;
        }

        if ((uintmax_t)match_start > SIZE_MAX ||
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            (uintmax_t)match_end > SIZE_MAX ||
            (uintmax_t)full_match_end > SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         *  start is assigned '(unsigned long)match_start' here.
         */
        start = (size_t)match_start;
        /* Possible weaknesses found:
         *  Assignment 'end=(unsigned long)match_end', assigned value is less than symbolic=start-1
         */
        end = (size_t)match_end;
        advance = (size_t)full_match_end;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        cursor_length = strlen(cursor);

        /* Possible weaknesses found:
         *  Condition 'start>end' is always true
         *  Condition 'start>end' is always true [knownConditionTrueFalse]
         */
        if (start > end || end > cursor_length ||
            advance > cursor_length || advance == 0) {
            regfree(&regex);
            return -1;
        }

        length = end - start;
        if (length == SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        value = malloc(length + 1);
        if (value == NULL) {
            regfree(&regex);
            return -1;
        }

        if (length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(value, cursor + start, length);
        }
        value[length] = '\0';

        if (fwrite(value, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);
        cursor += advance;

        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (count == INT_MAX) {
            regfree(&regex);
            return -1;
        }
        ++count;
    }

    regfree(&regex);
    return result == REG_NOMATCH ? count : -1;
}

int main(int argc, char *argv[])
{
    int count;

    if (argc != 2) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    count = extract_quoted_values(argv[1]);
    if (count < 0) {
        fprintf(stderr, "Failed to extract quoted values\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}