#include <stdio.h>

// Function to convert string to lower case
void toLowerCase(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i++;
    }
}

int main() {
    char str[] = "Hello World";
    printf("Before Conversion: %s\n", str);
    toLowerCase(str);
    printf("After Conversion: %s\n", str);

    return 0;
}