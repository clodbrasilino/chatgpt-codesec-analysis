#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>

#define MAX_MATCHES 100
#define MAX_LENGTH 256

int extract_quoted_values(const char *input, char matches[][MAX_LENGTH], int max_matches) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "\"([^\"]*)\"";
    int count = 0;
    const char *cursor = input;
    int ret;

    if (input == NULL || matches == NULL || max_matches <= 0 || max_matches > MAX_MATCHES) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (count < max_matches) {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret != 0) {
            break;
        }

        if (match[0].rm_so == -1 || match[0].rm_eo == -1) {
            break;
        }

        regoff_t start = match[0].rm_so + 1;
        regoff_t end = match[0].rm_eo - 1;
        regoff_t length = end - start;

        if (length < 0 || length >= MAX_LENGTH) {
            cursor += match[0].rm_eo;
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(cursor) < (size_t)match[0].rm_eo) {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(matches[count], cursor + start, (size_t)length);
        matches[count][length] = '\0';
        count++;

        cursor += match[0].rm_eo;
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