#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *s) {
    int n = strlen(s);
    int *doubled = (int *)malloc(2 * n * sizeof(int));
    if (doubled == NULL) {
        return -1;
    }

    for (int i = 0; i < 2 * n; i++) {
        doubled[i] = s[i % n] - '0';
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        int value = 0;
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: left shift of negative value -43 (AFL crash: id:000001,sig:06,src:000000,time:280,execs:165,op:havoc,rep:11)
             * UBSan: left shift of 2147483647 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:7994,execs:3736,op:havoc,rep:12)
             * UBSan: left shift of negative value -1 (AFL crash: id:000000,sig:06,src:000000,time:43,execs:43,op:havoc,rep:11)
             */
            value = (value << 1) | doubled[i + j];
        }
        if (value % 2 == 1) {
            count++;
        }
    }

    free(doubled);
    return count;
}

int main(void) {
    char input[256];
    if (scanf("%255s", input) != 1) {
        return 1;
    }

    int result = count_odd_rotations(input);
    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}