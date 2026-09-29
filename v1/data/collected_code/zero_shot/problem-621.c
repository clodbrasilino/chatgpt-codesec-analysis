#include <stdio.h>

void incrementString(char* str, int k) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            str[i] += k;
        }
        i++;
    }
}

int main() {
    char str1[] = "Hello123";
    char str2[] = "Testing456";
    int k = 3;
    
    incrementString(str1, k);
    incrementString(str2, k);
    
    printf("String 1 after increment: %s\n", str1);
    printf("String 2 after increment: %s\n", str2);
    
    return 0;
}