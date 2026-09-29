#include <regex.h>
#include <stdio.h>

int isValidEmail(char* email) {
    regex_t regex;
    int reti;
    
    reti = regcomp(&regex, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$", REG_EXTENDED);

    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return -1;
    }

    reti = regexec(&regex, email, 0, NULL, 0);

    regfree(&regex);

    if(!reti){
        return 1;
    }
    else if(reti == REG_NOMATCH){
        return 0;
    }
    else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return -1;
    }
}

int main() {
    char email1[] = "example@example.com";
    char email2[] = "wrongemail.com";
  
    if (isValidEmail(email1) == 1) {
        printf("\"%s\" is a valid email address\n", email1);
    } else {
        printf("\"%s\" is not a valid email address\n", email1);
    }

    if (isValidEmail(email2) == 1) {
        printf("\"%s\" is a valid email address\n", email2);
    } else {
        printf("\"%s\" is not a valid email address\n", email2);
    }

    return 0;

}