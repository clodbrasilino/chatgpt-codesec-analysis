#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_characters(const char *str) {
    regex_t regex;
    /* Possible weaknesses found:
     *  The scope of the variable 'ret' can be reduced. [variableScope]
     */
    int ret;
    regmatch_t match[1];

    const char *patterns[4] = {
        "[A-Z]",
        "[a-z]",
        "[0-9]",
        "[^A-Za-z0-9]"
    };

    const char *categories[4] = {
        "Uppercase",
        "Lowercase",
        "Numeric",
        "Special"
    };

    for (size_t i = 0; i < 4; i++) {
        ret = regcomp(&regex, patterns[i], REG_EXTENDED);
        if (ret != 0) {
            continue;
        }

        printf("%s: ", categories[i]);

        const char *cursor = str;
        int first = 1;

        while (cursor != NULL && *cursor != '\0') {
            ret = regexec(&regex, cursor, 1, match, 0);
            if (ret == REG_NOMATCH) {
                break;
            }

            if (match[0].rm_so == -1) {
                break;
            }

            if (!first) {
                printf(", ");
            }
            first = 0;

            size_t start = match[0].rm_so;
            size_t end = match[0].rm_eo;

            printf("%.*s", (int)(end - start), cursor + start);

            if (end > 0) {
                cursor += end;
            } else {
                cursor += 1;
            }
        }

        printf("\n");
        regfree(&regex);
    }
}

int main(int argc, char *argv[]) {
    const char *test_str;

    if (argc > 1) {
        test_str = argv[1];
    } else {
        test_str = "HelloWorld123!";
    }

    find_characters(test_str);

    return 0;
}