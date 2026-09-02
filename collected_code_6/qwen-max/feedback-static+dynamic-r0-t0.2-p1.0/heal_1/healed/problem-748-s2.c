#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char *str, size_t str_size) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([A-Z][^A-Z]*)";
    char result[256] = "";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    while (regexec(&regex, str, 1, match, 0) == 0) {
        size_t len = match[0].rm_eo - match[0].rm_so;
        strncat(result, str + match[0].rm_so, len < sizeof(result) - strlen(result) - 1 ? len : sizeof(result) - strlen(result) - 1);
        strncat(result, " ", sizeof(result) - strlen(result) - 1 > 1 ? 1 : 0);
        str += match[0].rm_eo;
    }

    if (strlen(result) < str_size) {
        strcpy(str, result);
    } else {
        strncpy(str, result, str_size - 1);
        str[str_size - 1] = '\0';
    }

    regfree(&regex);
}

int main() {
    char input[256] = "HelloWorldThisIsATest";
    add_spaces_between_capital_words(input, sizeof(input));
    printf("%s\n", input);
    return 0;
}