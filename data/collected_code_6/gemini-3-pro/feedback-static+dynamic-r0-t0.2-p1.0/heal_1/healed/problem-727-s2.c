#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 8192

int remove_special_characters(const char *input, char **output) {
    if (input == NULL || output == NULL) {
        return -1;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    size_t len = strnlen(input, MAX_INPUT_LEN);
    *output = (char *)malloc(len + 1);
    if (*output == NULL) {
        regfree(&regex);
        return -1;
    }

    size_t out_idx = 0;
    regmatch_t pmatch[1];
    const char *cursor = input;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0 && cursor < input + len) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        for (size_t i = 0; i < match_start; ++i) {
            if (out_idx < len) {
                (*output)[out_idx++] = cursor[i];
            }
        }

        cursor += match_end;
    }

    while (*cursor != '\0' && out_idx < len && cursor < input + len) {
        (*output)[out_idx++] = *cursor++;
    }

    (*output)[out_idx] = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    if (remove_special_characters(input, &output) == 0) {
        printf("Original: %s\n", input);
        printf("Cleaned:  %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}