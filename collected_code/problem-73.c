#include <stdio.h>
#include <regex.h>

void split_string(char *string, char *delimiters) {
    regex_t regex;
    regmatch_t match;
    int res = regcomp(&regex, delimiters, REG_EXTENDED);

    if (res) {
        printf("Error compiling regex\n");
        return;
    }

    char *token = strtok(string, delimiters);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, delimiters);
    }

    regfree(&regex);
}

int main() {
    char input_string[] = "This,is;a test-string";
    char delim[] = "[,;]";
    
    split_string(input_string, delim);
    
    return 0;
}