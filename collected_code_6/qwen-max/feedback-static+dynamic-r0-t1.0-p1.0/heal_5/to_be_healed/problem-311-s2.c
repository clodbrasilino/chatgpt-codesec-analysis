#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 14, got <no output>
  *  test case 2 failed: expected 15, got <no output>
  *  test case 1 failed: expected 14, got <no output>
  */

long setLeftMostUnsetBit(long n) {
    long result = n;
    bool found = false;
    for (int i = 0; i < sizeof(n) * CHAR_BIT; ++i) {
        if (!(n & (1L << i)) && (n | (1L << i)) <= LONG_MAX) {
            result |= (1L << i);
            found = true;
            break;
        }
    }
    return found ? result : -1;
}

int main() {
    long n;
    printf("Enter a number: ");
    if (scanf("%ld", &n) == 1) {
        long newNumber = setLeftMostUnsetBit(n);
        if (newNumber != -1) {
            printf("New number with the leftmost unset bit set: %ld\n", newNumber);
        } else {
            printf("All bits are set.\n");
        }
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}