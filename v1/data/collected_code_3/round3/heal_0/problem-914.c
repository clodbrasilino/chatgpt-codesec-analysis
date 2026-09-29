#include <stdio.h>
#include <string.h>

int checkAlternatingCharacters(char* str) {
    int i;
    char first = str[0];
    char second = str[1];

    if(first == second) {
        return 0;
    }

    for(i = 2; i < strlen(str); i++) {
        if(i % 2 == 0) {
            if(str[i] != first) {
                return 0;
            }
        } else {
            if(str[i] != second) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    char str1[] = "ABABABAB";
    char str2[] = "AABAABAA";

    if(checkAlternatingCharacters(str1)) {
        printf("%s is made up of two alternating characters\n", str1);
    } else {
        printf("%s is not made up of two alternating characters\n", str1);
    }

    if(checkAlternatingCharacters(str2)) {
        printf("%s is made up of two alternating characters\n", str2);
    } else {
        printf("%s is not made up of two alternating characters\n", str2);
    }

    return 0;
}