#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int starts_ends_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    regex_t regex;
    int ret;
    const char *pattern = "^(.)\\1$|^(.).\\2$|^(.).{2}\\3$|^(.).{3}\\4$|^(.).{4}\\5$|^(.).{5}\\6$|^([a-zA-Z0-9_]).*\\7$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main(int argc, char const * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    if (starts_ends_same(argv[1])) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}