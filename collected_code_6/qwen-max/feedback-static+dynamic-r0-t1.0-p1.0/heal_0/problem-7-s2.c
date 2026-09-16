#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_long_words(const char *input) {
    int ret;
    int nmatch = 1;
    regex_t reg;
    regmatch_t pmatch[1];

    const char *pattern = "\\b\\w{4,}\\b";

    if (regcomp(&reg, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while ((ret = regexec(&reg, input, nmatch, pmatch, 0)) == 0) {
        for (int i = 0; i < nmatch; i++) {
            if (pmatch[i].rm_so == pmatch[i].rm_eo) continue;
            printf("%.*s\n", pmatch[i].rm_eo - pmatch[i].rm_so, &input[pmatch[i].rm_so]);
        }
        input += pmatch[0].rm_eo;
    }

    if (ret != REG_NOMATCH) {
        fprintf(stderr, "Regex match failed\n");
    }

    regfree(&reg);
}

int main() {
    const char *test_string = "Hello world this is a test string with SomeLongWords and short ones";
    find_long_words(test_string);
    return 0;
}