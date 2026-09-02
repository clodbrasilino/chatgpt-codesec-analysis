#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void add_spaces_between_capital_words(char *input) {
    regex_t reg;
    regmatch_t matches[1];
    const char *pattern = "([A-Z][^ ]*)";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) return;

    int offset = 0;
    size_t len = strlen(input);
    char *temp = malloc(len * 2 + 1);
    if (temp == NULL) return;
    strcpy(temp, input);

    while (regexec(&reg, temp + offset, 1, matches, 0) == 0) {
        size_t start = matches[0].rm_so + offset;
        memmove(temp + start + 1, temp + start, len - start + 1);
        temp[start] = ' ';
        len += 1;
        offset = start + 1;
    }

    strcpy(input, temp);
    free(temp);
    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATestString";
    size_t initial_len = strlen(str);
    char *new_str = (char *)malloc(initial_len * 2 + 1);
    if (new_str == NULL) return 1;
    strcpy(new_str, str);
    add_spaces_between_capital_words(new_str);
    printf("%s\n", new_str);
    free(new_str);
    return 0;
}