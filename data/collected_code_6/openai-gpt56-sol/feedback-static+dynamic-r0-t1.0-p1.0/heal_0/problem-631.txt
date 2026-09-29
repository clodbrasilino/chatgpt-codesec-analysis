#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_whitespace_and_underscores(char *string)
{
    regex_t whitespace_regex;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&whitespace_regex, "[[:space:]]", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    for (char *current = string; *current != '\0'; ++current) {
        char candidate[2] = {*current, '\0'};

        if (*current == '_') {
            *current = ' ';
        } else if (regexec(&whitespace_regex, candidate, 0, NULL, 0) == 0) {
            *current = '_';
        }
    }

    regfree(&whitespace_regex);
    return 0;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Input exceeds the maximum supported length.\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (replace_whitespace_and_underscores(input) != 0) {
        fprintf(stderr, "Unable to process the input.\n");
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        perror("puts");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}