#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

int extract_max_number(const char *input, long *result)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    /* Possible weaknesses found:
     *  The scope of the variable 'value' can be reduced. [variableScope]
     */
    long value;
    long max_value = LONG_MIN;
    int found = 0;
    int rc;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;
    char *endptr;

    if (input == NULL || result == NULL) {
        return -1;
    }

    rc = regcomp(&regex, "-?[0-9]+", REG_EXTENDED);
    if (rc != 0) {
        return -1;
    }

    cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        len = (size_t)(match.rm_eo - match.rm_so);
        if (len >= sizeof(buffer)) {
            regfree(&regex);
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, cursor + match.rm_so, len);
        buffer[len] = '\0';

        errno = 0;
        value = strtol(buffer, &endptr, 10);
        if (errno == ERANGE || endptr == buffer || *endptr != '\0') {
            regfree(&regex);
            return -1;
        }

        if (!found || value > max_value) {
            max_value = value;
            found = 1;
        }

        cursor += match.rm_eo;
        if (match.rm_eo == match.rm_so) {
            if (*cursor == '\0') {
                break;
            }
            cursor++;
        }
    }

    regfree(&regex);

    if (!found) {
        return -1;
    }

    *result = max_value;
    return 0;
}

int main(void)
{
    const char *test = "abc 42 def -17 ghi 1000 jkl 999";
    long max_value;

    if (extract_max_number(test, &max_value) != 0) {
        fprintf(stderr, "No numeric value found or error occurred\n");
        return EXIT_FAILURE;
    }

    printf("Maximum numeric value: %ld\n", max_value);
    return EXIT_SUCCESS;
}