#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void search_literals(const char *text, const char *pattern) {
    if (text == NULL || pattern == NULL) {
        return;
    }

    regex_t regex;
    int reti;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti != 0) {
        return;
    }

    reti = regexec(&regex, text, 0, NULL, 0);
    if (!reti) {
        printf("Match found.\n");
    } else if (reti == REG_NOMATCH) {
        printf("No match.\n");
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

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog.";
    const char *pattern = "(fox|dog)";

    search_literals(text, pattern);

    return EXIT_SUCCESS;
}