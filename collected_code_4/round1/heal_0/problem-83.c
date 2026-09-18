#include <stdio.h>
#include <string.h>

char sum_character(const char *str) {
    long long int sum = 0;
    int len = strlen(str);
    
    for(int i = 0; i < len; i++) {
        sum += (int)str[i];
    }
    
    return (char)(sum % 256);
}

int main() {
    char *str = "Hello";
    printf("%c\n", sum_character(str));

    return 0;
}