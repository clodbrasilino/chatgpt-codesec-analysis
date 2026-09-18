#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

int isValidEmail(char *email) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$", REG_EXTENDED);
    if(ret){
        printf("Could not compile regex\n");
        return 0;
    }

    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    if(!ret)
    {
        return 1;
    }
    else if(ret == REG_NOMATCH){
        return 0;
    }
    else{
        printf("Regex match failed\n");
        return 0;
    }
}

int main()
{
    char email[MAX_EMAIL_LENGTH];
    printf("Enter the email address: \n");
    scanf("%s", email);

    int isValid = isValidEmail(email);

    if (isValid)
    {
        printf("Email is valid\n");
    }
    else
    {
        printf("Email is not valid\n");
    }
    return 0;
}