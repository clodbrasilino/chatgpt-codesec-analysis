#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void insert_spaces(char *str) {
    regex_t reg;
    regmatch_t match[1];
    char pattern[] = "([A-Z][^A-Z]*)";
    int reti;

    if (regcomp(&reg, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    while (regexec(&reg, str, 1, match, 0) == 0) {
        memmove(str + match[0].rm_eo + 1, str + match[0].rm_eo, strlen(str + match[0].rm_eo) + 1);
        str[match[0].rm_eo] = ' ';
        str += match[0].rm_eo + 1;
    }

    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    insert_spaces(str);
    printf("%s\n", str);
    return 0;
}