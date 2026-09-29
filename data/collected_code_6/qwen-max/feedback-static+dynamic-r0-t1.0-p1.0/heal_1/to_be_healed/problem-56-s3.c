#include <stdio.h>
#include <stdlib.h>

int reverse_number(int num) {
    int rev = 0;
    while (num > 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 972649942 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:258,execs:126,op:havoc,rep:3)
         */
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return rev;
}

int is_one_less_than_twice_reverse(int number) {
    int reversed = reverse_number(number);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1795818402 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:4104,execs:1741,op:havoc,rep:7)
     * UBSan: signed integer overflow: 2 * 1136564829 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:258,execs:126,op:havoc,rep:3)
     */
    return number == 2 * reversed - 1;
}

int main() {
    int test_number;
    printf("Enter a number: ");
    if (scanf("%d", &test_number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_one_less_than_twice_reverse(test_number)) {
        printf("The number is one less than twice its reverse.\n");
    } else {
        printf("The number is not one less than twice its reverse.\n");
    }

    return EXIT_SUCCESS;
}