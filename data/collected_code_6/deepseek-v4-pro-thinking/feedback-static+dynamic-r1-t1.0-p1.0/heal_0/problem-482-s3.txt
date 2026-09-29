#include <stdio.h>
#include <regex.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t match[1];
    const char *p = str;
    int reti;

    reti = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (reti != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        printf("%.*s\n", (int)(match[0].rm_eo - match[0].rm_so), p + match[0].rm_so);
        p += match[0].rm_eo;
        if (match[0].rm_eo == match[0].rm_so) {
            p++;
        }
    }

    regfree(&regex);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    find_sequences(argv[1]);
    return 0;
}