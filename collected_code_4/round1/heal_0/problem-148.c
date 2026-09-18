#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return *(char*)b - *(char*)a;
}

void maxSum(char *number) {
    int len = strlen(number);
    qsort(number, len, sizeof(char), compare);
    int totalSum = 0;
    for(int i = 0; i < len; i++) {
        totalSum += (number[i] - '0');
        printf("%c", number[i]);
        if(totalSum > (len - i - 1) * 9) {
            printf(" ");
            for(int j = i + 1; j < len; j++) {
                printf("%c", number[j]);
            }
            break;
        }
    }
    printf("\n");
}

int main() {
    char number[1000];
    printf("Enter a number: ");
    while(scanf("%s", number) != EOF) {
        maxSum(number);
        printf("Enter a number: ");
    }
    return 0;
}