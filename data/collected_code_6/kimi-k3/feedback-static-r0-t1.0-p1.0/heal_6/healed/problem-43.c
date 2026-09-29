#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
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
    char error_buf[128];
    size_t input_len;
    size_t offset;

    if (input == NULL || matches == NULL || max_matches <= 0 || max_matches > MAX_MATCHES) {
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len == 0 || input_len >= MAX_INPUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buf);
        return -1;
    }

    while (count < max_matches) {
        offset = (size_t)(cursor - input);
        if (offset >= input_len) {
            break;
        }

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
        
        if (start < 0 || end < 0 || end <= start || (size_t)end > input_len - offset) {
            regfree(&regex);
            return -1;
        }
        
        size_t length = (size_t)(end - start);

        if (length == 0 || length >= MAX_MATCH_LEN) {
            fprintf(stderr, "Match length invalid\n");
            regfree(&regex);
            return -1;
        }

        size_t copy_len = (length < MAX_MATCH_LEN - 1) ? length : MAX_MATCH_LEN - 1;
        memcpy(matches[count], cursor + start, copy_len);
        matches[count][copy_len] = '\0';
        
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

    if (MAX_INPUT_LEN == 0 || MAX_MATCHES == 0 || MAX_MATCH_LEN == 0 || 
        MAX_INPUT_LEN > SIZE_MAX / sizeof(char) || 
        MAX_MATCHES > SIZE_MAX / MAX_MATCH_LEN) {
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
    if (input_len >= MAX_INPUT_LEN) {
        input_len = MAX_INPUT_LEN - 1;
    }
    input[input_len] = '\0';

    result = find_lowercase_underscore_sequences(input, matches, MAX_MATCHES);
    if (result < 0) {
        fprintf(stderr, "Error processing regex\n");
        free(matches);
        free(input);
        return EXIT_FAILURE;
    }

    printf("Found %d sequence(s):\n", result);
    for (int i = 0; i < result && i < MAX_MATCHES; i++) {
        printf("%d: %s\n", i + 1, matches[i]);
    }

    free(matches);
    free(input);

    return EXIT_SUCCESS;
}