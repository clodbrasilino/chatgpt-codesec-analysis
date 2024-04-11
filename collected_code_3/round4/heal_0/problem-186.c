#include <stdio.h>
#include <string.h>
#include <regex.h>

int search_regex(char *base, char *search) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, search, 0);
    if (ret) {
        printf("Could not compile regex\n");
        return -1;
    }

    ret = regexec(&regex, base, 0, NULL, 0);
    if (!ret) {
        return 0;
    } else if (ret == REG_NOMATCH) {
        return -1;
    } else {
        printf("Regex match failed\n");
        return -1;
    }

    regfree(&regex);
    return -1;
}

int main() {
    char base[100];
    char search[100];

    printf("Enter the base string: ");
    fgets(base, 100, stdin);
    base[strlen(base) - 1] = '\0';

    printf("Enter the search string: ");
    fgets(search, 100, stdin);
    search[strlen(search) - 1] = '\0';

    int result = search_regex(base, search);

    if (result == 0) {
        printf("Match found\n");
    } else {
        printf("Match not found\n");
    }

    return 0;
}