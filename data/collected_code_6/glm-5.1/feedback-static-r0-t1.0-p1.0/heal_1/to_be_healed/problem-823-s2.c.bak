#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with_substring(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return 0;
    }

    size_t sub_len = strlen(sub);
    if (sub_len == 0) {
        return 1;
    }

    char *pattern = malloc(sub_len + 3);
    if (pattern == NULL) {
        return 0;
    }

    pattern[0] = '^';
    memcpy(pattern + 1, sub, sub_len);
    pattern[sub_len + 1] = '$';
    pattern[sub_len + 2] = '\0';

    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    free(pattern);

    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <substring>\n", argv[0]);
        return 1;
    }

    if (starts_with_substring(argv[1], argv[2])) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }

    return 0;
}