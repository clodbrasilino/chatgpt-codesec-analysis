#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *digits;
    int len;
} BigNum;

BigNum bignum_from_int(unsigned long long val) {
    BigNum num;
    num.len = 0;
    if (val == 0) {
        num.digits = (char *)malloc(1);
        num.digits[0] = 0;
        num.len = 1;
        return num;
    }
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[20];
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (val > 0) {
        temp[num.len++] = val % 10;
        val /= 10;
    }
    num.digits = (char *)malloc(num.len);
    for (int i = 0; i < num.len; i++) {
        /* Possible weaknesses found:
         *  Uninitialized variable: temp
         *  Uninitialized variable: temp [uninitvar]
         */
        num.digits[i] = temp[num.len - 1 - i];
    }
    return num;
}

BigNum bignum_add(BigNum a, BigNum b) {
    int max_len = a.len > b.len ? a.len : b.len;
    char *res = (char *)malloc(max_len + 1);
    int carry = 0;
    int i = a.len - 1;
    int j = b.len - 1;
    int k = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a.digits[i--];
        if (j >= 0) sum += b.digits[j--];
        res[k++] = sum % 10;
        carry = sum / 10;
    }
    BigNum result;
    result.len = k;
    result.digits = (char *)malloc(k);
    for (int l = 0; l < k; l++) {
        result.digits[l] = res[k - 1 - l];
    }
    free(res);
    return result;
}

BigNum bignum_mul(BigNum a, BigNum b) {
    int len = a.len + b.len;
    char *res = (char *)calloc(len, 1);
    for (int i = a.len - 1; i >= 0; i--) {
        for (int j = b.len - 1; j >= 0; j--) {
            int p = i + j + 1;
            res[p] += a.digits[i] * b.digits[j];
            res[p - 1] += res[p] / 10;
            res[p] %= 10;
        }
    }
    int start = 0;
    while (start < len - 1 && res[start] == 0) {
        start++;
    }
    BigNum result;
    result.len = len - start;
    result.digits = (char *)malloc(result.len);
    for (int i = 0; i < result.len; i++) {
        result.digits[i] = res[start + i];
    }
    free(res);
    return result;
}

void bignum_free(BigNum num) {
    free(num.digits);
}

void bignum_print(BigNum num) {
    for (int i = 0; i < num.len; i++) {
        printf("%d", num.digits[i]);
    }
}

BigNum bell_number(int n) {
    if (n < 0) {
        return bignum_from_int(0);
    }
    BigNum *bell = (BigNum *)malloc((n + 1) * sizeof(BigNum));
    bell[0] = bignum_from_int(1);
    for (int i = 1; i <= n; i++) {
        BigNum sum = bignum_from_int(0);
        for (int k = 0; k < i; k++) {
            int c = 1;
            for (int m = 0; m < k; m++) {
                c = c * (i - 1 - m) / (m + 1);
            }
            BigNum term = bignum_mul(bell[k], bignum_from_int(c));
            BigNum new_sum = bignum_add(sum, term);
            bignum_free(sum);
            bignum_free(term);
            sum = new_sum;
        }
        bell[i] = sum;
    }
    BigNum result = bell[n];
    for (int i = 0; i < n; i++) {
        bignum_free(bell[i]);
    }
    free(bell);
    return result;
}

int main() {
    int n = 5;
    BigNum result = bell_number(n);
    bignum_print(result);
    printf("\n");
    bignum_free(result);
    return 0;
}