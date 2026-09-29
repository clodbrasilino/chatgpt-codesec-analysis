#include <stdio.h>
#include <regex.h>
#include <string.h>

int validateUrl(const char* url) {
    regex_t regex;
    int ret;
    char error_message[1024];

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
        regerror(ret, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex match failed: %s\n", error_message);
        regfree(&regex);
        return 0;
    }
}

int main() {
    char url[1024];

    printf("Enter a URL: ");
    fgets(url, sizeof(url), stdin);

    size_t url_length = strlen(url);
    if (url_length > 0 && url[url_length - 1] == '\n')
        url[url_length - 1] = '\0';

    if (validateUrl(url)) {
        printf("Valid URL\n");
    } else {
        printf("Invalid URL\n");
    }

    return 0;
}