#include <stdio.h>
#include <string.h>

int countSwaps(const char *str1, const char *str2, int len) {
    int mismatchCount = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            mismatchCount++;
        }
    }
    return mismatchCount / 2;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000013,time:36623,execs:16508,op:havoc,rep:45; likely memory-safety defect
  */

int main() {
    char str1[256], str2[256];
    printf("Enter the first binary string: ");
    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     */
    scanf("%s", str1);
    printf("Enter the second binary string: ");
    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     */
    scanf("%s", str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        printf("Strings must be of the same length\n");
        return 1;
    }

    int swaps = countSwaps(str1, str2, len1);
    printf("Minimum number of swaps required: %d\n", swaps);

    return 0;
}