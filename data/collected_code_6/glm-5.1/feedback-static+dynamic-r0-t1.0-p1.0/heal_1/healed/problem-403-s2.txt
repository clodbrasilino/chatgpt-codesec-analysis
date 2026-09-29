#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_url(const char *url) {
    if (!url) {
        return 0;
    }

    regex_t regex;
    int ret;

    const char *pattern = "^https?://([[:alnum:].-]+\\.[[:alpha:]]{2,})(:[0-9]+)?(/[[:alnum:]_.~!*'();:@&=+$,/?#%\\[\\]-]*)?$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        printf("True");
        return 1;
    } else if (ret == REG_NOMATCH) {
        printf("False");
        return 0;
    } else {
        printf("False");
        return 0;
    }
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    is_valid_url(argv[1]);

    return EXIT_SUCCESS;
}