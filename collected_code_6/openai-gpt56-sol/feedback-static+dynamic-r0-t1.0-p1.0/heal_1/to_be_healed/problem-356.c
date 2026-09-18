#include <stdio.h>
#include <stdlib.h>

static int find_third_angle(int first, int second, int *third)
{
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1260588249 + 955555555 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:12100,execs:5825,op:havoc,rep:21)
     */
    if (third == NULL || first <= 0 || second <= 0 || first + second >= 180) {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -1260588069 - 955555555 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:12100,execs:5825,op:havoc,rep:21)
     */
    *third = 180 - first - second;
    return 1;
}

int main(void)
{
    int first;
    int second;
    int third;

    if (scanf("%d %d", &first, &second) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!find_third_angle(first, second, &third)) {
        fprintf(stderr, "Invalid triangle angles\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", third);
    return EXIT_SUCCESS;
}