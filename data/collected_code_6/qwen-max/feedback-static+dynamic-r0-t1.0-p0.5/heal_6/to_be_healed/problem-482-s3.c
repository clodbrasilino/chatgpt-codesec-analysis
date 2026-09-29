#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *input) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    reti = regexec(&regex, input, 0, NULL, 0);
    if (!reti) {
        printf("Match found\n");
    } else if (reti == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    regfree(&regex);
}

int main() {
    const char *test_string = "This is a TestString with SomeSequences and some without";
    find_sequences(test_string);
    return 0;
}