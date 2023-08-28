#include <stdio.h>
#include <regex.h>

void removeWhitespace(char *str) {
    regex_t regex;
    const char *pattern = "[[:space:]]";
    
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex pattern\n");
        return;
    }
    
    char *output = regreplace(str, regex, "", REG_EXTENDED);
    printf("%s", output);
    regfree(&regex);
    free(output);
}

int main() {
    char str[] = "Hello World! How are you?";
    removeWhitespace(str);
    return 0;
}