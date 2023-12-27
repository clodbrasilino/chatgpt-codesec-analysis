#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_MSG_BUF_LEN 100
#define MAX_STR_LEN 100

int match_regex(const char *string){
    regex_t regex;
    int reti;
    char msgbuf[MAX_MSG_BUF_LEN];

    reti = regcomp(&regex, "a.*b$", 0);
    if(reti){
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    if(!reti){
        return 1;
    }
    else if(reti == REG_NOMATCH){
        return 0;
    }
    else{
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }
}

int main(){
    char string1[MAX_STR_LEN] = "abc";
    char string2[MAX_STR_LEN] = "axyzb";
    char string3[MAX_STR_LEN] = "ab";
    
    printf("String 1: %d\n", match_regex(string1));
    printf("String 2: %d\n", match_regex(string2));
    printf("String 3: %d\n", match_regex(string3));

    return 0;
}