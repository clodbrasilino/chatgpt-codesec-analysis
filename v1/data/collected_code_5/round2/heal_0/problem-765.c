#include <stdio.h>

int findNthPolite(int n) {
    int count = 0, i = 1;
    while (1) {
        int j = i;
        while (j) {
            if ((j & 1) == 0) {
                count++;
                if (count == n) {
                    return i;
                }
                break;
            }
            j = j >> 1;
        }
        i++;
    }
    return -1;
}

int main() {
    int n;
    scanf("%d", &n);
    int result = findNthPolite(n);
    if (result != -1) {
        printf("The %dth polite number is %d\n", n, result);
    }
    else {
        printf("Error: Invalid input\n");
    }
    return 0;
}