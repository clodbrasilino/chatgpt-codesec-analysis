#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100

void add_spaces(char *str) {
    regex_t regexCompiled;
    regmatch_t groupArray[MAX_MATCHES];
    char *cursor = str;

    if (regcomp(&regexCompiled, "[A-Z]", REG_EXTENDED)) {
        printf("Could not compile regular expression.\n");
        return;
    };

    while (!regexec(&regexCompiled, cursor, MAX_MATCHES, groupArray, 0)) {
        int offset = groupArray[0].rm_eo;

        memmove(cursor + offset + 1, cursor + offset, strlen(cursor + offset) + 1);
        cursor[offset] = ' ';

        cursor += offset + 1;
    }

    regfree(&regexCompiled);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    printf("Before: %s\n", str);
    add_spaces(str);
    printf("After: %s\n", str);
    return 0;
}