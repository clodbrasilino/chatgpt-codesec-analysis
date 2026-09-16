#include <stdio.h>
#include <stdlib.h>

int maxProfit(int k, const int *prices, int n)
{
    int i;
    int j;
    int *buy;
    int *sell;
    int result;

    if (k <= 0 || prices == NULL || n <= 1)
    {
        return 0;
    }

    if (k >= n / 2)
    {
        int profit = 0;

        for (i = 1; i < n; ++i)
        {
            int diff = prices[i] - prices[i - 1];

            if (diff > 0)
            {
                profit += diff;
            }
        }

        return profit;
    }

    buy = (int *)malloc(((size_t)k + 1U) * sizeof(int));
    sell = (int *)malloc(((size_t)k + 1U) * sizeof(int));

    if (buy == NULL || sell == NULL)
    {
        free(buy);
        free(sell);
        return -1;
    }

    for (j = 0; j <= k; ++j)
    {
        buy[j] = -prices[0];
        sell[j] = 0;
    }

    for (i = 1; i < n; ++i)
    {
        for (j = 1; j <= k; ++j)
        {
            int buyCandidate = sell[j - 1] - prices[i];
            int sellCandidate;

            if (buyCandidate > buy[j])
            {
                buy[j] = buyCandidate;
            }

            sellCandidate = buy[j] + prices[i];

            if (sellCandidate > sell[j])
            {
                sell[j] = sellCandidate;
            }
        }
    }

    result = sell[k];

    free(buy);
    free(sell);

    return result;
}

int main(void)
{
    int k;
    int n;
    int *prices;
    int result;

    if (scanf("%d", &k) != 1 || k < 0)
    {
        fprintf(stderr, "Error: invalid number of transactions.\n");
        return EXIT_FAILURE;
    }

    if (scanf("%d", &n) != 1 || n < 0)
    {
        fprintf(stderr, "Error: invalid number of prices.\n");
        return EXIT_FAILURE;
    }

    prices = NULL;

    if (n > 0)
    {
        int i;

        prices = (int *)malloc((size_t)n * sizeof(int));

        if (prices == NULL)
        {
            fprintf(stderr, "Error: memory allocation failed.\n");
            return EXIT_FAILURE;
        }

        for (i = 0; i < n; ++i)
        {
            if (scanf("%d", &prices[i]) != 1 || prices[i] < 0)
            {
                fprintf(stderr, "Error: invalid price value.\n");
                free(prices);
                return EXIT_FAILURE;
            }
        }
    }

    result = maxProfit(k, prices, n);

    free(prices);
    prices = NULL;

    if (result < 0)
    {
        fprintf(stderr, "Error: profit computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}