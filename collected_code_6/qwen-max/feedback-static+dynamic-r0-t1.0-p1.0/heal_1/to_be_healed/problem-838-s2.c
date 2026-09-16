#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 */
int minSwapsToEqual(char *a, char *b) {
    int count01 = 0, count10 = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '0' && b[i] == '1') {
            count01++;
        } else if (a[i] == '1' && b[i] == '0') {
            count10++;
        }
    }
    if ((count01 + count10) % 2 != 0) {
        return -1;
    }
    return (count01 + count10) / 2;
}

int main() {
    char a[100], b[100];
    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     */
    scanf("%s", a);
    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     */
    scanf("%s", b);

    int result = minSwapsToEqual(a, b);

    if (result == -1) {
        printf("Strings cannot be made equal by swapping\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}