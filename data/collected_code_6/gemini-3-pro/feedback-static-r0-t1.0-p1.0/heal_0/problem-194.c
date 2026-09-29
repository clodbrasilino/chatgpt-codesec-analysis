#include <stdio.h>
#include <limits.h>

int octal_to_decimal(const char *octal_str, long long *result);

int main(void) {
    long long decimal_value = 0;
    
    if (octal_to_decimal("745", &decimal_value) == 0) {
        printf("%lld\n", decimal_value);
    } else {
        printf("Error\n");
    }
    
    if (octal_to_decimal("82", &decimal_value) == 0) {
        printf("%lld\n", decimal_value);
    } else {
        printf("Error\n");
    }

    if (octal_to_decimal(NULL, &decimal_value) == 0) {
        printf("%lld\n", decimal_value);
    } else {
        printf("Error\n");
    }
    
    return 0;
}

int octal_to_decimal(const char *octal_str, long long *result) {
    long long current_val = 0;
    int i = 0;

    if (octal_str == NULL || result == NULL || octal_str[0] == '\0') {
        return -1;
    }

    while (octal_str[i] != '\0') {
        if (octal_str[i] < '0' || octal_str[i] > '7') {
            return -1;
        }

        if (current_val > (LLONG_MAX - (octal_str[i] - '0')) / 8) {
            return -1;
        }

        current_val = (current_val * 8) + (octal_str[i] - '0');
        i++;
    }

    *result = current_val;
    return 0;
}