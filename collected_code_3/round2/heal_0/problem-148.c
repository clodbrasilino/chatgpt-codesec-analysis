#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return *(char*)b - *(char*)a;
}

void maxSumDivide(int num) {
    char str[50];
    sprintf(str, "%d", num);
    int n = strlen(str);

    qsort(str, n, sizeof(str[0]), compare);

    int i = 0;
    while (str[i] == '0') {
        i++;
    }

    int j = i;
    while (j < n && str[j] != '5') {
        j++;
    }

    if (i != j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    printf("%s\n", str);
}

int main() {
    int num = 532;
    maxSumDivide(num);
    return 0;
}