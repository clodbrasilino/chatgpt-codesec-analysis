#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void removeNonAlphanumeric(char *str);
char *regreplace(char *str, regex_t regex);

int main() {
    char string[] = "Hello, World! 123 #^&%$*";
    removeNonAlphanumeric(string);
    printf("%s", string);
    return 0;
}

void removeNonAlphanumeric(char *str) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED);

    if (reti == 0) {
        reti = regexec(&regex, str, 0, NULL, 0);

        if (reti == 0) {
            char *result = regreplace(str, regex);
            if(result == NULL) {
                regfree(&regex);
                return;
            }

            size_t length = strlen(result);
            memmove(str, result, length);
            str[length] = '\0';
        }

        regfree(&regex);
    }
} 

char *regreplace(char *str, regex_t regex) {
    if (str == NULL) return NULL;
    return str;
}