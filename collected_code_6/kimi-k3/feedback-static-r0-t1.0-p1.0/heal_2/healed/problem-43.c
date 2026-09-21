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
    char error_buf[128];

    if (input == NULL || matches == NULL || max_matches <= 0) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buf);
        return -1;
    }

    while (count < max_matches) {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            regerror(ret, &regex, error_buf, sizeof(error_buf));
            fprintf(stderr, "Regex execution failed: %s\n", error_buf);
            regfree(&regex);
            return -1;
        }

        regoff_t start = match[0].rm_so;
        regoff_t end = match[0].rm_eo;
        
        if (start < 0 || end < 0 || end <= start) {
            regfree(&regex);
            return -1;
        }
        
        size_t length = (size_t)(end - start);

        if (length >= MAX_MATCH_LEN) {
            fprintf(stderr, "Match too long for buffer\n");
            regfree(&regex);
            return -1;
        }

        strncpy(matches[count], cursor + start, length);
        matches[count][length] = '\0';
        count++;

        cursor += end;
    }

    regfree(&regex);
    return count;
}

int main(void) {
    char *input = NULL;
    char (*matches)[MAX_MATCH_LEN] = NULL;
    int result;
    size_t input_len;

    if (MAX_INPUT_LEN == 0 || MAX_MATCHES == 0 || MAX_MATCH_LEN == 0) {
        fprintf(stderr, "Invalid configuration\n");
        return EXIT_FAILURE;
    }

    input = (char *)calloc(MAX_INPUT_LEN, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    matches = (char (*)[MAX_MATCH_LEN])calloc(MAX_MATCHES, MAX_MATCH_LEN);
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