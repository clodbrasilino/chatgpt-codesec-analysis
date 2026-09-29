#include <stdio.h>
#include <string.h>

int countSubstringsWithSameStartEnd(const char *str) {
    int count = 0;
    int n = strlen(str);
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    const char *input = "abcab";
    int result = countSubstringsWithSameStartEnd(input);
    printf("Number of substrings starting and ending with the same character: %d\n", result);
    return 0;
}