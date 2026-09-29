#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define NUM_CATEGORIES 4
#define MAX_CATEGORY_LEN 16
#define MAX_PATTERN_LEN 16

typedef struct {
    char pattern[MAX_PATTERN_LEN];
    char category[MAX_CATEGORY_LEN];
} CharCategory;

void find_characters(const char *str) {
    regex_t regex;
    regmatch_t match;
    CharCategory categories[NUM_CATEGORIES] = {
        {"[A-Z]", "Uppercase"},
        {"[a-z]", "Lowercase"},
        {"[0-9]", "Numeric"},
        {"[^A-Za-z0-9]", "Special"}
    };

    for (size_t i = 0; i < NUM_CATEGORIES; i++) {
        int ret = regcomp(&regex, categories[i].pattern, REG_EXTENDED);
        if (ret != 0) {
            continue;
        }

        printf("%s: ", categories[i].category);

        const char *cursor = str;
        int first = 1;

        while (cursor != NULL && *cursor != '\0') {
            ret = regexec(&regex, cursor, 1, &match, 0);
            if (ret == REG_NOMATCH) {
                break;
            }

            if (match.rm_so == -1) {
                break;
            }

            if (match.rm_eo <= match.rm_so) {
                cursor++;
                continue;
            }

            if (!first) {
                printf(", ");
            }
            first = 0;

            size_t start = (size_t)match.rm_so;
            size_t end = (size_t)match.rm_eo;
            size_t len = end - start;

            printf("%.*s", (int)len, cursor + start);

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