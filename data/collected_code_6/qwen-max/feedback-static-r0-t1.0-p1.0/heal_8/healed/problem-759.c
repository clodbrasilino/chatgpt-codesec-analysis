#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_decimal_with_precision_2(const char *str) {
    char *endptr;
    long double number = strtold(str, &endptr);

    if (endptr == str || *endptr != '\0') return 0;

    char *buffer = malloc(50 * sizeof(char));
    if (!buffer) return -1;
    snprintf(buffer, 50, "%.2Lf", number);

    char *temp_buffer = malloc(50 * sizeof(char));
    if (!temp_buffer) {
        free(buffer);
        return -1;
    }
    snprintf(temp_buffer, 50, "%.20Lf", number);

    int result = strcmp(buffer, str) == 0 && (strcmp(temp_buffer, str) == 0);

    free(buffer);
    free(temp_buffer);

    return result;
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