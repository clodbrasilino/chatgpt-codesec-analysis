#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_SIZE 2048
#define MAX_ERROR_SIZE 2048

int validateUrl(const char* url) {
    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char error_message[MAX_ERROR_SIZE];

    ret = regcomp(&regex, "^(http[s]?|ftp):\\/\\/(([a-zA-Z0-9_-])+\\.)*[a-zA-Z]{2,}(\\/([a-zA-Z0-9._/?#%$-&=]+))*$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    if (!ret) {
        regfree(&regex);
        return 1;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        regerror(ret, &regex, error_message, MAX_ERROR_SIZE);
        fprintf(stderr, "Regex match failed: %s\n", error_message);
        regfree(&regex);
        return 0;
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char url[MAX_URL_SIZE];

    printf("Enter a URL: ");
    fgets(url, sizeof(url), stdin);

    size_t url_length = strnlen(url, MAX_URL_SIZE);
    if (url_length > 0 && url[url_length - 1] == '\n')
        url[url_length - 1] = '\0';

    if (validateUrl(url)) {
        printf("Valid URL\n");
    } else {
        printf("Invalid URL\n");
    }

    return 0;
}