#include <stdio.h>
#include <regex.h>
#include <string.h>

int check_if_starts_with_substring(char *str, char *substring){
    regex_t reg;

    if (str == NULL || substring == NULL) {
        return -1;
    }

    int reti = regcomp(&reg, substring, 0);
    if (reti) {
        return -1;
    }
    
    reti = regexec(&reg, str, 0, NULL, 0);
    regfree(&reg);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}


int main() {
    char* str = "Hello world!";
    char* substring = "Hello";

    int result = check_if_starts_with_substring(str, substring);

    if (result == 1) {
        printf("String starts with the substring\n");
    } else if (result == 0) {
        printf("String does not start with the substring\n");
    } else {
        printf("An error occurred\n");
    }  

    return 0;
}