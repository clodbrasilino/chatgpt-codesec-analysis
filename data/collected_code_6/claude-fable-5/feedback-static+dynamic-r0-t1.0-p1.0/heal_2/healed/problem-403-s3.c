#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define URL_PATTERN "^(https?|ftp)://[A-Za-z0-9.-]+(\\.[A-Za-z]{2,})(:[0-9]{1,5})?(/[A-Za-z0-9._~:/?#@!$&'()*+,;=%-]*)?$"
#define MAX_URL_LEN 2048
#define ERRBUF_LEN 256

static int compile_url_regex(regex_t *regex)
{
    int ret;

    ret = regcomp(regex, URL_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        char errbuf[ERRBUF_LEN];
        size_t needed;

        memset(errbuf, 0, sizeof(errbuf));
        needed = regerror(ret, regex, errbuf, sizeof(errbuf) - 1);
        if (needed >= sizeof(errbuf)) {
            errbuf[sizeof(errbuf) - 1] = '\0';
        }
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }
    return 0;
}

static int is_valid_url(const regex_t *regex, const char *url)
{
    int ret;
    size_t len;

    if (regex == NULL || url == NULL) {
        return 0;
    }

    len = strnlen(url, MAX_URL_LEN + 1);
    if (len == 0 || len > MAX_URL_LEN) {
        return 0;
    }

    ret = regexec(regex, url, 0, NULL, 0);
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
    regex_t regex;
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

    if (compile_url_regex(&regex) != 0) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        int result = is_valid_url(&regex, test_urls[i]);
        if (result < 0) {
            fprintf(stderr, "Error while validating URL: %s\n", test_urls[i]);
            regfree(&regex);
            return EXIT_FAILURE;
        }
        printf("%-60s : %s\n", test_urls[i], result == 1 ? "VALID" : "INVALID");
        fflush(stdout);
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}