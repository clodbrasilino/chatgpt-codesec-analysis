#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_MATCHES 100
#define MAX_LENGTH 256

int extract_quoted_values(const char *input, char matches[][MAX_LENGTH], int max_matches) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "\"([^\"]*)\"";
    int count = 0;
    const char *cursor = input;
    int ret;
    size_t remaining_len;

    if (input == NULL || matches == NULL || max_matches <= 0 || max_matches > MAX_MATCHES) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    remaining_len = strlen(input);

    while (count < max_matches && remaining_len > 0) {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret != 0) {
            break;
        }

        if (match[0].rm_so == -1 || match[0].rm_eo == -1) {
            break;
        }

        if ((size_t)match[0].rm_eo > remaining_len || (size_t)match[0].rm_so >= remaining_len) {
            break;
        }

        regoff_t start = match[0].rm_so + 1;
        regoff_t end = match[0].rm_eo - 1;
        regoff_t length = end - start;

        if (length < 0 || length >= MAX_LENGTH) {
            size_t advance = (size_t)match[0].rm_eo;
            if (advance > remaining_len) {
                break;
            }
            cursor += advance;
            remaining_len -= advance;
            continue;
        }

        /* Possible weaknesses found:
         *  If condition 'remaining_len<(unsigned long)match[0].rm_eo' is true, the function will return/exit
         */
        if (remaining_len < (size_t)match[0].rm_eo) {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(matches[count], cursor + start, (size_t)length);
        matches[count][length] = '\0';
        count++;

        /* Possible weaknesses found:
         *  'advance' is assigned value '(unsigned long)match[0].rm_eo' here.
         */
        size_t advance = (size_t)match[0].rm_eo;
        /* Possible weaknesses found:
         *  Testing identical condition 'remaining_len<(unsigned long)match[0].rm_eo'
         *  Identical condition 'remaining_len<(unsigned long)match[0].rm_eo', second condition is always false [identicalConditionAfterEarlyExit]
         */
        if (advance > remaining_len) {
            break;
        }
        cursor += advance;
        remaining_len -= advance;
    }

    regfree(&regex);
    return count;
}

int main(void) {
    const char *input = "The quick \"brown fox\" jumps over the \"lazy dog\" near the \"river bank\"";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char results[MAX_MATCHES][MAX_LENGTH];
    int num_matches;
    int i;

    memset(results, 0, sizeof(results));

    num_matches = extract_quoted_values(input, results, MAX_MATCHES);

    if (num_matches < 0) {
        fprintf(stderr, "Error processing regex\n");
        return EXIT_FAILURE;
    }

    printf("Found %d matches:\n", num_matches);
    for (i = 0; i < num_matches && i < MAX_MATCHES; i++) {
        printf("%d: %s\n", i + 1, results[i]);
    }

    return EXIT_SUCCESS;
}