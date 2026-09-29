#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define URL_PATTERN "^(https?|ftp)://[A-Za-z0-9]([A-Za-z0-9.-]*[A-Za-z0-9])?(:[0-9]{1,5})?(/[A-Za-z0-9._~%/?#=&+-]*)?$"

int is_valid_url(const char *url)
{
    regex_t regex;
    int ret;

    if (url == NULL) {
        return 0;
    }

    ret = regcomp(&regex, URL_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        size_t errlen = regerror(ret, &regex, NULL, 0);
        char *errbuf = malloc(errlen);
        if (errbuf != NULL) {
            regerror(ret, &regex, errbuf, errlen);
            fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
            free(errbuf);
        } else {
            fprintf(stderr, "Regex compilation failed\n");
        }
        return -1;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regex execution failed\n");
        return -1;
    }
}

int main(void)
{
    const char *test_urls[] = {
        "https://www.example.com",
        "http://example.com/path/to/page?name=value",
        "ftp://files.example.org",
        "https://example.com:8080/index.html",
        "not_a_url",
        "http://",
        "https://sub.domain.example.com/page#section"
    };
    size_t count = sizeof(test_urls) / sizeof(test_urls[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = is_valid_url(test_urls[i]);
        if (result == 1) {
            printf("VALID:   %s\n", test_urls[i]);
        } else if (result == 0) {
            printf("INVALID: %s\n", test_urls[i]);
        } else {
            fprintf(stderr, "Error validating: %s\n", test_urls[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}