#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "[A-Z][a-z]+";
    int ret;
    const char *cursor = str;

    if (!str) {
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        int start = match[0].rm_so;
        int end = match[0].rm_eo;

        /* Possible weaknesses found:
         *  Assuming that condition 'end<=start' is not redundant
         */
        if (start < 0 || end < 0 || end <= start) {
            cursor++;
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(cursor);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if ((size_t)start >= remaining || (size_t)end > remaining) {
            cursor++;
            continue;
        }

        /* Possible weaknesses found:
         *  Assignment 'match_len=end-start', assigned value is greater than 0
         */
        int match_len = end - start;
        /* Possible weaknesses found:
         *  Condition 'match_len<=0' is always false [knownConditionTrueFalse]
         *  Condition 'match_len<=0' is always false
         */
        if (match_len <= 0) {
            cursor++;
            continue;
        }

        size_t len = (size_t)match_len;

        if (len > SIZE_MAX - 1) {
            cursor++;
            continue;
        }

        char *seq = (char *)malloc(len + 1);
        if (!seq) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }

        size_t copy_start = (size_t)start;
        size_t copy_len = len;
        if (copy_start + copy_len > remaining) {
            free(seq);
            cursor++;
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(seq, cursor + copy_start, copy_len);
        seq[copy_len] = '\0';
        printf("%s\n", seq);
        free(seq);
        cursor += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "Hello World This Is A Test String with Some Uppercase Letters";
    find_sequences(text);
    return 0;
}