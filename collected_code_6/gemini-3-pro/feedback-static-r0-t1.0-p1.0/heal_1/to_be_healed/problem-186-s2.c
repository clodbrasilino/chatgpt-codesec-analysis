#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void search_patterns(const char *target, const char **patterns, size_t num_patterns) {
    if (target == NULL || patterns == NULL || num_patterns == 0) {
        return;
    }

    regex_t regex;
    int reti;

    for (size_t i = 0; i < num_patterns; ++i) {
        if (patterns[i] == NULL) {
            continue;
        }

        reti = regcomp(&regex, patterns[i], REG_EXTENDED);
        if (reti != 0) {
            fprintf(stderr, "Could not compile regex: %s\n", patterns[i]);
            continue;
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        if (reti == 0) {
            printf("Pattern '%s' found in string.\n", patterns[i]);
        } else if (reti == REG_NOMATCH) {
            printf("Pattern '%s' not found in string.\n", patterns[i]);
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
}

int main(void) {
    const char *target = "The quick brown fox jumps over the lazy dog.";
    const char *patterns[] = {
        "fox",
        "cat",
        "lazy dog",
        "^[A-Z]",
        "invalid[regex("
    };
    size_t num_patterns = sizeof(patterns) / sizeof(patterns[0]);

    search_patterns(target, patterns, num_patterns);

    return 0;
}