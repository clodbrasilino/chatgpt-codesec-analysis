#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define NUM_CATEGORIES 4
#define MAX_STR_LEN 1024

void find_characters(const char *str, size_t str_len) {
    regex_t regex;
    regmatch_t match[1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char * const patterns[NUM_CATEGORIES] = {
        "[A-Z]", "[a-z]", "[0-9]", "[^A-Za-z0-9]"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char * const categories[NUM_CATEGORIES] = {
        "Uppercase", "Lowercase", "Numeric", "Special"
    };

    if (str == NULL || str_len == 0) {
        return;
    }

    for (size_t i = 0; i < NUM_CATEGORIES; i++) {
        int ret = regcomp(&regex, patterns[i], REG_EXTENDED);
        if (ret != 0) {
            continue;
        }

        printf("%s: ", categories[i]);

        const char *cursor = str;
        size_t remaining_len = str_len;
        int first = 1;

        while (cursor != NULL && remaining_len > 0 && *cursor != '\0') {
            ret = regexec(&regex, cursor, 1, match, 0);
            if (ret == REG_NOMATCH) {
                break;
            }

            if (match[0].rm_so == -1) {
                break;
            }

            size_t start = (size_t)match[0].rm_so;
            size_t end = (size_t)match[0].rm_eo;

            if (start >= remaining_len || end > remaining_len || end <= start) {
                break;
            }

            if (!first) {
                printf(", ");
            }
            first = 0;

            printf("%.*s", (int)(end - start), cursor + start);

            cursor += end;
            remaining_len -= end;
        }

        printf("\n");
        regfree(&regex);
    }
}

int main(int argc, char * const * const argv) {
    char *test_str = malloc(MAX_STR_LEN + 1);
    if (test_str == NULL) {
        return 1;
    }

    size_t test_str_len;

    if (argc > 1) {
        snprintf(test_str, MAX_STR_LEN + 1, "%s", argv[1]);
        test_str_len = strnlen(test_str, MAX_STR_LEN);
    } else {
        snprintf(test_str, MAX_STR_LEN + 1, "%s", "HelloWorld123!");
        test_str_len = strnlen(test_str, MAX_STR_LEN);
    }

    find_characters(test_str, test_str_len);

    free(test_str);

    return 0;
}