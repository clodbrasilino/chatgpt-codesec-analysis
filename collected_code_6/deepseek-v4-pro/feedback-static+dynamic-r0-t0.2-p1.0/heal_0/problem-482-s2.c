#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *input) {
    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "[A-Z][a-z]+";
    int reti;
    const char *cursor = input;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, cursor, 1, matches, 0) == 0) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        printf("%.*s\n", end - start, cursor + start);
        cursor += end;
        if (*cursor == '\0') break;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "Hello World This Is A Test String With Uppercase And lowercase Letters";
    find_sequences(text);
    return 0;
}