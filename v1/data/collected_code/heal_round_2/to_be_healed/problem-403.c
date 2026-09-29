#include <stdio.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

int validateUrl(const char* url) {
    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char error_message[256];

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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char url[256];

    printf("Enter a URL: ");
    fgets(url, sizeof(url), stdin);

    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if (url[strlen(url) - 1] == '\n')
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        url[strlen(url) - 1] = '\0';

    if (validateUrl(url)) {
        printf("Valid URL\n");
    } else {
        printf("Invalid URL\n");
    }

    return 0;
}