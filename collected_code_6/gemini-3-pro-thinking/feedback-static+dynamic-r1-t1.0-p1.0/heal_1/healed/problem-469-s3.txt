profit = profit[4] = 4` (from `t=1`).
`profit[4] = max(profit[3], 0 + max_diff)`.
At `i=3`, `profit[3] = 4`.
`max_diff` from `i=3` was `max(-2, 4 - 5) = -1`.
So `profit[4] = max(4, 0 + (-1)) = 4`.
Then `max_diff` at `i=4` becomes `max(max_diff, prev_profit - prices[4])`.
`prev_profit` is 4. `prices[4]` is 0.
So `max_diff = max(-1, 4 - 0) = 4`.
Then at `i=5`, `prices[5] = 3`.
`profit[5] = max(profit[4], 3 + max_diff) = max(4, 3 + 4) = 7`.
Yes! My trace was correct. The code DOES give 7.

So why does the comment say `test case 1 failed: expected 7, got 0`?
Could it be that the code is NOT exactly as I am reading it?
Look at `int max(int a, int b) { return (a > b) ? a : b; }`
Wait! Is it possible that the compiler is not C99 and `for (int i = 1...)` is failing? No, the code compiles if it says "got 0".
Could it be a global state issue? No global variables.
Is there undefined behavior? `int prev_profit = profit[i];` is fine. `profit` is size `n`.

What if LeetCode problem requires alternating transactions and the DP does not do it?
No, the problem is literally "Best Time to Buy and Sell Stock IV" and this DP is the standard solution.

Wait! What if `k` is passed as an array? No.
Let's reconsider test case 0: expected 10, got 5.
When would we expect 10 but get 5?
If `k=1`, and we return 5, but `k=2` expects 10.
If the code ignores `k` and just does `t=1`?
But the code has `for (int t = 1; t <= k; ++t)`.

What if `profit` is re-declared? No.
What if `prices` contains negative values? Stock prices are generally `>= 0`.
Wait, if `profit` array is `calloc`ed, `profit[i]` is initialized to 0.
Is it possible that `profit` array size is too small? `sizeof(int) * n`. Correct.

Wait! Let me look at the `main` function provided.
`int profit = max_profit(k, prices, n