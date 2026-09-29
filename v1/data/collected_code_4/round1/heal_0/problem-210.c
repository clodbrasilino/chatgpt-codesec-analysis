#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_string(char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED);
    if (ret) {
        printf("Cannot compile regular expression.\n");
        regfree(&regex);
        return 1;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    
    regfree(&regex);

    if (ret == REG_NOMATCH) {
        return -1;
    }

    
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");  
    fgets(str, sizeof(str), stdin);
  
    str[strlen(str) - 1] = '\0';
    
    int result = check_string(str);
    
    if (result == -1) {
        printf("Invalid string.\n");
    } else if (result == 1) {
        printf("Error during regular expression compilation.\n");
    } else {
        printf("The string is valid.\n");
    }
  
    return EXIT_SUCCESS;
}
