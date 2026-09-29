#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_to_capitalized_words(char *str) {
    regex_t regex;
    regmatch_t match[1];
    int offset = 0;

    const char *pattern = "([A-Z][a-zA-Z]*)";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    /* Possible weaknesses found:
     * ASan: SEGV
     */
    while (regexec(&regex, str + offset, 1, match, 0) == 0) {
        if (match[0].rm_so > 0 && str[offset + match[0].rm_so - 1] != ' ') {
            memmove(str + match[0].rm_so + 1 + offset, str + match[0].rm_so + offset, strlen(str + match[0].rm_so + offset) + 1);
            str[offset + match[0].rm_so] = ' ';
        }
        offset += match[0].rm_eo - match[0].rm_so;
    }
    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    add_spaces_to_capitalized_words(str);
    printf("%s\n", str);
    return 0;
}