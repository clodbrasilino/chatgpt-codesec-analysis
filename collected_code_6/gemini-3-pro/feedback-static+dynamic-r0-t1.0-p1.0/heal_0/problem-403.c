#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    const char *pattern = "^(https?|ftp)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1; 
    } else if (reti == REG_NOMATCH) {
        return 0; 
    } else {
        return 0; 
    }
}

int main(void) {
    const char *test_urls[] = {
        "http://www.google.com",
        "https://example.com/path/to/resource?query=string",
        "ftp://ftp.is.co.za/rfc/rfc1808.txt",
        "invalid_url",
        "http://",
        NULL
    };

    for (int i = 0; test_urls[i] != NULL; ++i) {
        if (is_valid_url(test_urls[i])) {
            printf("VALID: %s\n", test_urls[i]);
        } else {
            printf("INVALID: %s\n", test_urls[i]);
        }
    }

    return 0;
}