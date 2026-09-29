#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

int url_check(const char *url) {
    regex_t regex;
    int return_val;

    return_val = regcomp(&regex, "^(http|https)://"
    "[a-zA-Z0-9\\-\\.]+\\."
    "[a-zA-Z]{2,3}(/\\S*)?$", REG_EXTENDED);

    if(return_val) {
        printf("Could not compile regex\n");
        return 0;  
    }

    return_val = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if(!return_val)
        return 1;
    else if(return_val == REG_NOMATCH)
        return 0;
    else 
        return 0;
}

int main() {
    char url[MAX_URL_LENGTH];

    printf("Enter a URL to check: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    
    url[strlen(url) - 1] = '\0';

    if(url_check(url))
        printf("URL is valid\n");
    else
        printf("URL is invalid\n");

    return 0;
}