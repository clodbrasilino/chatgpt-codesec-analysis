#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define URL_PATTERN "^(https?|ftp)://[A-Za-z0-9.-]+(\\.[A-Za-z]{2,})(:[0-9]{1,5})?(/[A-Za-z0-9._~:/?#@!$&'()*+,;=%-]*)?$"
#define MAX_URL_LEN 2048
#define ERRBUF_LEN 256

int is_valid_url(const char *url)
{
    regex_t regex;
    int ret;
    size_t len;

    if (url == NULL) {
        return 0;
    }

    len = strnlen(url, MAX_URL_LEN + 1);
    if (len == 0 || len > MAX_URL_LEN) {
        return 0;
    }

    ret = regcomp(&regex, URL_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[ERRBUF_LEN];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    }

    if (ret == REG_NOMATCH) {
        return 0;
    }

    fprintf(stderr, "Regex execution failed\n");
    return -1;
}

int main(void)
{
    const char *test_urls[] = {
        "https://www.example.com",
        "http://example.com/path/to/page?query=value",
        "ftp://files.example.org:2121/downloads",
        "https://sub.domain.co.uk/index.html",
        "not_a_url",
        "http://",
        "www.example.com",
        "https://example",
        ""
    };
    size_t count = sizeof(test_urls) / sizeof(test_urls[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = is_valid_url(test_urls[i]);
        if (result < 0) {
            fprintf(stderr, "Error while validating URL: %s\n", test_urls[i]);
            return EXIT_FAILURE;
        }
        printf("%-60s : %s\n", test_urls[i], result == 1 ? "VALID" : "INVALID");
    }

    return EXIT_SUCCESS;
}