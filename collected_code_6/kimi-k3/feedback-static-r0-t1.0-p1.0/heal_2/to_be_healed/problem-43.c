#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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

        int start = match[0].rm_so;
        int end = match[0].rm_eo;
        int length = end - start;

        if (length >= MAX_MATCH_LEN) {
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(matches[count], cursor + start, (size_t)length);
        matches[count][length] = '\0';
        count++;

        cursor += end;
    }

    regfree(&regex);
    return count;
}

int main(void) {
    char *input = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*matches)[MAX_MATCH_LEN] = NULL;
    int result;
    size_t input_len;

    input = (char *)malloc(MAX_INPUT_LEN);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    matches = (char (*)[MAX_MATCH_LEN])malloc(MAX_MATCHES * sizeof(*matches));
    if (matches == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(matches);
        free(input);
        return EXIT_FAILURE;
    }

    input_len = strcspn(input, "\n");
    input[input_len] = '\0';

    result = find_lowercase_underscore_sequences(input, matches, MAX_MATCHES);
    if (result < 0) {
        fprintf(stderr, "Error processing regex\n");
        free(matches);
        free(input);
        return EXIT_FAILURE;
    }

    printf("Found %d sequence(s):\n", result);
    for (int i = 0; i < result; i++) {
        printf("%d: %s\n", i + 1, matches[i]);
    }

    free(matches);
    free(input);

    return EXIT_SUCCESS;
}