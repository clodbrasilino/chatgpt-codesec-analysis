#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_decimal_with_precision_2(const char *str) {
    char *endptr;
    long double number = strtold(str, &endptr);

    if (endptr == str || *endptr != '\0') return 0;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2Lf", number);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp_buffer[50];
    snprintf(temp_buffer, sizeof(temp_buffer), "%.20Lf", number);

    /* Possible weaknesses found:
     *  Variable 'parsed_number' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'parsed_number' during its initialization is never read [deadcode.DeadStores]
     */
    long double parsed_number = strtold(buffer, &endptr);

    return strcmp(buffer, str) == 0 && (strcmp(temp_buffer, str) == 0);
}

int main() {
    const char *test1 = "123.45";
    const char *test2 = "123.456";

    int result1 = is_decimal_with_precision_2(test1);
    int result2 = is_decimal_with_precision_2(test2);

    printf("%s: %s\n", test1, result1 ? "Valid" : "Invalid");
    printf("%s: %s\n", test2, result2 ? "Valid" : "Invalid");

    return 0;
}