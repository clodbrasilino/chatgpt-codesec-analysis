#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_five_char_words(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[a-zA-Z]{5}\\b";
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[256];
        regerror(result, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return;
    }

    const char *cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        char *word = (char *)malloc(match.rm_eo - match.rm_so + 1);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(word, cursor + match.rm_so, match.rm_eo - match.rm_so);
        word[match.rm_eo - match.rm_so] = '\0';
        printf("%s\n", word);
        free(word);
        cursor += match.rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    input[strcspn(input, "\n")] = '\0';

    find_five_char_words(input);

    return EXIT_SUCCESS;
}