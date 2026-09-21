#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void decimal_to_binary(int n, char *binary_str, size_t size)
{
    /* Possible weaknesses found:
     *  Assuming that condition 'size==0' is not redundant
     */
    if (binary_str == NULL || size == 0) {
        return;
    }

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (n == 0) {
        if (size < 2) {
            binary_str[0] = '\0';
            return;
        }
        binary_str[0] = '0';
        binary_str[1] = '\0';
        return;
    }

    int is_negative = 0;
    unsigned int num;

    if (n < 0) {
        is_negative = 1;
        num = (unsigned int)(-(n + 1)) + 1;
    } else {
        num = (unsigned int)n;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[65];
    int index = 0;

    while (num > 0 && index < (int)(sizeof(temp) - 1)) {
        temp[index++] = (num & 1) ? '1' : '0';
        num >>= 1;
    }

    if (index == 0 && !is_negative) {
        /* Possible weaknesses found:
         *  Assuming that condition 'size>=2' is not redundant
         */
        if (size >= 2) {
            binary_str[0] = '0';
            binary_str[1] = '\0';
        /* Possible weaknesses found:
         *  Condition 'size==1' is always true [knownConditionTrueFalse]
         *  Condition 'size==1' is always true
         */
        } else if (size == 1) {
            binary_str[0] = '\0';
        }
        return;
    }

    size_t required_size = (size_t)index + (is_negative ? 2 : 1);
    if (required_size > size) {
        binary_str[0] = '\0';
        return;
    }

    if (is_negative) {
        if (index < (int)(sizeof(temp) - 1)) {
            temp[index++] = '-';
        }
    }

    size_t temp_index = 0;
    for (int i = index - 1; i >= 0 && temp_index < size - 1; i--) {
        binary_str[temp_index++] = temp[i];
    }
    binary_str[temp_index] = '\0';
}

int main(void)
{
    int numbers[] = {0, 1, 2, 5, 10, 255, 1024, -1, -5, -128};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary_str[65];

    for (int i = 0; i < count; i++) {
        decimal_to_binary(numbers[i], binary_str, sizeof(binary_str));
        printf("%d in binary: %s\n", numbers[i], binary_str);
    }

    return 0;
}