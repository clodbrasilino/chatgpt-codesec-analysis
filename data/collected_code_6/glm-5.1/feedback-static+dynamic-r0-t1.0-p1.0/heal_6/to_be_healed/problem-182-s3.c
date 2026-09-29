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
        int first = 1;

        while (cursor != NULL && *cursor != '\0' && (size_t)(cursor - str) < str_len) {
            ret = regexec(&regex, cursor, 1, match, 0);
            if (ret == REG_NOMATCH) {
                break;
            }

            if (match[0].rm_so == -1) {
                break;
            }

            size_t start = (size_t)match[0].rm_so;
            size_t end = (size_t)match[0].rm_eo;

            if (start >= str_len || end > str_len || end <= start) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test_str[MAX_STR_LEN + 1];
    size_t test_str_len;

    if (argc > 1) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(test_str, argv[1], MAX_STR_LEN);
        test_str[MAX_STR_LEN] = '\0';
        test_str_len = strnlen(test_str, MAX_STR_LEN);
    } else {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
         */
        strncpy(test_str, "HelloWorld123!", MAX_STR_LEN);
        test_str[MAX_STR_LEN] = '\0';
        test_str_len = strnlen(test_str, MAX_STR_LEN);
    }

    find_characters(test_str, test_str_len);

    return 0;
}