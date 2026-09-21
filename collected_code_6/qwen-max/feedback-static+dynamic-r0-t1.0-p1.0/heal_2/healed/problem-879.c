#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int match_pattern(const char *str) {
    regex_t regex;
    int reti;
    size_t msgbuf_size = regerror(0, &regex, NULL, 0);
    char *msgbuf = malloc(msgbuf_size);

    if (!msgbuf) {
        perror("malloc failed");
        return 1;
    }

    reti = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (reti) {
        regerror(reti, &regex, msgbuf, msgbuf_size);
        fprintf(stderr, "Could not compile regex: %s\n", msgbuf);
        free(msgbuf);
        return 1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        free(msgbuf);
        return 1;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        free(msgbuf);
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, msgbuf_size);
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        free(msgbuf);
        return 1;
    }
}

int main() {
    const char *test_strings[] = {"ab", "aab", "acb", "acbb", "abcd", "a_b", "axb"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        if (match_pattern(test_strings[i])) {
            printf("Matched: %s\n", test_strings[i]);
        } else {
            printf("Not matched: %s\n", test_strings[i]);
        }
    }
    return 0;
}