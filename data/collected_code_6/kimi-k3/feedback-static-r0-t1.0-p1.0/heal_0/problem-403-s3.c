#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int is_valid_url(const char *url) {
    regex_t regex;
    int ret;
    const char *pattern = "^(https?|ftp)://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(:[0-9]{1,5})?(/.*)?$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main() {
    const char *test_urls[] = {
        "http://www.example.com",
        "https://sub.domain.co.uk/path/to/page",
        "ftp://files.server.org:21/download",
        "invalid-url",
        "http://missingdot",
        NULL
    };

    for (int i = 0; test_urls[i] != NULL; i++) {
        printf("URL: %s is %s\n", test_urls[i], is_valid_url(test_urls[i]) ? "valid" : "invalid");
    }

    return 0;
}