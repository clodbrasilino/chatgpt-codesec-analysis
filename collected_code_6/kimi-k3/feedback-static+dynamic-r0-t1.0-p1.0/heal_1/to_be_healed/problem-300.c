#include <stdio.h>
#include <stdlib.h>

long long count_binary_sequences(int n)
{
    if (n <= 0)
    {
        return 0;
    }

    int len = n + 1;
    long long *prev = (long long *)calloc((size_t)len, sizeof(long long));
    long long *curr = (long long *)calloc((size_t)len, sizeof(long long));

    if (prev == NULL || curr == NULL)
    {
        free(prev);
        free(curr);
        return -1;
    }

    prev[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            curr[j] = prev[j];
            if (j > 0)
            {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 5516694892996182896 + 4472995859186094240 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:953,execs:304,op:havoc,rep:11)
                 */
                curr[j] += prev[j - 1];
            }
        }

        for (int j = i + 1; j <= n; j++)
        {
            curr[j] = 0;
        }

        long long *temp = prev;
        prev = curr;
        curr = temp;
    }

    long long result = 0;

    for (int k = 0; k <= n; k++)
    {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 33963647355 * 33963647355 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:953,execs:304,op:havoc,rep:11)
         * UBSan: signed integer overflow: 6358402050 * 6358402050 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:8321,execs:415,op:havoc,rep:6)
         * UBSan: signed integer overflow: 6646215757681299270 + 4857445984927644900 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:43477,execs:1029,op:havoc,rep:15)
         * UBSan: signed integer overflow: -1092909427850234422 + -9007751406077477071 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:953,execs:304,op:havoc,rep:11)
         * UBSan: signed integer overflow: 5060288580294794640 + 6933266088399950564 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:8321,execs:415,op:havoc,rep:6)
         */
        result += prev[k] * prev[k];
    }

    free(prev);
    free(curr);

    return result;
}

int main(void)
{
    int n;

    if (scanf("%d", &n) != 1)
    {
        return 1;
    }

    long long result = count_binary_sequences(n);

    if (result < 0)
    {
        return 1;
    }

    printf("%lld\n", result);

    return 0;
}