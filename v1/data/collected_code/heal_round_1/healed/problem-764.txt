#include <stdio.h>

int countNumericValues(const char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            count++;
        }
    }
    return count;
}

int main() {
    const char str[] = "Hello123World456";
    int numericCount = countNumericValues(str);
    printf("Number of numeric values in the string: %d\n", numericCount);
    return 0;
}