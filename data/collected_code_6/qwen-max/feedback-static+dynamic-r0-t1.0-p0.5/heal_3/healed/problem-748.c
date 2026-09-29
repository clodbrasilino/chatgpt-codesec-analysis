#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces_between_capital_words(char *str, size_t str_len) {
    regex_t regex;
    regmatch_t matches[2];
    char pattern[] = "([A-Z][^A-Z]*)";
    char replacement[] = " \\1";
    char result[256] = "";
    int start = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, str + start, 2, matches, 0) == 0) {
        int end = matches[0].rm_so + start;
        strncat(result, str + start, end - start);
        strncat(result, replacement, sizeof(replacement) - 2);
        start = matches[0].rm_eo + start;
    }

    strncat(result, str + start, str_len - start - 1);
    strncpy(str, result, str_len - 1);
    str[str_len - 1] = '\0';

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_words(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}