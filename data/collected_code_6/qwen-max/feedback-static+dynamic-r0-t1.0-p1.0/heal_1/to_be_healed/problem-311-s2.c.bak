#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got -9223372036854775796
  *  test case 2 failed: expected 15, got -9223372036854775793
  *  test case 0 failed: expected 14, got -9223372036854775798
  */

long setLeftMostUnsetBit(long n) {
    long result = n;
    bool found = false;
    for (int i = sizeof(n) * CHAR_BIT - 1; i >= 0; --i) {
        if (!(n & (1L << i))) {
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