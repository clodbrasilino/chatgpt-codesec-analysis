#include <stdio.h>
#include <regex.h>
#include <string.h>

int starts_ends_same(const char *str) {
    regex_t regex;
    int ret;
    char pattern[] = "^(.).*\\1$";
    
    if (str == NULL || strlen(str) == 0) {
        return 0;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main() {
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (starts_ends_same(input)) {
        printf("The string starts and ends with the same character.\n");
    } else {
        printf("The string does not start and end with the same character.\n");
    }
    
    return 0;
}