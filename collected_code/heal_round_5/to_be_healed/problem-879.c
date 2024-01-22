#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_BUF_LEN 100
#define MAX_STR_LEN 100

int match_regex(const char *string) {
    if(string == NULL) {
        fprintf(stderr, "Null string\n");
        return -1;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(string);

    if(len > MAX_STR_LEN) {
        fprintf(stderr, "Input size greater than buffer size\n");
        return -1;
    }

    regex_t regex;
    int reti;
    char *msgbuf = (char *) malloc(sizeof(char) * (len+1));
    if(msgbuf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    reti = regcomp(&regex, "a.*b$", 0);
    if(reti) {
        fprintf(stderr, "Could not compile regex\n");
        regfree(&regex);
        free(msgbuf);
        return -1;
    }

    reti = regexec(&regex, string, 0, NULL, 0);

    if(!reti) {
        regfree(&regex);
        free(msgbuf);
        return 1;
    } else if(reti == REG_NOMATCH) {
        regfree(&regex);
        free(msgbuf);
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, len+1);
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        free(msgbuf);
        return -1;
    }
}

int main() {
    char *string1 = "abc";
    if(match_regex(string1) == -1) {
        fprintf(stderr, "An error occurred\n");
        return -1;
    }

    char *string2 = "axyzb";
    if(match_regex(string2) == -1) {
        fprintf(stderr, "An error occurred\n");
        return -1;
    }

    char *string3 = "ab";
    if(match_regex(string3) == -1) {
        fprintf(stderr, "An error occurred\n");
        return -1;
    }

    printf("String 1: %d\n", match_regex(string1));
    printf("String 2: %d\n", match_regex(string2));
    printf("String 3: %d\n", match_regex(string3));

    return 0;
}
/* Possible weaknesses found:
 *  data definition has no type or storage class
 *  type defaults to 'int' in declaration of 'Now' [-Wimplicit-int]
 *  syntax error [syntaxError]
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'allocated'
 */
Now, dynamically allocated memory is used to handle strings. This prevents the possibility of overflow by statically-sized arrays. The input string is checked if it is NULL. regfree and free are called to release memory before we return from the function. This prevents memory leaks. Regerror usage has an appropriately sized buffer.