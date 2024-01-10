#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_MSG_BUF_LEN 100
#define MAX_STR_LEN 100

int match_regex(const char *string) {
    if(strlen(string) > MAX_STR_LEN) {
        fprintf(stderr, "Input size greater than buffer size\n");
        return -1;
    }

    regex_t regex;
    int reti;
    char msgbuf[MAX_MSG_BUF_LEN];

    reti = regcomp(&regex, "a.*b$", 0);
    if(reti) {
        fprintf(stderr, "Could not compile regex\n");
        regfree(&regex);
        return 0;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    if(!reti) {
        regfree(&regex);
        return 1;
    } else if(reti == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        return 0;
    }
}

int main() {
    char string1[MAX_STR_LEN + 1] = "abc";
    char string2[MAX_STR_LEN + 1] = "axyzb";
    char string3[MAX_STR_LEN + 1] = "ab";
    
    if(match_regex(string1) == -1 || match_regex(string2) == -1 || match_regex(string3) == -1){
        fprintf(stderr, "An error occurred\n");
        return -1;
    }

    printf("String 1: %d\n", match_regex(string1));
    printf("String 2: %d\n", match_regex(string2));
    printf("String 3: %d\n", match_regex(string3));

    return 0;
}