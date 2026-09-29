#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alphanumeric(char *str) {
    regex_t regex;
    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NEWLINE))
        return -1;

    if (regexec(&regex, str, 0, NULL, 0)) {
        regfree(&regex);
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (!result) {
        regfree(&regex);
        return -1;
    }

    int i = 0, j = 0;
    while (i < len) {
        if (regexec(&regex, &str[i], 0, NULL, 0)) {
            result[j++] = str[i];
            i++;
        } else {
            i += regerror(0, &regex, NULL, 0);
        }
    }
    result[j] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, result, len + 1);
    free(result);
    regfree(&regex);

    return 0;
}

int main() {
    char str[] = "Hello!@# World$%^&*()_+";
    if (remove_non_alphanumeric(str) == 0) {
        printf("%s\n", str);
    } else {
        printf("Error occurred.\n");
    }
    return 0;
}