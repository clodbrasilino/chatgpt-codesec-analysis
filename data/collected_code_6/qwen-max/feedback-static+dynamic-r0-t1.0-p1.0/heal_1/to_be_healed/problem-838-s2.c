#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000020,time:39909,execs:15407,op:havoc,rep:12; likely memory-safety defect
  */

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char a[100], b[100];
    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. (risk 4, buffer)
     */
    scanf("%s", a);
    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. (risk 4, buffer)
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