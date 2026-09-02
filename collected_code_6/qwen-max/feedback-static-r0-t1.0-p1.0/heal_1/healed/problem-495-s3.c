#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_lowercase_substrings(char *str) {
    regex_t reg;
    regmatch_t pmatch[1];

    if (regcomp(&reg, "[a-z]+", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&reg, str, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;

        memmove(str + start, str + end, strlen(str + end) + 1);
    }

    regfree(&reg);
}

int main() {
    char str[] = "TesTIngStrIng";

    remove_lowercase_substrings(str);

    printf("Result: %s\n", str);

    return 0;
}