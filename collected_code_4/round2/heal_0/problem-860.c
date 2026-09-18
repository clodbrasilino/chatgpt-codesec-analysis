#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

#define MATCHES_SIZE 10

int is_ending_alphanumeric(const char *str) {
    regex_t regex;
    regmatch_t matches[MATCHES_SIZE];
    const char *pattern = "[a-zA-Z0-9]+$";
    int res;

    res = regcomp(&regex, pattern, REG_EXTENDED);
    if (res) {
        printf("Could not compile regex\n");
        return 0;
    }

    res = regexec(&regex, str, MATCHES_SIZE, matches, 0);
    regfree(&regex);
    if (res) return 0;
    
    return 1;
}

int main() {
    char *str1 = "Hello, World!";
    char *str2 = "Hello, World3";

    if (is_ending_alphanumeric(str1))
        printf("\"%s\" ends with alphanumeric characters\n", str1);
    else
        printf("\"%s\" doesn't end with alphanumeric characters\n", str1);

    if (is_ending_alphanumeric(str2))
        printf("\"%s\" ends with alphanumeric characters\n", str2);
    else
        printf("\"%s\" doesn't end with alphanumeric characters\n", str2);

    return 0;
}