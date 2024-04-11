#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return *(char*)b - *(char*)a;
}

void maxSum(char num[]) {
    int len = strlen(num);
    qsort(num, len, sizeof(char), compare);
    int i;
    for (i = 0; i < len; i++) {
        printf("%c", num[i]);
    }
}

int main() {
    char num[100];
    printf("Enter a number: ");
    scanf("%s", num);
    maxSum(num);
    return 0;
}