#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(char *a, char *b) {
    int count[2] = {0, 0};
    int n = strlen(a);
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            count[a[i] - '0']++;
        }
    }
    return count[1] % 2 == 0 ? count[1] / 2 : -1;
}

int main() {
    char a[] = "1100";
    char b[] = "1001";
    int result = minSwaps(a, b);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    return 0;
}