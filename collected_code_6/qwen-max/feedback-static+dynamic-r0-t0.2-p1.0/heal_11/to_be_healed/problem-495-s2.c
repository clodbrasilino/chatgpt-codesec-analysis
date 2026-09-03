#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED | REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        /* Possible weaknesses found:
         *  Value stored to 'len' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        int len = match[0].rm_eo - match[0].rm_so;
        memmove(p + match[0].rm_so, p + match[0].rm_eo, strlen(p + match[0].rm_eo) + 1);
        p += match[0].rm_so;
    }

    regfree(&regex);
}

int main() {
    char str[] = "ThiS iS a TeSt StrinG";
    remove_lowercase_substrings(str);
    printf("%s\n", str);
    return 0;
}