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

void printNextPalindrome(char *numStr) {
    if (numStr == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(numStr);
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
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result, numStr);

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