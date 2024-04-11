#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

char* findNext(char num[], int n) {
    int i, j;
    for (i = n-1; i > 0; i--)
        if (num[i] > num[i-1])
           break;
    if (i==0) {
        printf("Next number is not possible");
        return num;
    }
    int x = num[i-1], smallest = i;
    for (j = i+1; j < n; j++)
        if (num[j] > x && num[j] < num[smallest])
            smallest = j;
    swap(&num[smallest], &num[i-1]);
    qsort(num + i, n - i, sizeof(char), (int(*)(const void*, const void*))strcmp);
    return num;
}

int main() {
    char digits[] = "534976";
    int n = strlen(digits);
    printf("Next number with same set of digits is %s", findNext(digits, n));
    return 0;
}