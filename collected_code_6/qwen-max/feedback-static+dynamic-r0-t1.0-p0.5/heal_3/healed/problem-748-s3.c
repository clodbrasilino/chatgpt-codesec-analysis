#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces_between_capital_letters(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([a-z])([A-Z])";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    int pos = 0;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        if (i + 1 < len && islower(str[i]) && isupper(str[i + 1])) {
            memmove(str + i + 2, str + i + 1, len - i);
            str[i + 1] = ' ';
            len++;
            str[len] = '\0';
            i++;
        }
    }

    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_letters(input);
    printf("%s\n", input);
    return 0;
}