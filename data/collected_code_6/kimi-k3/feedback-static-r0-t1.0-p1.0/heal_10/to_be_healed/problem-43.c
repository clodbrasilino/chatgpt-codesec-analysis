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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_buf[128];
    size_t input_len;

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
        size_t offset = (size_t)(cursor - input);
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
        
        /* Possible weaknesses found:
         *  Assuming that condition 'end<=start' is not redundant
         */
        if (start < 0 || end < 0 || end <= start || (size_t)end > input_len - offset) {
            regfree(&regex);
            return -1;
        }
        
        /* Possible weaknesses found:
         *  Assignment 'length=(unsigned long)(end-start)', assigned value is greater than 0
         */
        size_t length = (size_t)(end - start);

        /* Possible weaknesses found:
         *  Condition 'length==0' is always false
         *  Condition 'length==0' is always false [knownConditionTrueFalse]
         */
        if (length == 0 || length >= MAX_MATCH_LEN) {
            fprintf(stderr, "Match length invalid\n");
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         *  Assignment 'copy_len=(length<256-1)?length:256-1', assigned value is less than 1
         */
        size_t copy_len = (length < MAX_MATCH_LEN - 1) ? length : MAX_MATCH_LEN - 1;
        /* Possible weaknesses found:
         *  Condition 'copy_len>0' is always false [knownConditionTrueFalse]
         *  Condition 'copy_len>0' is always false
         */
        if (copy_len < MAX_MATCH_LEN && copy_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(matches[count], cursor + start, copy_len);
            matches[count][copy_len] = '\0';
        } else {
            regfree(&regex);
            return -1;
        }
        
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

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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