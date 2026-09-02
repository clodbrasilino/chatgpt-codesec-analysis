#include <stdio.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char *input) {
    regex_t reg;
    regmatch_t matches[1];
    const char *pattern = "([A-Z][^ ]*)";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) return;

    while (regexec(&reg, input, 1, matches, 0) == 0) {
        memmove(input + matches[0].rm_eo, input + matches[0].rm_so, strlen(input + matches[0].rm_so) + 1);
        input[matches[0].rm_so] = ' ';
        input++;
    }

    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATestString";
    add_spaces_between_capital_words(str);
    printf("%s\n", str);
    return 0;
}