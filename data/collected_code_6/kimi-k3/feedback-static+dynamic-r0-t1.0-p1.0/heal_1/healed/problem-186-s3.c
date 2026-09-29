#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literal_strings(const char *text, const char *pattern) {
    regex_t regex;
    int result;
    int found = 0;

    if (text == NULL || pattern == NULL) {
        fprintf(stderr, "Error: NULL input provided\n");
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        size_t error_size = regerror(result, &regex, NULL, 0);
        char *error_buffer = malloc(error_size);
        if (error_buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return -1;
        }
        regerror(result, &regex, error_buffer, error_size);
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        free(error_buffer);
        return -1;
    }

    result = regexec(&regex, text, 0, NULL, 0);
    if (result == 0) {
        found = 1;
    } else if (result != REG_NOMATCH) {
        size_t error_size = regerror(result, &regex, NULL, 0);
        char *error_buffer = malloc(error_size);
        if (error_buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return -1;
        }
        regerror(result, &regex, error_buffer, error_size);
        fprintf(stderr, "Regex execution failed: %s\n", error_buffer);
        free(error_buffer);
        found = -1;
    }

    regfree(&regex);
    return found;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *patterns[] = {
        "quick|lazy",
        "cat|bird",
        "fox"
    };
    size_t num_patterns = sizeof(patterns) / sizeof(patterns[0]);
    size_t i;

    for (i = 0; i < num_patterns; i++) {
        int result = search_literal_strings(text, patterns[i]);
        if (result == 1) {
            printf("Pattern '%s' found in text.\n", patterns[i]);
        } else if (result == 0) {
            printf("Pattern '%s' not found in text.\n", patterns[i]);
        } else {
            printf("Error searching for pattern '%s'.\n", patterns[i]);
        }
    }

    return 0;
}