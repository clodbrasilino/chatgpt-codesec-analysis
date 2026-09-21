#include <stdio.h>
#include <string.h>

char string_sum(const char *str, size_t max_len) {
    char sum = 0;
    size_t i;
    
    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        sum += str[i];
    }
    
    return sum;
}

int main(void) {
    const char *test = "Hello";
    char result = string_sum(test, strlen(test) + 1);
    
    printf("String: %s\n", test);
    printf("Character sum: %d\n", result);
    
    return 0;
}