#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>
#include <errno.h>

int extract_max_value(const char *str, long *max_val) {
    regex_t regex;
    int ret;
    ret = regcomp(&regex, "[0-9]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    regmatch_t match;
    long current_max = -1;
    const char *p = str;

    while (1) {
        ret = regexec(&regex, p, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so == -1) {
            break;
        }

        long len = match.rm_eo - match.rm_so;
        char *endptr;
        errno = 0;
        long val = strtol(p + match.rm_so, &endptr, 10);

        if (errno == ERANGE) {
            regfree(&regex);
            return -1;
        }
        if (endptr != p + match.rm_so + len) {
            regfree(&regex);
            return -1;
        }

        if (val > current_max) {
            current_max = val;
        }

        p += match.rm_eo;
        if (*p == '\0') {
            break;
        }
    }

    regfree(&regex);

    if (current_max == -1) {
        return -1;
    }

    *max_val = current_max;
    return 0;
}

int main(void) {
    const char *text = "abc 42 def 105 ghi 7 jkl";
    long max_val;

    if (extract_max_value(text, &max_val) == 0) {
        printf("%ld\n", max_val);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}