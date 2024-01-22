#include <stdio.h>
#include <string.h>

#define MAX_HEX_LENGTH 21

int isHexEvenOrOdd(const char *hex) {
    int i = 0;

    if(hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
        i = 2;
    }

    while(hex[i] != '\0' && i < MAX_HEX_LENGTH - 1) {
        if(!((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'A' && hex[i] <= 'F') || (hex[i] >= 'a' && hex[i] <= 'f'))) {
            return -1;
        }
        i++;
    }

    int decimal = 0;
    i = 0;

    while (hex[i] != '\0' && i < MAX_HEX_LENGTH - 1) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            decimal = decimal * 16 + (hex[i] - '0');
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F') {
            decimal = decimal * 16 + (hex[i] - 'A' + 10);
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f') {
            decimal = decimal * 16 + (hex[i] - 'a' + 10);
        }
        i++;
    }

    return decimal % 2 == 0;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char hex[MAX_HEX_LENGTH];

    printf("Enter a hexadecimal number: ");
    fgets(hex, sizeof(hex), stdin);

    hex[strcspn(hex, "\n")] = '\0';

    int result = isHexEvenOrOdd(hex);
    if(result == -1){
        printf("Invalid Hexadecimal number.\n");
    }
    else if (result) {
        printf("The hexadecimal number is even.\n");
    } else {
        printf("The hexadecimal number is odd.\n");
    }

    return 0;
}