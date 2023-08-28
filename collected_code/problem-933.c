#include <stdio.h>
#include <regex.h>

void camelToSnake(char *str) {
    char pattern[] = "([A-Z])";
    char replacement[] = "_\\1";
    regex_t regex;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed");
        return;
    }
    
    char *result = NULL;
    int length = regerror(REG_EBUF, &regex, NULL, 0);
    length += strlen(str) + 1;
    result = malloc(length);
    
    regmatch_t match;
    int offset = 0;
    int status = 0;
    int i = 0;
    
    while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int start = match.rm_so;
        int end = match.rm_eo;
        int matchedLength = end - start;
        
        strncpy(result + i, str + offset, start);
        i += start;
        strncpy(result + i, replacement, strlen(replacement));
        i += strlen(replacement);
        
        offset += end;
    }
    
    strcpy(result + i, str + offset);
    printf("%s\n", result);
    
    free(result);
    regfree(&regex);
}

int main() {
    char input[] = "camelCaseString";
    camelToSnake(input);
    
    return 0;
}