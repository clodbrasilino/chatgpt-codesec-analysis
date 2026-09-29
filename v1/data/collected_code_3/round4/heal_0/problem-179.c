#include <stdio.h>

int isKeith(int X) {
    int temp = X, sum = 0;
    int arr[100];
    int i = 0;

    while (temp > 0) {
        arr[i] = temp % 10;
        sum += arr[i];
        temp = temp / 10;
        i++;
    }

    int j;
    for (j = i - 1; j >= 0; j--) {
        if (sum == X)
            return 1;
        sum = sum - arr[j] + sum;
    }

    return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isKeith(num))
        printf("%d is a Keith number\n", num);
    else
        printf("%d is not a Keith number\n", num);

    return 0;
}