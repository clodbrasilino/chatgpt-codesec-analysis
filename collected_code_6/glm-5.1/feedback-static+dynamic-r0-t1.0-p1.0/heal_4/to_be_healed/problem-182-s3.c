#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define NUM_CATEGORIES 4

void find_characters(const char *str) {
    regex_t regex;
    regmatch_t match[1];

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *patterns[NUM_CATEGORIES];
    patterns[0] = "[A-Z]";
    patterns[1] = "[a-z]";
    patterns[2] = "[0-9]";
    patterns[3] = "[^A-Za-z0-9]";

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *categories[NUM_CATEGORIES];
    categories[0] = "Uppercase";
    categories[1] = "Lowercase";
    categories[2] = "Numeric";
    categories[3] = "Special";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t max_len = strlen(str);
    if (max_len == 0) {
        return;
    }

    for (size_t i = 0; i < NUM_CATEGORIES; i++) {
        int ret = regcomp(&regex, patterns[i], REG_EXTENDED);
        if (ret != 0) {
            continue;
        }

        printf("%s: ", categories[i]);

        const char *cursor = str;
        int first = 1;

        while (cursor != NULL && *cursor != '\0' && (size_t)(cursor - str) < max_len) {
            ret = regexec(&regex, cursor, 1, match, 0);
            if (ret == REG_NOMATCH) {
                break;
            }

            if (match[0].rm_so == -1) {
                break;
            }

            size_t start = (size_t)match[0].rm_so;
            size_t end = (size_t)match[0].rm_eo;

            if (start >= max_len || end > max_len || end <= start) {
                break;
            }

            if (!first) {
                printf(", ");
            }
            first = 0;

            printf("%.*s", (int)(end - start), cursor + start);

            cursor += end;
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