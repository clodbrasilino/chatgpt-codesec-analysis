#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_MATCHES 100
#define MAX_MATCH_LEN 256
#define MAX_INPUT_LEN 1024

int find_lowercase_underscore_sequences(const char *input, char matches[][MAX_MATCH_LEN], int max_matches) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "[a-z]+(_[a-z]+)+";
    int ret;
    int count = 0;
    const char *cursor = input;

    if (input == NULL || matches == NULL || max_matches <= 0) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (count < max_matches) {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match[0].rm_so < 0 || match[0].rm_eo < 0 || match[0].rm_eo < match[0].rm_so) {
            regfree(&regex);
            return -1;
        }

        size_t start = (size_t)match[0].rm_so;
        size_t end = (size_t)match[0].rm_eo;
        size_t length = end - start;

        if (length >= MAX_MATCH_LEN || length == 0) {
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(matches[count], cursor + start, length);
        matches[count][length] = '\0';
        count++;

        cursor += end;
    }

    regfree(&regex);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char matches[MAX_MATCHES][MAX_MATCH_LEN];
    int result;

    printf("Enter a string: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t input_len = strcspn(input, "\n");
    input[input_len] = '\0';

    if (input_len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }

    result = find_lowercase_underscore_sequences(input, matches, MAX_MATCHES);
    if (result < 0) {
        fprintf(stderr, "Error processing regex\n");
        return EXIT_FAILURE;
    }

    printf("Found %d sequence(s):\n", result);
    for (int i = 0; i < result; i++) {
        printf("%d: %s\n", i + 1, matches[i]);
    }

    return EXIT_SUCCESS;
}