#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_keith_number(int num) {
    if (num < 10) {
        return false;
    }

    int temp = num;
    int num_digits = 0;

    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }

    int *sequence = (int *)malloc(num_digits * sizeof(int));
    if (sequence == NULL) {
        return false; 
    }

    temp = num;
    for (int i = num_digits - 1; i >= 0; i--) {
        sequence[i] = temp % 10;
        temp /= 10;
    }

    int next_term = 0;
    while (next_term < num) {
        next_term = 0;
        for (int i = 0; i < num_digits; i++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 1238103011 + 1239319241 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:957,execs:466,op:havoc,rep:3)
             */
            next_term += sequence[i];
        }

        if (next_term == num) {
            free(sequence);
            return true;
        }

        for (int i = 0; i < num_digits - 1; i++) {
            sequence[i] = sequence[i + 1];
        }
        sequence[num_digits - 1] = next_term;
    }

    free(sequence);
    return false;
}

int main(void) {
    int num = 0;

    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (is_keith_number(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return EXIT_SUCCESS;
}