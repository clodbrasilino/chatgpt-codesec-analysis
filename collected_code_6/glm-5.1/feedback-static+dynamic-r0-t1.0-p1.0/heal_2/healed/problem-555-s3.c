#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
        char buf[41];
        int pos = sizeof(buf) - 1;
        buf[pos] = '\0';
        while (result > 0) {
            if (pos <= 0) {
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