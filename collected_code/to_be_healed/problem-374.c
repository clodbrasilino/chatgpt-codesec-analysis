#include<stdio.h>
#include<string.h>

void swap(char* x, char* y) {
    char temp;
    /* Possible weaknesses found:
     *  Cannot determine that '*x' is initialized [premium-bughuntingUninit]
     */
    temp = *x;
    /* Possible weaknesses found:
     *  Cannot determine that '*y' is initialized [premium-bughuntingUninit]
     */
    *x = *y;
    *y = temp;
}

void permute(char* str, int l, int r) {
    int i;
    if (l == r) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%s\n", str);
    } else {
        for (i = l; i <= r; i++) {
            swap((str + l), (str + i));
            permute(str, l + 1, r);
            swap((str + l), (str + i)); // backtrack
        }
    }
}

int main() {
    char str[] = "AAB";
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int n = strlen(str);
    permute(str, 0, n - 1);
    return 0;
}