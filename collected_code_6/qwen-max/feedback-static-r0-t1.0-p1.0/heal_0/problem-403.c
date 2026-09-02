#include <stdio.h>
#include <regex.h>

int is_valid_url(const char *url) {
    int result;
    regex_t regex;

    if (regcomp(&regex, "^(http|https)://([A-Z0-9][A-Z0-9-]{0,61}[A-Z0-9]\\.)+([A-Z]{2,6}\\.?|[A-Z0-9-]{2,}\\.)+$", REG_EXTENDED | REG_ICASE | REG_NOSUB) != 0) {
        return 0;
    }

    result = regexec(&regex, url, 0, NULL, 0);

    regfree(&regex);
    return result == 0;
}

int main() {
    const char *test_urls[] = {
        "http://example.com",
        "https://www.example.org",
        "ftp://example.net",
        "example.com",
        "http:///example.com",
        "https://example..com"
    };

    for (int i = 0; i < 6; ++i) {
        printf("%s: %s\n", test_urls[i], is_valid_url(test_urls[i]) ? "Valid" : "Invalid");
    }

    return 0;
}