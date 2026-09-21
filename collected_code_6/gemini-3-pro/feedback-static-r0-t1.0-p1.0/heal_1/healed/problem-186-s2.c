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
            size_t errbuf_size = regerror(reti, &regex, NULL, 0);
            char *msgbuf = malloc(errbuf_size);
            if (msgbuf != NULL) {
                regerror(reti, &regex, msgbuf, errbuf_size);
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
                free(msgbuf);
            }
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