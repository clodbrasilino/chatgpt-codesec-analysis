#include <stdio.h>

int maxDiff(char* binaryString) {
    int maxDiff = 0, currentDiff = 0;
    int count0 = 0, count1 = 0;
    int i = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'binaryString[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (binaryString[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'binaryString[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (binaryString[i] == '0') {
            count0++;
        /* Possible weaknesses found:
         *  Cannot determine that 'binaryString[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        } else if (binaryString[i] == '1') {
            count1++;
        }
        
        currentDiff = count0 - count1;
        if (currentDiff > maxDiff) {
            maxDiff = currentDiff;
        }
        
        if (currentDiff < 0) {
            count0 = 0;
            count1 = 0;
        }
        
        i++;
    }
    
    return maxDiff;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char binaryString[100];
    printf("Enter a binary string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'binaryString[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", binaryString);
    
    int result = maxDiff(binaryString);
    printf("Maximum difference between 0s and 1s: %d\n", result);
    
    return 0;
}