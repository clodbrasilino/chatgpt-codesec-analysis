#include <stdio.h>

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
}

int main() {
    char str[] = "Hello World";
    printf("Before Conversion: %s\n", str);
    toLowerCase(str);
    printf("After Conversion: %s\n", str);

    return 0;
}