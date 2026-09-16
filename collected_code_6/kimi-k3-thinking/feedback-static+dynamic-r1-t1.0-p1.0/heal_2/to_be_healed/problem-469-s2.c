#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int imax(int a, int b)
{
    return (a > b) ? a : b;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 0 failed: expected 10, got <no output>
  */

int maxProfit(int k, const int *prices, int pricesSize)
{
    if (prices == NULL || pricesSize < 2 || k < 1)
    {
        return 0;
    }

    if (k >= pricesSize / 2)
    {
        int profit = 0;
        for (int i = 1; i < pricesSize; i++)
        {
            int diff = prices[i] - prices[i - 1];
            if (diff > 0)
            {
                profit += diff;
            }
        }
        return profit;
    }

    int *buy = (int *)malloc(((size_t)k + 1u) * sizeof(int));
    if (buy == NULL)
    {
        return -1;
    }

    int *sell = (int *)malloc(((size_t)k + 1u) * sizeof(int));
    if (sell == NULL)
    {
        free(buy);
        buy = NULL;
        return -1;
    }

    for (int j = 0; j <= k; j++)
    {
        buy[j] = INT_MIN;
        sell[j] = 0;
    }

    for (int i = 0; i < pricesSize; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            buy[j] = imax(buy[j], sell[j - 1] - prices[i]);
            sell[j] = imax(sell[j], buy[j] + prices[i]);
        }
    }

    int result = sell[k];

    free(buy);
    buy = NULL;
    free(sell);
    sell = NULL;

    return result;
}

int main(void)
{
    int k = 0;
    int n = 0;

    if (scanf("%d %d", &k, &n) != 2)
    {
        return EXIT_FAILURE;
    }

    if (k < 0 || n < 0)
    {
        return EXIT_FAILURE;
    }

    int *prices = NULL;
    if (n > 0)
    {
        prices = (int *)malloc((size_t)n * sizeof(int));
        if (prices == NULL)
        {
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &prices[i]) != 1)
        {
            free(prices);
            prices = NULL;
            return EXIT_FAILURE;
        }
    }

    int profit = maxProfit(k, prices, n);
    if (profit < 0)
    {
        free(prices);
        prices = NULL;
        return EXIT_FAILURE;
    }

    printf("%d\n", profit);

    free(prices);
    prices = NULL;

    return EXIT_SUCCESS;
}