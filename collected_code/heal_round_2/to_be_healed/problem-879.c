#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_MSG_BUF_LEN 100
#define MAX_STR_LEN 100

int match_regex(const char *string){
    regex_t regex;
    int reti;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string1[MAX_STR_LEN] = "abc";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string2[MAX_STR_LEN] = "axyzb";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string3[MAX_STR_LEN] = "ab";
    
    printf("String 1: %d\n", match_regex(string1));
    printf("String 2: %d\n", match_regex(string2));
    printf("String 3: %d\n", match_regex(string3));

    return 0;
}