#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isBinaryString(char* str) {
    int i, len = strlen(str);
    for(i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

int main() {
    char binString1[] = "101010101";
    char binString2[] = "124572103";
    
    printf("%s is a binary string: %d\n", binString1, isBinaryString(binString1));
    printf("%s is a binary string: %d\n", binString2, isBinaryString(binString2));
    
    return 0;
}