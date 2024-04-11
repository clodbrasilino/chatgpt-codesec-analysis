#include <stdio.h>
#include <string.h>

int minSwaps(char *A, char *B, int len) {
    int countA = 0, countB = 0;
    for (int i = 0; i < len; i++) {
        if (A[i] != B[i]) {
            if (A[i] == '1') {
                countA++;
            } else {
                countB++;
            }
        }
    }
    if (countA != countB) {
        return -1;
    }
    return (countA + countB) / 2;
}

int main() {
    char A[] = "1100";
    char B[] = "0011";
    int len = strlen(A);
    if (len != strlen(B)) {
        printf("Strings are not of equal length.\n");
        return 0;
    }
    int result = minSwaps(A, B, len);
    if (result != -1) {
        printf("Minimum number of swaps required to make strings equal: %d\n", result);
    } else {
        printf("It is not possible to make strings equal.\n");
    }
    return 0;
}