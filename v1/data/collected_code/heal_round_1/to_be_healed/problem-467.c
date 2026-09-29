/* Possible weaknesses found:
 *  include '<stdio.h>' or provide a declaration of 'printf'
 */
void decimalToOctal(int decimal){
    int octal[100];
    int i = 0;
    
    while(decimal > 0){
        octal[i] = decimal % 8;
        decimal /= 8;
        i++;
    }
    
    for(int j = i - 1; j >= 0; j--){
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  Cannot determine that 'octal[j]' is initialized [premium-bughuntingUninit]
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("%d", octal[j]);
    }
}