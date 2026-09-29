#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void add_spaces_between_capital_letters(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([a-z])([A-Z])";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return;
    }

    size_t len = 0;
    while (str[len] != '\0') len++;

    char *new_str = malloc((len * 2 + 1) * sizeof(char));
    if (!new_str) {
        regfree(&regex);
        return;
    }

    size_t new_len = 0;
    for (size_t i = 0; str[i] != '\0'; i++, new_len++) {
        new_str[new_len] = str[i];
    }
    new_str[new_len] = '\0';

    size_t pos = 0;
    while (regexec(&regex, new_str + pos, 1, match, 0) == 0) {
        int start = pos + match[0].rm_so;
        int end = pos + match[0].rm_eo;

        memmove(new_str + start + 2, new_str + start, strlen(new_str + start) + 1);
        new_str[start] = ' ';
        new_str[start + 1] = new_str[end];
        pos = start + 2;
    }

    size_t final_len = 0;
    while (new_str[final_len] != '\0') final_len++;
    strncpy(str, new_str, final_len + 1);
    free(new_str);
    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_letters(input);
    printf("%s\n", input);
    return 0;
}