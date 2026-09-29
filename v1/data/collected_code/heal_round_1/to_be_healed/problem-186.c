#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void searchStrings(char *string, char *pattern) {
    regex_t regex;
    int ret;

    /* Possible weaknesses found:
     *  Cannot determine that 'pattern[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Possible weaknesses found:
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    ret = regexec(&regex, string, 0, NULL, 0);
    if (!ret) {
        printf("Match found\n");
    } else if (ret == REG_NOMATCH) {
        printf("No match found\n");
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
        exit(1);
    }

    regfree(&regex);
}

int main() {
    char *string = "This is a test string.";
    char *pattern = "test";

    searchStrings(string, pattern);

    return 0;
}