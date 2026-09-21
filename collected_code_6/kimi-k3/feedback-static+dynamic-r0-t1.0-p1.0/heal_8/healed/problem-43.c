#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_MATCHES 100
#define MAX_MATCH_LEN 256
#define MAX_INPUT_LEN 1024

int find_lowercase_underscore_sequences(const char *input, char matches[][MAX_MATCH_LEN], size_t max_matches) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "[a-z]+(_[a-z]+)+";
    int ret;
    size_t count = 0;
    const char *cursor;
    size_t remaining_len;
    size_t input_len;

    if (input == NULL || matches == NULL || max_matches == 0 || max_matches > MAX_MATCHES) {
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len == 0 || input_len >= MAX_INPUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    remaining_len = input_len;

    while (count < max_matches && remaining_len > 0) {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match[0].rm_so < 0 || match[0].rm_eo < 0 || match[0].rm_eo <= match[0].rm_so) {
            regfree(&regex);
            return -1;
        }

        size_t start = (size_t)match[0].rm_so;
        size_t end = (size_t)match[0].rm_eo;

        if (end > remaining_len || start >= remaining_len) {
            regfree(&regex);
            return -1;
        }

        size_t length = end - start;

        if (length >= MAX_MATCH_LEN) {
            regfree(&regex);
            return -1;
        }

        memcpy(matches[count], cursor + start, length);
        matches[count][length] = '\0';
        count++;

        if (end >= remaining_len) {
            break;
        }

        cursor += end;
        remaining_len -= end;
    }

    regfree(&regex);
    return (int)count;
}

int main(void) {
    char input[MAX_INPUT_LEN];
    char matches[MAX_MATCHES][MAX_MATCH_LEN];
    int result;
    size_t input_len;

    memset(input, 0, sizeof(input));
    memset(matches, 0, sizeof(matches));

    printf("Enter a string: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input_len = strcspn(input, "\n");
    if (input_len >= sizeof(input)) {
        input_len = sizeof(input) - 1;
    }
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
    for (int i = 0; i < result && i < MAX_MATCHES; i++) {
        printf("%d: %s\n", i + 1, matches[i]);
    }

    return EXIT_SUCCESS;
}