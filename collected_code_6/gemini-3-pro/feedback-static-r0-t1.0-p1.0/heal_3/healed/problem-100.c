#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isAllNines(const char *numStr, int n) {
    for (int i = 0; i < n; ++i) {
        if (numStr[i] != '9') {
            return false;
        }
    }
    return true;
}

void printNextPalindrome(const char *numStr) {
    if (numStr == NULL) {
        return;
    }

    int n = 0;
    while (n < 4096 && numStr[n] != '\0') {
        n++;
    }

    if (n == 0) {
        return;
    }

    if (isAllNines(numStr, n)) {
        printf("1");
        for (int i = 0; i < n - 1; ++i) {
            printf("0");
        }
        printf("1\n");
        return;
    }

    char *result = (char *)malloc((n + 1) * sizeof(char));
    if (result == NULL) {
        return;
    }

    for (int k = 0; k < n; k++) {
        result[k] = numStr[k];
    }
    result[n] = '\0';

    int mid = n / 2;
    int i = mid - 1;
    int j = (n % 2 == 0) ? mid : mid + 1;
    bool leftSmaller = false;

    while (i >= 0 && result[i] == result[j]) {
        i--;
        j++;
    }

    if (i < 0 || result[i] < result[j]) {
        leftSmaller = true;
    }

    while (i >= 0) {
        result[j] = result[i];
        i--;
        j++;
    }

    if (leftSmaller) {
        int carry = 1;
        i = mid - 1;

        if (n % 2 == 1) {
            result[mid] += carry;
            carry = result[mid] - '0' >= 10 ? 1 : 0;
            result[mid] = (result[mid] - '0') % 10 + '0';
            j = mid + 1;
        } else {
            j = mid;
        }

        while (i >= 0 && carry > 0) {
            result[i] += carry;
            carry = result[i] - '0' >= 10 ? 1 : 0;
            result[i] = (result[i] - '0') % 10 + '0';
            result[j] = result[i];
            i--;
            j++;
        }
    }

    printf("%s\n", result);
    free(result);
}

int main(int argc, char *argv[]) {
    char defaultNum[] = "12345";
    char *numStr = defaultNum;

    if (argc > 1) {
        numStr = argv[1];
    }

    printNextPalindrome(numStr);

    return 0;
}