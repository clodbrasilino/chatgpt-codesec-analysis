#include <stdio.h>
#include <regex.h>

void find_sequences(const char* str) {
    regex_t regex;
    regmatch_t match;
    const char* pattern = "[A-Z][a-z]*";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex pattern\n");
        return;
    }
    
    int result = regexec(&regex, str, 1, &match, 0);
    
    while (result == 0) {
        for (int i = match.rm_so; i < match.rm_eo; i++) {
            printf("%c", str[i]);
        }
        printf("\n");
        str += match.rm_eo;
        result = regexec(&regex, str, 1, &match, 0);
    }
    
    regfree(&regex);
}

int main() {
    const char* str = "AbcD efGhiJkl";
    find_sequences(str);
    return 0;
}