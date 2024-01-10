#include <stdio.h>
#include <regex.h>

int validateUrl(char* url) {
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, "^(http[s]?|ftp):\\/\\/(([a-zA-Z0-9_-])+\\.)*[a-zA-Z]{2,}(\\/([a-zA-Z0-9._/?#%$-&=]+))*$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'url[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    ret = regexec(&regex, url, 0, NULL, 0);
    if (!ret) {
        regfree(&regex);
        return 1;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char error_message[100];
        /* Possible weaknesses found:
         *  Cannot determine that 'error_message[0]' is initialized [premium-bughuntingUninit]
         */
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
    char url[100];
    printf("Enter a URL: ");
    /* Possible weaknesses found:
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     *  Cannot determine that 'url[0]' is initialized [premium-bughuntingUninit]
     */
    scanf("%s", url);
    
    if (validateUrl(url)) {
        printf("Valid URL\n");
    } else {
        printf("Invalid URL\n");
    }
    
    return 0;
}