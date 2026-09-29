#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int regex_search(char * base, char * search) {
  
    regex_t regex;
    int reti;
    char msgbuf[100];
    /* Compile regular expression */
    reti = regcomp(&regex, search, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Execute a regular expression */
    reti = regexec(&regex, base, 0, NULL, 0);
    if (!reti) {
        return 1;
    }
    else if (reti == REG_NOMATCH) {
        return 0;
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    /* Free compiled regular expression */
    regfree(&regex);
    return 0;
}

int main() {
  
    char base[100] = "hello world!";
    char search[50] = "world";
    int found = regex_search(base, search);
    if(found) {
        printf("Found\n");
    }
    else {
        printf("Not Found\n");
    }
    return 0;
}