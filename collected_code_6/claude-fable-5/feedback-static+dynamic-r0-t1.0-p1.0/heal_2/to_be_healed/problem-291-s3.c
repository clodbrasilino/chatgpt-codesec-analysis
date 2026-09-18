#include <stdio.h>
#include <stdlib.h>

static long long count_ways(int n, int k)
{
    long long same;
    long long diff;
    long long total;
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
        long long prev_total = total;
        same = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9206884065845671936 * 52 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:14562,execs:8794,op:havoc,rep:2)
         * UBSan: signed integer overflow: 494029538344547392 * 22 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:3228,execs:2133,op:havoc,rep:3)
         */
        diff = prev_total * (long long)(k - 1);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -7578094230129508992 + -8729119997554879872 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:3228,execs:2133,op:havoc,rep:3)
         * UBSan: signed integer overflow: 171167238135256064 + 9068692769728623616 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:14562,execs:8794,op:havoc,rep:2)
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