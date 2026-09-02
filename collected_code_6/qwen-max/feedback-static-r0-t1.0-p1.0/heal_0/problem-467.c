#include <stdio.h>
#include <stdlib.h>

char* dec_to_oct(int num) {
    char *octal = (char*)malloc(12 * sizeof(char));  // Enough for 32 bit integers
    int i = 0;
    if (!octal) return NULL;  // Check for memory allocation failure

    while (num != 0) {
        octal[i++] = (num % 8) + '0';
        num /= 8;
    }
    if (i == 0) {  // Handle the case where num is 0
        octal[i++] = '0';
    }
    octal[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        int temp = octal[j];
        octal[j] = octal[i - j - 1];
        octal[i - j - 1] = temp;
    }

    return octal;
}

int main() {
    int num = 785;
    char *octal = dec_to_oct(num);
    if (octal) {
        printf("Octal: %s\n", octal);
        free(octal);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}