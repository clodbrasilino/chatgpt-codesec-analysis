#include <stdio.h>

float tupleToFloat(int tuple[]) {
    int integerPart = tuple[0];
    int decimalPart = tuple[1];
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