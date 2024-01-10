#include <stdio.h>

int isHexEvenOrOdd(char hex[]) {
    int i = 0;
    
    // Skip any leading "0x" or "0X"
    /* Possible weaknesses found:
     *  Cannot determine that 'hex[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'hex[1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
        i = 2;
    
    // Iterate through each digit of the hexadecimal number
    /* Possible weaknesses found:
     *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (hex[i] != '\0') {
        // If the current digit is not a valid hexadecimal digit, return 0
        /* Possible weaknesses found:
         *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (!((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'A' && hex[i] <= 'F') || (hex[i] >= 'a' && hex[i] <= 'f')))
            return 0;
        
        i++;
    }
    
    // Determine the numerical value of the hexadecimal number
    int decimal = 0;
    i = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (hex[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (hex[i] >= '0' && hex[i] <= '9')
            /* Possible weaknesses found:
             *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            decimal = decimal * 16 + (hex[i] - '0');
        /* Possible weaknesses found:
         *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            /* Possible weaknesses found:
             *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            decimal = decimal * 16 + (hex[i] - 'A' + 10);
        /* Possible weaknesses found:
         *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            /* Possible weaknesses found:
             *  Cannot determine that 'hex[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            decimal = decimal * 16 + (hex[i] - 'a' + 10);
        
        i++;
    }
    
    // Check if the decimal value is even or odd
    if (decimal % 2 == 0)
        return 1; // Even
    else
        return 0; // Odd
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char hex[20];
    printf("Enter a hexadecimal number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'hex[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", hex);
    
    if (isHexEvenOrOdd(hex))
        printf("The hexadecimal number is even.\n");
    else
        printf("The hexadecimal number is odd.\n");
    
    return 0;
}