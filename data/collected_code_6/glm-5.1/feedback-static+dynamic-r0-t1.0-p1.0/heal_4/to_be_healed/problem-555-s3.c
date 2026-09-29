#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 30, got <no output>
  *  test case 1 failed: expected 210, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  */

__int128 find_difference(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    __int128 sum = (__int128)n * (n + 1) / 2;
    __int128 sum_cubes = sum * sum;
    return sum_cubes - sum;
}

int main(void) {
    int n = 0;
    if (scanf("%d", &n) != 1) {
        exit(EXIT_FAILURE);
    }
    __int128 result = find_difference(n);
    if (result < 0) {
        printf("-");
        result = -result;
    }
    if (result > 9) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buf[41];
        size_t pos = sizeof(buf) - 1;
        buf[pos] = '\0';
        while (result > 0) {
            if (pos == 0) {
                exit(EXIT_FAILURE);
            }
            buf[--pos] = (result % 10) + '0';
            result /= 10;
        }
        printf("%s\n", buf + pos);
    } else {
        printf("%c\n", result + '0');
    }
    return 0;
}