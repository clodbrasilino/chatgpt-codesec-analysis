#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t match[1];
    const char pattern[] = "([A-Z][^A-Z]*)";

    char *result = malloc(strlen(str) * 2 + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    *result = '\0';

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        free(result);
        exit(1);
    }

    size_t result_len = 0;
    while (regexec(&regex, str, 1, match, 0) == 0) {
        size_t len = match[0].rm_eo - match[0].rm_so;
        if (result_len + len + 1 < strlen(str) * 2 + 1) {
            strncat(result, str + match[0].rm_so, len);
            result_len += len;
            strncat(result, " ", 1);
            result_len++;
        }
        str += match[0].rm_eo;
    }

    strncpy(str, result, strlen(str) * 2 + 1);
    str[strlen(result)] = '\0';

    free(result);
    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_words(input);
    printf("%s\n", input);
    return 0;
}