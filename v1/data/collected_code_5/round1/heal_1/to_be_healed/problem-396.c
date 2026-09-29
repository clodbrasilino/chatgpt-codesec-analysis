#include <stdio.h>
#include <string.h>
#include <regex.h>


int check_string(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    regex_t regex;
    int reti;
    char pattern[8] = "^.";
    /* Possible weaknesses found:
     *  Value stored to 'len' during its initialization is never read [deadcode.DeadStores]
     */
    size_t len = strlen(str);

    pattern[2] = str[0];
    pattern[3] = '*';
    pattern[4] = str[0];
    pattern[5] = '$';
    pattern[6] = '\0';

    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        printf("Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    if (!reti) {
        return 1;
    } 
    return 0;
}

int main() {
    char stringToCheck[] = "hannah";
    int result = check_string(stringToCheck);

    if (result == 1) {
        printf("String starts and ends with the same character\n");
    } else {
        printf("String does not start and end with the same character\n");
    }

    return 0;
}