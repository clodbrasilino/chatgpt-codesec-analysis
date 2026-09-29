#include <stdio.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char *input) {
    regex_t reg;
    regmatch_t matches[1];
    const char *pattern = "([A-Z][^ ]*)";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) return;

    int offset = 0, added_chars = 0;
    size_t len = strlen(input);
    while (regexec(&reg, input + offset, 1, matches, 0) == 0) {
        size_t start = matches[0].rm_so + offset + added_chars;
        /* Possible weaknesses found:
         * ASan: stack-buffer-overflow
         */
        memmove(input + start + 1, input + start, len - start + 1 - added_chars);
        input[start] = ' ';
        offset = start + 1 - added_chars;
        added_chars++;
    }

    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATestString";
    add_spaces_between_capital_words(str);
    printf("%s\n", str);
    return 0;
}