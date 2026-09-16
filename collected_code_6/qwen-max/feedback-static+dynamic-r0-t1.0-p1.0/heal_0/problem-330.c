#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void find_words(const char *input) {
    regex_t regex;
    int reti;
    regmatch_t match[1];

    const char *patterns[] = { "\\b\\w{3}\\b", "\\b\\w{4}\\b", "\\b\\w{5}\\b" };

    for (int i = 0; i < 3; i++) {
        reti = regcomp(&regex, patterns[i], REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return;
        }

        while ((reti = regexec(&regex, input, 1, match, 0)) == 0) {
            for (int j = 0; j < 1; j++) {
                if (match[j].rm_so == -1 || match[j].rm_eo == -1)
                    continue;
                printf("%.*s\n", match[j].rm_eo - match[j].rm_so, input + match[j].rm_so);
            }
        }

        regfree(&regex);
    }
}

int main() {
    const char *input = "This is a test string with words of different lengths";
    find_words(input);
    return 0;
}