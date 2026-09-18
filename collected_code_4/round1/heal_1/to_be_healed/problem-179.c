#include<stdio.h>
#include<stdlib.h>

int isKeithNumber(int n) {
    int num = n;
    int reverse = 0;
    while(n > 0) {
        reverse = reverse * 10 + n % 10;
        n /= 10;
    }
    int *arr = (int*)calloc(50, sizeof(int));
    int i = 0;
    while(reverse > 0) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        arr[i] = reverse % 10;
        reverse /= 10;
        i++;
    }
    int sum = 0, k = i;
    for(int j = 0; j < k; j++) {
        sum += arr[j];
        if(sum == num) {
            free(arr);
            return 1;
        }
        if(sum > num) {
            free(arr);
            return 0;
        }
        if(j == k-1) {
            for(int m = 0; m < k-1; m++)
                arr[m] = arr[m + 1];
            arr[k-1] = sum;
            j = -1;
        }
    }
    free(arr);
    return 0;
}

int main() {
    int num;
    printf("Enter the number: ");
    scanf("%d", &num);
    if(isKeithNumber(num))
        printf("%d is a Keith Number\n", num);
    else
        printf("%d is not a Keith Number\n", num);
    return 0;
}