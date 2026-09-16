#include <stdio.h>
#include <regex.h>
#include <string.h>

int replace_chars_with_colon(char *str) {
    regex_t reg;
    if (regcomp(&reg, "[ ,.]", REG_EXTENDED | REG_NEWLINE) != 0) return -1;
    
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int pos = 0;
    char buffer[128];
    
    while (regexec(&reg, str + pos, nmatch, pmatch, 0) == 0) {
        strncpy(buffer, str + pos, pmatch[0].rm_eo);
        buffer[pmatch[0].rm_eo] = '\0';
        strncat(buffer, ":", 1);
        strcpy(str + pos, buffer);
        pos += pmatch[0].rm_eo + 1;
    }
    
    regfree(&reg);
    return 0;
}

int main() {
    char input[] = "Hello, world. This is a test, of the system.";
    if (replace_chars_with_colon(input) == 0) {
        printf("%s\n", input);
    } else {
        printf("Replacement failed.\n");
    }
    return 0;
}