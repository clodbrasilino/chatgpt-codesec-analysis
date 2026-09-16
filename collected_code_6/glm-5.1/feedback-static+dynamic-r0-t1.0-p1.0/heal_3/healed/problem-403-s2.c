#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_url(const char *url) {
    if (!url) {
        printf("False\n");
        return 0;
    }

    regex_t regex;
    int ret;

    const char *pattern = "^https?://([[:alnum:].-]+\\.[[:alpha:]]{2,})(:[0-9]+)?(/[[:alnum:]_.~!*'();:@&=+$,/?#%\\[\\]-]*)?$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        printf("False\n");
        return 0;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        printf("True\n");
        return 1;
    } else {
        printf("False\n");
        return 0;
    }
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return is_valid_url(argv[1]) ? EXIT_SUCCESS : EXIT_FAILURE;
}