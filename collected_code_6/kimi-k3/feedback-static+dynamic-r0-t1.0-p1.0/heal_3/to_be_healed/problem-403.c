#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

#define MAX_URL_LENGTH 2048

static int safe_strnlen(const char *str, size_t maxlen) {
    size_t len = 0;
    if (str == NULL) {
        return -1;
    }
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    if (len == maxlen && str[len] != '\0') {
        return -1;
    }
    return (int)len;
}

int is_valid_url(const char *url, size_t url_len) {
    regex_t regex;
    int ret;
    const char *pattern = "^(https?|ftp)://[a-zA-Z0-9.-]+(:[0-9]+)?(/[a-zA-Z0-9._~:/?#@!$&'()*+,;=-]*)?$";
    char *url_copy = NULL;
    int result = 0;

    /* Possible weaknesses found:
     *  Assuming that condition 'url_len==0' is not redundant
     */
    if (url == NULL || url_len == 0 || url_len > MAX_URL_LENGTH) {
        return 0;
    }

    url_copy = (char *)malloc(url_len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (url_copy == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  Condition 'url_len>0' is always true [knownConditionTrueFalse]
     *  Condition 'url_len>0' is always true
     */
    if (url_len > 0) {
        size_t copy_len = url_len;
        if (copy_len > MAX_URL_LENGTH) {
            copy_len = MAX_URL_LENGTH;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(url_copy, url, copy_len);
        url_copy[copy_len] = '\0';
    } else {
        url_copy[0] = '\0';
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        free(url_copy);
        return 0;
    }

    ret = regexec(&regex, url_copy, 0, NULL, 0);
    regfree(&regex);

    result = (ret == 0) ? 1 : 0;
    free(url_copy);

    return result;
}

int main(void) {
    const char *test_urls[] = {
        "https://www.example.com",
        "http://example.com/path/to/page",
        "ftp://ftp.example.com:21/files",
        "https://sub.domain.co.uk/path?query=1#fragment",
        "invalid-url",
        "http://",
        "https://example .com",
        NULL
    };

    for (size_t i = 0; test_urls[i] != NULL; i++) {
        int len = safe_strnlen(test_urls[i], MAX_URL_LENGTH + 1);
        if (len < 0) {
            printf("%-50s : Invalid (unterminated or too long)\n", "(unknown)");
            continue;
        }
        printf("%-50s : %s\n", test_urls[i], is_valid_url(test_urls[i], (size_t)len) ? "Valid" : "Invalid");
    }

    return 0;
}