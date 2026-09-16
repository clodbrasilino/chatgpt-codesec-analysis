#include <stdio.h>
#include <stdint.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
uint64_t arrayMultiplicationModulo(uint64_t *arr, size_t len, uint64_t n) {
    uint64_t result = 1;
    for (size_t i = 0; i < len; ++i) {
        result = (result * (arr[i] % n)) % n;
    }
    return result;
}

int main() {
    uint64_t arr[] = {10, 20, 30, 40};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    uint64_t n = 11;
    uint64_t result = arrayMultiplicationModulo(arr, len, n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("The remainder of the multiplication modulo %llu is: %llu\n", n, result);
    return 0;
}