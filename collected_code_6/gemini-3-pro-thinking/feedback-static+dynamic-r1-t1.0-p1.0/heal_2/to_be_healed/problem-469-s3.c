/* Possible weaknesses found:
 *  stray '`' in program
 *  subscripted value is neither array nor pointer nor vector
 *  expected ')' before 't'
 *  type defaults to 'int' in declaration of 'profit' [-Wimplicit-int]
 *  called object is not a function or function pointer
 *  'from' undeclared here (not in a function)
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  subscripted value is not an array, pointer, or vector
 */
profit = profit[4] = 4` (from `t=1`).
/* Possible weaknesses found:
 *  subscripted value is neither array nor pointer nor vector
 *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
 *  stray '`' in program
 *  'max_diff' undeclared here (not in a function)
 */
`profit[4] = max(profit[3], 0 + max_diff)`.
/* Possible weaknesses found:
 *  expected ';' after top level declarator
 *  expected ',' or ';' before 'i'
 *  expected identifier or '('
 *  stray '`' in program
 */
At `i=3`, `profit[3] = 4`.
/* Possible weaknesses found:
 *  stray '`' in program
 */
`max_diff` from `i=3` was `max(-2, 4 - 5) = -1`.
/* Possible weaknesses found:
 *  stray '`' in program
 */
So `profit[4] = max(4, 0 + (-1)) = 4`.
/* Possible weaknesses found:
 *  stray '`' in program
 */
Then `max_diff` at `i=4` becomes `max(max_diff, prev_profit - prices[4])`.
/* Possible weaknesses found:
 *  stray '`' in program
 */
`prev_profit` is 4. `prices[4]` is 0.
/* Possible weaknesses found:
 *  stray '`' in program
 */
So `max_diff = max(-1, 4 - 0) = 4`.
/* Possible weaknesses found:
 *  stray '`' in program
 */
Then at `i=5`, `prices[5] = 3`.
/* Possible weaknesses found:
 *  stray '`' in program
 */
`profit[5] = max(profit[4], 3 + max_diff) = max(4, 3 + 4) = 7`.
Yes! My trace was correct. The code DOES give 7.

/* Possible weaknesses found:
 *  stray '`' in program
 */
So why does the comment say `test case 1 failed: expected 7, got 0`?
Could it be that the code is NOT exactly as I am reading it?
/* Possible weaknesses found:
 *  expected identifier or '('
 *  stray '`' in program
 */
Look at `int max(int a, int b) { return (a > b) ? a : b; }`
/* Possible weaknesses found:
 *  too many decimal points in number
 *  stray '`' in program
 *  expected '=', ',', ';', 'asm' or '__attribute__' before '!' token
 */
Wait! Is it possible that the compiler is not C99 and `for (int i = 1...)` is failing? No, the code compiles if it says "got 0".
Could it be a global state issue? No global variables.
/* Possible weaknesses found:
 *  expected identifier or '('
 *  unknown type name 'is'
 *  stray '`' in program
 *  expected '=', ',', ';', 'asm' or '__attribute__' before '.' token
 */
Is there undefined behavior? `int prev_profit = profit[i];` is fine. `profit` is size `n`.

What if LeetCode problem requires alternating transactions and the DP does not do it?
No, the problem is literally "Best Time to Buy and Sell Stock IV" and this DP is the standard solution.

/* Possible weaknesses found:
 *  stray '`' in program
 */
Wait! What if `k` is passed as an array? No.
/* Possible weaknesses found:
 *  missing terminating ' character
 *  No pair for character ('). Can't process file. File is either invalid or unicode, which is currently not supported. [syntaxError]
 */
Let's reconsider test case 0: expected 10, got 5.
When would we expect 10 but get 5?
/* Possible weaknesses found:
 *  stray '`' in program
 */
If `k=1`, and we return 5, but `k=2` expects 10.
/* Possible weaknesses found:
 *  stray '`' in program
 */
If the code ignores `k` and just does `t=1`?
/* Possible weaknesses found:
 *  expected identifier or '(' before '++' token
 *  stray '`' in program
 *  expected '=', ',', ';', 'asm' or '__attribute__' before '<=' token
 */
But the code has `for (int t = 1; t <= k; ++t)`.

/* Possible weaknesses found:
 *  stray '`' in program
 */
What if `profit` is re-declared? No.
/* Possible weaknesses found:
 *  stray '`' in program
 */
What if `prices` contains negative values? Stock prices are generally `>= 0`.
/* Possible weaknesses found:
 *  stray '`' in program
 */
Wait, if `profit` array is `calloc`ed, `profit[i]` is initialized to 0.
/* Possible weaknesses found:
 *  stray '`' in program
 */
Is it possible that `profit` array size is too small? `sizeof(int) * n`. Correct.

/* Possible weaknesses found:
 *  stray '`' in program
 */
Wait! Let me look at the `main` function provided.
/* Possible weaknesses found:
 *  stray '`' in program
 */
`int profit = max_profit(k, prices, n