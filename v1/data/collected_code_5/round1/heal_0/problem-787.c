#include <stdio.h>
#include <string.h>

int match_pattern(const char *str) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == 'a' && str[i+1] == 'b' && str[i+2] == 'b' && str[i+3] == 'b'){
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    const char *string1 = "abcbb";
    const char *string2 = "abbba";

    printf("%s -> %s\n", string1, match_pattern(string1) ? "match" : "no match");
    printf("%s -> %s\n", string2, match_pattern(string2) ? "match" : "no match");

    return 0;
}