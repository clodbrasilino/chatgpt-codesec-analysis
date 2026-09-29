#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

int64_t reverseNumber(int num) {
    int64_t reversed = 0;
    while (num != 0) {
        if (reversed > INT32_MAX / 10 || (reversed == INT32_MAX / 10 && num % 10 > 7)) {
            return 0;
        }
        if (reversed < INT32_MIN / 10 || (reversed == INT32_MIN / 10 && num % 10 < -8)) {
            return 0;
        }
        reversed = (reversed * 10) + (num % 10);
        num /= 10;
    }
    return reversed;
}

bool checkCondition(int64_t num) {
    int64_t reversed = reverseNumber(num);
    if (reversed == 0) {
        return false;
    }
    if (reversed > INT32_MAX / 2 || (2 * reversed - 1) != num) {
        return false;
    }
    return true;
}

int main() {
    int64_t number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    scanf("%lld", &number);

    if (checkCondition(number)) {
        printf("The number is one less than twice its reverse.\n");
    } else {
        printf("The number is not one less than twice its reverse.\n");
    }

    return 0;
}