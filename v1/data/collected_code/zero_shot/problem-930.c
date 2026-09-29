#include <stdio.h>
#include <regex.h>

int match_a_followed_by_bs(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "a[b]*", REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        printf("String matches pattern\n");
        return 1;
    } else {
        printf("String does not match pattern\n");
        return 0;
    }
}

int main() {
    const char *str = "abb";
    match_a_followed_by_bs(str);

    return 0;
}
