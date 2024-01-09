#include <stdio.h>

int countUnsetBits(int num) {
    int unsetBits = 0;
    
    while (num > 0) {
        if (!(num & 1)) {
            unsetBits++;
        }
        num >>= 1;
    }
    
    return unsetBits;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    
    int unsetBits = countUnsetBits(num);
    printf("Number of unset bits: %d\n", unsetBits);
    
    return 0;
}