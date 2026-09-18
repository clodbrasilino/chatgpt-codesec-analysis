#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

bool is_prime(uint64_t n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

uint64_t nsw_prime(unsigned int n) {
    if (n == 0) return 0;
    uint64_t a = 1;
    uint64_t b = 1;
    /* Possible weaknesses found:
     *  Assignment 'count=0', assigned value is 0
     */
    unsigned int count = 0;
    uint64_t candidate = 1;
    /* Possible weaknesses found:
     *  Calling function 'is_prime' returns 0
     *  Condition 'is_prime(1)' is always false [knownConditionTrueFalse]
     *  Condition 'is_prime(1)' is always false
     */
    if (is_prime(1)) {
        count++;
        if (count == n) return 1;
    }
    if (n == 1) {
        /* Possible weaknesses found:
         *  Calling function 'is_prime' returns 0
         *  Condition 'is_prime(1)' is always false [knownConditionTrueFalse]
         *  Condition 'is_prime(1)' is always false
         */
        if (is_prime(1)) return 1;
        /* Possible weaknesses found:
         *  b is assigned
         *  Value stored to 'b' is never read [deadcode.DeadStores]
         */
        b = 1;
        /* Possible weaknesses found:
         *  Value stored to 'a' is never read [deadcode.DeadStores]
         *  a is assigned
         */
        a = 1;
        count = 0;
        /* Possible weaknesses found:
         *  Value stored to 'candidate' is never read [deadcode.DeadStores]
         *  candidate is assigned
         */
        candidate = 1;
    }
    /* Possible weaknesses found:
     *  Calling function 'is_prime' returns 0
     *  count is assigned
     *  Condition 'is_prime(1)' is always false [knownConditionTrueFalse]
     *  Condition 'count==0' is always true
     *  Value stored to 'count' is never read [deadcode.DeadStores]
     *  Condition 'is_prime(1)' is always false
     *  Condition 'count==0' is always true [knownConditionTrueFalse]
     */
    if (count == 0 && is_prime(1)) count = 1;
    /* Possible weaknesses found:
     *  Calling function 'is_prime' returns 0
     *  Condition 'is_prime(1)' is always false [knownConditionTrueFalse]
     *  Condition 'is_prime(1)' is always false
     */
    if (n == 1 && is_prime(1)) return 1;
    /* Possible weaknesses found:
     *  a is overwritten
     *  Variable 'a' is reassigned a value before the old one has been used. [redundantAssignment]
     */
    a = 1;
    /* Possible weaknesses found:
     *  b is overwritten
     *  Variable 'b' is reassigned a value before the old one has been used. [redundantAssignment]
     */
    b = 1;
    /* Possible weaknesses found:
     *  count is overwritten
     *  Variable 'count' is reassigned a value before the old one has been used. [redundantAssignment]
     */
    count = 0;
    /* Possible weaknesses found:
     *  candidate is overwritten
     *  Variable 'candidate' is reassigned a value before the old one has been used. [redundantAssignment]
     */
    candidate = 1;
    /* Possible weaknesses found:
     *  Calling function 'is_prime' returns 0
     *  Condition 'is_prime(1)' is always false [knownConditionTrueFalse]
     *  Condition 'is_prime(1)' is always false
     */
    if (is_prime(1)) {
        count = 1;
        candidate = 1;
    }
    while (count < n) {
        if (b > UINT64_MAX / 2) break;
        uint64_t next = 2 * b + a;
        if (next < b) break;
        a = b;
        b = next;
        if (is_prime(next)) {
            count++;
            candidate = next;
        }
    }
    return candidate;
}

int main(void) {
    unsigned int n;
    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%" PRIu64 "\n", nsw_prime(n));
    return EXIT_SUCCESS;
}