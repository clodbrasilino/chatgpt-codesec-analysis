#include <stdio.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *str) {
    regex_t regex;
    int reti;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char msgbuf[100];

    reti = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        return 1;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
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