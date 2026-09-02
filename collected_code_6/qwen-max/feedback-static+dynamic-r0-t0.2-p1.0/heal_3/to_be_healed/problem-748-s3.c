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

    while (regexec(&regex, str, 1, match, 0) == 0) {
        size_t len = strlen(str + match[0].rm_eo);
        /* Possible weaknesses found:
         * ASan: stack-buffer-overflow
         */
        memmove(str + match[0].rm_eo + 1, str + match[0].rm_eo, len + 1);
        str[match[0].rm_eo] = ' ';
    }

    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    insert_spaces(input);
    printf("%s\n", input);
    return 0;
}