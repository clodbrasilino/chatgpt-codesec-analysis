#include <stdio.h>
#include <regex.h>

int match_regex(char *string){
    regex_t regex;
    int reti;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char msgbuf[100];

    reti = regcomp(&regex, "a.*b$", 0);
    if(reti){
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    /* Possible weaknesses found:
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    reti = regexec(&regex, string, 0, NULL, 0);
    if(!reti){
        return 1;
    }
    else if(reti == REG_NOMATCH){
        return 0;
    }
    else{
        /* Possible weaknesses found:
         *  Cannot determine that 'msgbuf[0]' is initialized [premium-bughuntingUninit]
         */
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }
}

int main(){
    char *string1 = "abc";
    char *string2 = "axyzb";
    char *string3 = "ab";
    
    printf("String 1: %d\n", match_regex(string1));
    printf("String 2: %d\n", match_regex(string2));
    printf("String 3: %d\n", match_regex(string3));

    return 0;
}