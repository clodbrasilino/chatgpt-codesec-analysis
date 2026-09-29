#include<stdio.h>

int count_Pairs(int arr[], int n) {
    int even_XOR = 0;
    int even_count = 0, odd_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            even_count++;
        else
            odd_count++;
    }

    even_XOR += (even_count * (even_count - 1) / 2);
    even_XOR += (odd_count * (odd_count - 1) / 2);
    
    return even_XOR;
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Number of pairs with even XOR is %d\n", count_Pairs(arr, n));
    
    return 0;
}