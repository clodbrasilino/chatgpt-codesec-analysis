#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got 1
  */

int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    const char *pattern = "^(https?|ftp)://[^\s/$.?#].[^\s]*$";
    
    reti = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    const char *url1 = "https://www.example.com";
    const char *url2 = "invalid_url";

    if (is_valid_url(url1)) {
        printf("URL is valid\n");
    } else {
        printf("URL is invalid\n");
    }

    if (is_valid_url(url2)) {
        printf("URL is valid\n");
    } else {
        printf("URL is invalid\n");
    }

    return 0;
}