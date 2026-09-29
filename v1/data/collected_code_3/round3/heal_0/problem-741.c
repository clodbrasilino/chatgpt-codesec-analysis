#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool check_same_characters(char* str) {
    int i;
    for(i = 1; i < strlen(str); i++) {
        if(str[i] != str[0]) {
            return false;
        }
    }
    return true;
}

int main() {
    char str[] = "aaaaaa";
    if(check_same_characters(str)) {
        printf("All characters are same.\n");
    } else {
        printf("All characters are not same.\n");
    }
    return 0;
}