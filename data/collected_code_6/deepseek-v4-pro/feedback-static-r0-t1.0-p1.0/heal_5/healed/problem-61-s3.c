#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

int countSubstrings(const char *str, int length) {
    int n = length;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += str[j] - '0';
            int len = j - i + 1;
            if (sum == len) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char str[MAX_LENGTH + 2];
    
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = 0;
        while (len < sizeof(str) && str[len] != '\0') {
            len++;
        }
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
        
        for (size_t i = 0; i < len; i++) {
            if (str[i] < '0' || str[i] > '9') {
                return 1;
            }
        }
        
        if (len > 0 && len <= MAX_LENGTH) {
            printf("%d\n", countSubstrings(str, (int)len));
        }
    }
    
    return 0;
}