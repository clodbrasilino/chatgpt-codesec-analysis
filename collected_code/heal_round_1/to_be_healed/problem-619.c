/* Possible weaknesses found:
 *  include '<ctype.h>' or provide a declaration of 'isdigit'
 */
void moveNumbersToString(char *string) {
    int index = 0;
    int numIndex = 0;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  
    /* Possible weaknesses found:
     *  Cannot determine that 'string[index]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (string[index] != '\0') {
        /* Possible weaknesses found:
         *  implicit declaration of function 'isdigit' [-Wimplicit-function-declaration]
         *  Cannot determine that 'string[index]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (isdigit(string[index])) {
            /* Possible weaknesses found:
             *  Cannot determine that 'string[index]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            string[numIndex] = string[index];
            numIndex++;
        }
        index++;
    }
  
    string[numIndex] = '\0';
}