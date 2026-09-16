#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void find_words(const char *str, const char *pattern) {
    int status;
    regex_t re;
    regmatch_t matches[1];

    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    for (const char *p = str; *p; p++) {
        if (regexec(&re, p, 1, matches, 0) == 0) {
            for (int i = 0; matches[i].rm_so != -1; i++) {
                for (int j = 0; j < matches[i].rm_eo - matches[i].rm_so; j++) {
                    putchar(p[j + matches[i].rm_so]);
                }
                putchar('\n');
            }
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