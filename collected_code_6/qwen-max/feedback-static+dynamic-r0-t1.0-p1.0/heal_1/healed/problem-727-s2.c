#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_non_alphanumeric(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[^a-zA-Z0-9]";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        memmove(str + pmatch[0].rm_so, str + pmatch[0].rm_eo, strlen(str + pmatch[0].rm_eo) + 1);
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    remove_non_alphanumeric(input);

    printf("%s\n", input);

    return EXIT_SUCCESS;
}