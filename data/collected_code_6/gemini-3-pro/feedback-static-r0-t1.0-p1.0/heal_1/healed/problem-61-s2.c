#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countSubstrings(const char* s) {
    if (s == NULL) {
        return 0;
    }

    int n = 0;
    while (s[n] != '\0') {
        if (s[n] < '0' || s[n] > '9') {
            return 0; 
        }
        n++;
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        int current_sum = 0;
        for (int j = i; j < n; j++) {
            current_sum += (s[j] - '0');
            int current_length = j - i + 1;
            if (current_sum == current_length) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char* str = "1101112";
    int result = countSubstrings(str);
    printf("%d\n", result);
    return 0;
}