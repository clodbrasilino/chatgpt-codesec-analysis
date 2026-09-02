#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void find_adverbs(const char *sentence) {
    regex_t regex;
    regmatch_t match[1];
    int reti;

    if (regcomp(&regex, "\\b\\w+ly\\b", REG_EXTENDED|REG_NOSUB) != 0) {
        return;
    }

    const size_t len = strlen(sentence);
    for (size_t i = 0; i <= len; i++) {
        reti = regexec(&regex, sentence + i, 1, match, 0);
        if (!reti) {
            match[0].rm_so += i;
            match[0].rm_eo += i;
            printf("Adverb: %.*s at position %ld to %ld\n", match[0].rm_eo - match[0].rm_so, sentence + match[0].rm_so, match[0].rm_so, match[0].rm_eo - 1);
            i += match[0].rm_eo - match[0].rm_so - 1;
        } else if (reti == REG_NOMATCH) {
            continue;
        } else {
            regfree(&regex);
            return;
        }
    }

    regfree(&regex);
}

int main() {
    const char *sentence = "He quickly and quietly walked away.";
    find_adverbs(sentence);
    return 0;
}