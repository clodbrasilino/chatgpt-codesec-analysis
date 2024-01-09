#include <stdio.h>

int getRightmostSetBit(int num) {
    // Performing bitwise AND of num and its twos' complement
    int twosComplement = num & (-num);
  
    // Finding position of the rightmost set bit using logarithmic formula
    int position = -1;
    while (twosComplement != 0) {
        twosComplement = twosComplement >> 1;
        position++;
    }
  
    return position;
}

int main() {
    int num = 21;
    int position = getRightmostSetBit(num);
  
    printf("Position of the rightmost set bit in %d is %d\n", num, position);
  
    return 0;
}