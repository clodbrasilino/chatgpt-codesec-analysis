#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100
#define MAX_LENGTH 256

int extract_quoted_values(const char *input, char matches[][MAX_LENGTH], int max_matches) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "\"([^\"]*)\"";
    int count = 0;
    const char *cursor = input;

    if (input == NULL || matches == NULL || max_matches <= 0) {
        return -1;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    while (count < max_matches && regexec(&regex, cursor, 1, match, 0) == 0) {
        if (match[0].rm_so == -1) {
            break;
        }

        int start = match[0].rm_so + 1;
        int length = match[0].rm_eo - match[0].rm_so - 2;

        if (length >= 0 && length < MAX_LENGTH) {
            strncpy(matches[count], cursor + start, length);
            matches[count][length] = '\0';
            count++;
        }

        cursor += match[0].rm_eo;
    }

    regfree(&regex);
    return count;
}

int main(void) {
    const char *input = "The quick \"brown fox\" jumps over the \"lazy dog\" near the \"river bank\"";
    char results[MAX_MATCHES][MAX_LENGTH];
    int num_matches;

    num_matches = extract_quoted_values(input, results, MAX_MATCHES);

    if (num_matches < 0) {
        fprintf(stderr, "Error processing regex\n");
        return EXIT_FAILURE;
    }

    printf("Found %d matches:\n", num_matches);
    for (int i = 0; i < num_matches; i++) {
        printf("%d: %s\n", i + 1, results[i]);
    }

    return EXIT_SUCCESS;
}