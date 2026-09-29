#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

bool is_undulating(long long num) {
    if (num < 0) {
        num = -num;
    }
    
    if (num < 100) {
        return num >= 10 && (num / 10 != num % 10);
    }
    
    char *str = NULL;
    int len = 0;
    size_t buffer_size = 24;
    
    str = (char *)malloc(buffer_size);
    if (str == NULL) {
        return false;
    }
    
    len = snprintf(str, buffer_size, "%lld", num);
    
    if (len < 0) {
        free(str);
        return false;
    }
    
    if ((size_t)len >= buffer_size) {
        char *temp = (char *)realloc(str, (size_t)len + 1);
        if (temp == NULL) {
            free(str);
            return false;
        }
        str = temp;
        snprintf(str, (size_t)len + 1, "%lld", num);
    }
    
    if (str[0] == str[1]) {
        free(str);
        return false;
    }
    
    for (int i = 2; i < len; i++) {
        if (str[i] != str[i - 2]) {
            free(str);
            return false;
        }
    }
    
    free(str);
    return true;
}

int main(void) {
    long long test_cases[] = {121, 1212, 212, 12121, 123, 111, 12345, 9090, 151515, 100};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("%lld: %s\n", test_cases[i], is_undulating(test_cases[i]) ? "Undulating" : "Not undulating");
    }
    
    return 0;
}