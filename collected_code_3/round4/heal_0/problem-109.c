#include <stdio.h>
#include <string.h>

int binaryToDecimal(char *n) {
    int dec = 0, base = 1, len = strlen(n);
    for(int i=len-1; i>=0; i--) {
        if (n[i] == '1') {
            dec += base;
        }
        base = base * 2;
    }
    return dec;
}

int countRotations(char *bin) {
    int len = strlen(bin);
    char rotated[len+1];
    int count = 0;
    for(int i=0; i<len; i++) {
        int j, k;
        for(j=i, k=0; j<len; j++, k++) {
            rotated[k] = bin[j];
        }
        for(j=0; j<i; j++, k++) {
            rotated[k] = bin[j];
        }
        rotated[k] = '\0';
        if (binaryToDecimal(rotated) % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main() {
    char bin[100];
    printf("Enter a binary string: ");
    scanf("%s", bin);
    printf("Count of rotations with odd decimal value: %d\n", countRotations(bin));
    return 0;
}