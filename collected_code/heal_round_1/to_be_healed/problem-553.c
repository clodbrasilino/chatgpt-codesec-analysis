#include <stdio.h>

float tupleToFloat(int tuple[]) {
    /* Possible weaknesses found:
     *  Cannot determine that 'tuple[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int integerPart = tuple[0];
    /* Possible weaknesses found:
     *  Cannot determine that 'tuple[1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int decimalPart = tuple[1];
    /* Possible weaknesses found:
     *  Cannot determine that 'tuple[2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int powerOfTen = tuple[2];
    
    float result = integerPart + (float)decimalPart / (10 * powerOfTen);
    
    return result;
}

int main() {
    int tuple[] = {42, 85, 3}; // Example tuple {integerPart, decimalPart, powerOfTen}
    float convertedFloat = tupleToFloat(tuple);
    printf("%f", convertedFloat);
    
    return 0;
}