#include <stdio.h>

int countRotationsOfOddValueBinaryString(const char *str) {
    int count = 0;
    int i = 0;
    while (str[i] != '\0') {
        int num = str[i] - '0';
        if (num % 2 != 0) {
            count++;
        }
        i++;
    }
    return count;
}

int main() {
    char str[] = "1010111";
    int rotations = countRotationsOfOddValueBinaryString(str);
    printf("Count of rotations of binary string with odd value: %d\n", rotations);
    return 0;
}