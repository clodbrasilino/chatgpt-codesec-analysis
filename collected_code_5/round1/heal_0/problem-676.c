#include <stdio.h>
#include <string.h>
#include <regex.h>


void keep_alphanumeric_chars(char *str) {
    regex_t regex;
    char output[100];
    int i = 0, j = 0;

    regcomp(&regex, "[a-zA-Z0-9]", 0);

    while (i < strlen(str)) {
        if (regexec(&regex, &str[i], 0, NULL, 0) == 0) {
            output[j++] = str[i];
        }
        i++;
    }

    output[j] = '\0';
    strcpy(str, output);
    regfree(&regex);
}

int main() {
    char str[] = "He11o_Wor!d@";

    printf("Before: %s\n", str);
    keep_alphanumeric_chars(str);
    printf("After: %s\n", str);

    return 0;
}