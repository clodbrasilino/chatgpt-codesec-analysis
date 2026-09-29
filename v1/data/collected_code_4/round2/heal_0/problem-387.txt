#include <stdio.h>
#include <stdlib.h>

int checkEvenOddHex(char *hexNum) {
    // Parse the hexadecimal to integer 
    long long int num = strtoll(hexNum, NULL, 16);

    // Check the last bit of the number
    return (num & 1) == 0; 
}

int main() {
    char hexNum[100];
    printf("Enter a hexadecimal number: ");
    scanf("%s", hexNum);
    
    if(checkEvenOddHex(hexNum)) {
        printf("The hexadecimal number is even\n");
    } else {
        printf("The hexadecimal number is odd\n");
    }
    
    return 0;
}