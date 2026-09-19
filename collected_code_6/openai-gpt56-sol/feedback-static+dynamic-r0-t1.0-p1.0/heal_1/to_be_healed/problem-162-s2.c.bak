#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_positive_sequence(int64_t n, int64_t *result)
{
    if (result == NULL || n <= 0) {
        return -1;
    }

    int64_t terms = (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3333333333333 * 3333333333334 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:572,execs:298,op:havoc,rep:4)
     * UBSan: signed integer overflow: 3000000000000003 * 3000000000000004 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000004,time:13208,execs:6796,op:havoc,rep:2)
     * UBSan: signed integer overflow: 333333333333333 * 333333333333334 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000004,time:16130,execs:8241,op:havoc,rep:2)
     * UBSan: signed integer overflow: 33333333333 * 33333333334 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000005,sig:06,src:000009,time:28150,execs:14247,op:havoc,rep:1)
     * UBSan: signed integer overflow: 333333333233 * 333333333234 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000011,time:27254,execs:13826,op:havoc,rep:5)
     * UBSan: signed integer overflow: 333333333333 * 333333333334 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000006,sig:06,src:000008,time:31315,execs:15741,op:havoc,rep:2)
     */
    *result = terms * (n - terms + 1);
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000010,time:26934,execs:13672,op:havoc,rep:1; likely memory-safety defect
  */

int main(void)
{
    char input[128];
    char *end = NULL;
    int64_t n;
    int64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || sum_positive_sequence(n, &sum) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}