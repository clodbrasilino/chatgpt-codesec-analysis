#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return *(char*)b - *(char*)a;
}

void maxSum(char num[]) {
    int len = strlen(num);
    qsort(num, len, sizeof(char), compare);
    int i = 0, j = len - 1;
    char num1[20] = {0}, num2[20] = {0};

    while (i <= j) {
        if (i != j) {
            strncat(num1, &num[i++], 1);
        }
        if (i <= j) {
            strncat(num2, &num[j--], 1);
        }
    }

    printf("The two parts are %s and %s\n", num1, num2);
}

int main() {
    char num[20];
    printf("Enter a number: ");
    scanf("%s", num);
    maxSum(num);
    return 0;
}