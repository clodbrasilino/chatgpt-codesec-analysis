#include <stdio.h>
#include <string.h>

int total_ascii_value(const char *str, size_t max_len) {
    int total = 0;
    
    for (size_t i = 0; i < max_len && str[i] != '\0'; i++) {
        total += (unsigned char)str[i];
    }
    
    return total;
}

int main(void) {
    const char *test_string = "Hello, World!";
    size_t max_len = 100;
    int result = total_ascii_value(test_string, max_len);
    
    printf("Total ASCII value of \"%s\": %d\n", test_string, result);
    
    return 0;
}