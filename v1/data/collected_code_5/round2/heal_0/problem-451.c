#include <stdio.h>
#include <ctype.h>

void remove_spaces(char* str) {
    char* result = str;
    char* ptr = str;
  
    while (*ptr != '\0') {
        if(!isspace((unsigned char)*ptr)) {
            *result = *ptr;
            result++;
        }
        ptr++;
    }
    *result = '\0';
}

int main() {
    char str[] = "Remove   me   some   spaces";
    remove_spaces(str);
    printf("%s\n", str);
    return 0;
}