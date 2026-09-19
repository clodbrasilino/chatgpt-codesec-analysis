#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 */
int minSwapsToEqual(char *a, char *b, int len) {
    int mismatch[2] = {0};
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            mismatch[a[i] - '0']++;
        }
    }
    if (mismatch[0] != mismatch[1]) {
        return -1;
    }
    return (mismatch[0] + 1) / 2;
}

int main() {
    char *a = "1100";
    char *b = "1001";
    int len = strlen(a);
    int result = minSwapsToEqual(a, b, len);
    printf("%d\n", result);
    return 0;
}