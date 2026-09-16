#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void find_words(const char *str, const char *pattern) {
    regex_t re;
    regmatch_t matches[1];

    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    for (const char *p = str; *p; p++) {
        if (regexec(&re, p, 1, matches, 0) == 0) {
            for (int j = matches[0].rm_so; j < matches[0].rm_eo; j++) {
                putchar(p[j]);
            }
            putchar('\n');
            p += matches[0].rm_eo - 1;
        }
    }

    regfree(&re);
}

int main() {
    const char *input = "This is a test string with three, four, and five characters long words.";
    const char *pattern = "\\b\\w{3,5}\\b";

    find_words(input, pattern);

    return 0;
}