#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    const char *pattern = "^https?://(www\\.)?[a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)+([/?#][a-zA-Z0-9-._~:/?#@!$&'()*+,;=]*)?$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_valid_url(argv[1])) {
        printf("Valid URL\n");
    } else {
        printf("Invalid URL\n");
    }

    return EXIT_SUCCESS;
}