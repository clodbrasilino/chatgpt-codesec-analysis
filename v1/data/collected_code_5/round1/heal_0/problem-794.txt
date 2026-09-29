#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool string_match(const char* str) {
    size_t len = strlen(str);
    if(len < 2) {
        return false;
    }

    if(str[0] == 'a' && str[len - 1] == 'b') {
        return true;
    }
    
    return false;
}

int main() {
    char string1[] = "a123b";
    char string2[] = "123b";
    char string3[] = "a123";
  
    printf("%d\n", string_match(string1));
    printf("%d\n", string_match(string2));
    printf("%d\n", string_match(string3));
  
    return 0;
}