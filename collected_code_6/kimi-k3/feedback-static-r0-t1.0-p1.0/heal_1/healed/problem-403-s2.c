#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

#define URL_REGEX "^https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(/[^\\s]*)?$"
#define MAX_URL_LENGTH 2048

bool is_valid_url(const char *url, size_t url_len) {
    regex_t regex;
    int result;
    bool is_valid = false;

    if (url == NULL || url_len == 0 || url_len > MAX_URL_LENGTH) {
        return false;
    }

    result = regcomp(&regex, URL_REGEX, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, url, 0, NULL, 0);
    if (result == 0) {
        is_valid = true;
    } else if (result != REG_NOMATCH) {
        is_valid = false;
    }

    regfree(&regex);
    return is_valid;
}

int main(void) {
    const char *test_urls[] = {
        "https://www.example.com",
        "http://subdomain.example.co.uk/path/to/page",
        "https://example.org",
        "ftp://invalid.com",
        "https://",
        "not_a_url",
        "https://example.com/path with spaces",
        "https://example.com/valid-path"
    };
    
    size_t num_urls = sizeof(test_urls) / sizeof(test_urls[0]);
    
    for (size_t i = 0; i < num_urls; i++) {
        size_t url_len = strnlen(test_urls[i], MAX_URL_LENGTH + 1);
        printf("%-50s : %s\n", test_urls[i], 
               is_valid_url(test_urls[i], url_len) ? "Valid" : "Invalid");
    }

    return EXIT_SUCCESS;
}