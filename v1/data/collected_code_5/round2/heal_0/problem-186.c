#include <regex.h>
#include <stdio.h>
#include <string.h>

int search_regex(char *pattern, char *str) {
    regex_t regex;
    int ret;

    if(regcomp(&regex, pattern, REG_EXTENDED|REG_ICASE) != 0) {
        printf("Error creating regex\n");
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if(!ret) {
        return 1;
    }
    else if(ret == REG_NOMATCH) {
        return 0;
    }
    else {
        printf("Regex match failed\n");
        return -1;
    }

    regfree(&regex);
    return ret;
}

int main(void) {
    char str[] = "Hello, World!";
    char pattern[] = "World";

    int found = search_regex(pattern, str);

    if(found < 0) {
        printf("An error occurred\n");
        return 1;
    }
    else if(found) {
        printf("Match found\n");
        return 0;
    }
    else {
        printf("Match not found\n");
        return 0;
    }
}