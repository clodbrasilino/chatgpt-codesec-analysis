#include <stdio.h>
#include <string.h>
#include <ctype.h>

int binary_to_decimal(const char *binary) {
    int decimal = 0;
    size_t len = strlen(binary);
    
    for (size_t i = 0; i < len; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            return -1;
        }
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1610612736 * 2 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2560,execs:1066,op:havoc,rep:7)
         */
        decimal = decimal * 2 + (binary[i] - '0');
    }
    
    return decimal;
}

int main(void) {
    char input[65];
    
    printf("Enter a binary number: ");
    if (scanf("%64s", input) != 1) {
        printf("Error reading input\n");
        return 1;
    }
    
    int result = binary_to_decimal(input);
    
    if (result == -1) {
        printf("Invalid binary number\n");
        return 1;
    }
    
    printf("Decimal equivalent: %d\n", result);
    
    return 0;
}