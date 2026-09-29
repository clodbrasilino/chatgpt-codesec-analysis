#include <stdio.h>
#include <string.h>

int countSubstrings(char *str) {
    int len = strlen(str), count = 0;
    for (int i = 0; i < len; i++) {
        int sum = 0, j = 0;
        while (i + j < len && (sum + (str[i + j] - '0')) <= (j + 1)) {
            sum += str[i + j] - '0';
            if (sum == j + 1) {
                count++;
            }
            j++;
        }
    }
    return count;
}

int main() {
    char input[256];
    printf("Enter a number: ");
    scanf("%s", input);
    int result = countSubstrings(input);
    printf("Count of substrings: %d\n", result);
    return 0;
}