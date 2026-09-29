#include <stdio.h>
#include <stdbool.h>

long long ProductOfNonRepeated(int* nums, int numsSize) {
    int i, j;
    long long product = 1;
    bool isRepeated;

    for(i = 0; i < numsSize; i++) {
        isRepeated = false;
        for(j = i + 1; j < numsSize; j++) {
            if(nums[i] == nums[j]) {
                isRepeated = true;
                break;
            }
        }

        if(!isRepeated) {
            product *= nums[i];
        }
    }

    return product;
}

int main() {
    int N, i;

    printf("Enter the number of elements: ");
    scanf("%d", &N);

    int arr[N];

    printf("Enter the elements: ");
    for(i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    long long result = ProductOfNonRepeated(arr, N);
    printf("The product of non-repeated elements is: %lld\n", result);

    return 0;
}