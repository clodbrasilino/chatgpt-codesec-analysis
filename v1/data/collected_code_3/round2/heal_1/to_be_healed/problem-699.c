#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int minSwaps(char *str1, char *str2, int n) {
    int count1 = 0, count2 = 0;
    for (int i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            if (str1[i] == '1')
                count1++;
            else
                count2++;
        }
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     */
    return (count1 + count2 - abs(count1 - count2)) / 2;
}

int main() {
    char str1[] = "1100";
    char str2[] = "1010";
    int n = strlen(str1);
    printf("Minimum swaps required is %d", minSwaps(str1, str2, n));
    return 0;
}