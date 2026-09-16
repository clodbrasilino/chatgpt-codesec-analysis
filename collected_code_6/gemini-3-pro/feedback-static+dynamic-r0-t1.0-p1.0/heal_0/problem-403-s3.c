#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    const char *pattern = "^(https?|ftp)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main(void) {
    const char *test_urls[] = {
        "http://www.google.com",
        "https://example.com/path?query=1",
        "ftp://ftp.is.co.za/rfc/rfc1808.txt",
        "invalid_url",
        "http://",
        NULL
    };

    for (size_t i = 0; test_urls[i] != NULL; ++i) {
        if (is_valid_url(test_urls[i])) {
            printf("Valid: %s\n", test_urls[i]);
        } else {
            printf("Invalid: %s\n", test_urls[i]);
        }
    }

    return 0;
}