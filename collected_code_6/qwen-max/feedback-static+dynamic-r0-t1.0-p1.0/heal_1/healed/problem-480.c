#include <stdio.h>
#include <string.h>
#include <limits.h>

int findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    int max = -1;
    int result = 0;  // Initialize result to a default value

    for (int i = 0; str[i]; i++) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
        if (max < count[c]) {
            max = count[c];
            result = c;
        }
    }

    return result;
}

int main() {
    const char *input = "test string";
    int maxChar = findMaxOccurringChar(input);
    printf("The maximum occurring character is: %c\n", maxChar);
    return 0;
}