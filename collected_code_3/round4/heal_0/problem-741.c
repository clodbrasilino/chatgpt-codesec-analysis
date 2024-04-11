#include <stdio.h>
#include <stdbool.h>

bool check_same_char(char* str) {
    int i = 1;
    while (str[i]) {
        if (str[i] != str[0]) {
            return false;
        }
        i++;
    }
    return true;
}

int main() {
    char str[] = "aaaaa";
    if (check_same_char(str)) {
        printf("All characters are same.\n");
    } else {
        printf("All characters are not same.\n");
    }
    return 0;
}