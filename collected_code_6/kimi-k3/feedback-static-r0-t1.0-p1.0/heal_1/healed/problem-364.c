#include <stdio.h>
#include <string.h>

int countFlips(const char *str) {
    int flips1 = 0, flips2 = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (str[i] != (i % 2 == 0 ? '0' : '1')) {
            flips1++;
        } else {
            flips2++;
        }
    }

    return (flips1 < flips2) ? flips1 : flips2;
}

int main() {
    char str[100];

    printf("Enter a binary string: ");
    if (scanf("%99s", str) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    int result = countFlips(str);
    printf("Number of flips required: %d\n", result);

    return 0;
}