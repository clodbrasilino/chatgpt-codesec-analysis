#include <stdio.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char *input) {
    regex_t reg;
    regmatch_t matches[1];
    const char *pattern = "([A-Z][^ ]*)";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) return;

    int offset = 0;
    while (regexec(&reg, input + offset, 1, matches, 0) == 0) {
        size_t start = matches[0].rm_so + offset;
        /* Possible weaknesses found:
         *  Value stored to 'end' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'end' is assigned a value that is never used. [unreadVariable]
         */
        size_t end = matches[0].rm_eo + offset;
        size_t len = strlen(input);
        /* Possible weaknesses found:
         * ASan: stack-buffer-overflow
         */
        memmove(input + start + 1, input + start, len - start + 1);
        input[start] = ' ';
        offset++;
    }

    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATestString";
    add_spaces_between_capital_words(str);
    printf("%s\n", str);
    return 0;
}