#include <stdio.h>
#include <regex.h>

int find_sequences(char* str) {
    regex_t reg;
    int result;
    
    if (regcomp(&reg, "[a-z]+_[a-z]+", REG_EXTENDED) != 0) {
        return -1;
    }
    
    result = regexec(&reg, str, 0, NULL, 0);
    regfree(&reg);
    
    return result == 0 ? 1 : 0;
}

int main() {
    char str[] = "hello_world";
    
    if (find_sequences(str)) {
        printf("Match found\n");
    } else {
        printf("No match found\n");
    }
    
    return 0;
}