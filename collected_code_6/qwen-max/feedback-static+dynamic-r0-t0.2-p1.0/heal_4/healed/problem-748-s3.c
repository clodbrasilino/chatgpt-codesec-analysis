#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void insert_spaces(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([A-Z][^A-Z]*)";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char *new_str = malloc(strlen(str) * 2 + 1);
    if (!new_str) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    strcpy(new_str, str);

    while (regexec(&regex, new_str, 1, match, 0) == 0) {
        size_t len = strlen(new_str + match[0].rm_eo);
        memmove(new_str + match[0].rm_eo + 1, new_str + match[0].rm_eo, len + 1);
        new_str[match[0].rm_eo] = ' ';
    }

    strcpy(str, new_str);
    free(new_str);
    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    insert_spaces(input);
    printf("%s\n", input);
    return 0;
}