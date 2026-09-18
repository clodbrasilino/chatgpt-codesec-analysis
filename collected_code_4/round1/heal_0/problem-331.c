#include <stdio.h>

int countUnsetBits(int n) {
    int counter = 0;
    while (n) {
        counter += (n & 1) ? 0 : 1;
        n >>= 1;
    }
    return counter;
}

int main() {
    int num;
    printf("Enter a number:\n");
    if(scanf("%d", &num) != 1) {
        printf("Failed to read the number.\n");
        return 1;
    }
    int unsetBits = countUnsetBits(num);
    printf("Number of unset bits: %d\n", unsetBits);
    return 0;
}