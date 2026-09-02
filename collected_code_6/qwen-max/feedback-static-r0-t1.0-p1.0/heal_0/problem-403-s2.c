#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_url(const char *url) {
    const char *pattern = "^(http|https)://[a-zA-Z0-9\\-\\.]+\\.[a-zA-Z]{2,}(/.*)?$";
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret) {
        return false;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return !ret;
}

int main() {
    const char *test_urls[] = {
        "http://example.com",
        "https://www.example.com/path",
        "ftp://example.com",
        "http://-example-.com",
        "http://127.0.0.1",
        "https://localhost:8000"
    };

    for (size_t i = 0; i < sizeof(test_urls)/sizeof(test_urls[0]); ++i) {
        printf("%s is %s\n", test_urls[i], is_valid_url(test_urls[i]) ? "valid" : "invalid");
    }

    return 0;
}