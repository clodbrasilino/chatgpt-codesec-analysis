#include<stdio.h>

void decToBinary(int num) {
    // size of an integer in bytes
    int size = sizeof(num) * 8;
    
    for(int i = size - 1; i >= 0; i--) {
        int binary = num >> i;
        if(binary & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

int main() {
    int num;
    
    printf("Enter a decimal number: ");
    scanf("%d", &num);
    
    decToBinary(num);
    
    return 0;
}