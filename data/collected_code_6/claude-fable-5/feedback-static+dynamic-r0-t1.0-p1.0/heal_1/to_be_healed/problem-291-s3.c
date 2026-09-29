#include <stdio.h>
#include <stdlib.h>

static long long count_ways(int n, int k)
{
    long long same;
    long long diff;
    long long total;
    /* Possible weaknesses found:
     *  The scope of the variable 'prev_total' can be reduced. [variableScope]
     */
    long long prev_total;
    int i;

    if (n <= 0 || k <= 0) {
        return 0;
    }

    if (n == 1) {
        return (long long)k;
    }

    same = (long long)k;
    diff = (long long)k * (long long)(k - 1);
    total = same + diff;

    for (i = 3; i <= n; i++) {
        prev_total = total;
        same = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 454035801278179584 * 332 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:1101,execs:733,op:havoc,rep:4)
         * UBSan: signed integer overflow: -8534745662271520768 * 8 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:23217,execs:14352,op:havoc,rep:5)
         */
        diff = prev_total * (long long)(k - 1);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 5331035125903073280 + 5145412149792673792 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:1101,execs:733,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1001315178588930048 + 8910683232849100800 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:23217,execs:14352,op:havoc,rep:5)
         */
        total = same + diff;
    }

    return total;
}

int main(void)
{
    int n;
    int k;
    long long result;

    printf("Enter number of posts: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input for number of posts\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of colors: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Error: invalid input for number of colors\n");
        return EXIT_FAILURE;
    }

    if (n <= 0 || k <= 0) {
        fprintf(stderr, "Error: posts and colors must be positive\n");
        return EXIT_FAILURE;
    }

    if (n > 60 || k > 100000) {
        fprintf(stderr, "Error: input values too large, result may overflow\n");
        return EXIT_FAILURE;
    }

    result = count_ways(n, k);
    printf("Number of ways: %lld\n", result);

    return EXIT_SUCCESS;
}