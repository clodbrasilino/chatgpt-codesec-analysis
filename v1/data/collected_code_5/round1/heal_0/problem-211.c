#include <stdio.h>

int count_set_bits(int n, int bit) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (((i >> bit) & 1) && (i & 1)) {
            count++;
        }
    }
    return count;
}

int main() {
    int n, bit;
    printf("Enter n value: ");
    scanf("%d", &n);
    printf("Enter bit position: ");
    scanf("%d", &bit);
    
    if(bit > 31) {
        printf("Bit position should be between 0 and 31\n");
        return -1;
    }
    
    int count = count_set_bits(n, bit);
    printf("Count of numbers where 0th and %dth bit is set: %d\n", bit, count);

    return 0;
}