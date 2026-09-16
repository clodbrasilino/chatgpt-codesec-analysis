#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool check_decimal_precision(double value, double expected)
{
    double scaled_value;
    double scaled_expected;
    double difference;

    if (!isfinite(value) || !isfinite(expected))
    {
        return false;
    }

    scaled_value = round(value * 100.0) / 100.0;
    scaled_expected = round(expected * 100.0) / 100.0;
    difference = fabs(scaled_value - scaled_expected);

    return difference < 0.005;
}

int main(void)
{
    double value;
    double expected;
    int scan_result;

    printf("Enter a decimal value: ");
    scan_result = scanf("%lf", &value);
    if (scan_result != 1)
    {
        fprintf(stderr, "Invalid input for decimal value.\n");
        return 1;
    }

    printf("Enter expected value: ");
    scan_result = scanf("%lf", &expected);
    if (scan_result != 1)
    {
        fprintf(stderr, "Invalid input for expected value.\n");
        return 1;
    }

    if (check_decimal_precision(value, expected))
    {
        printf("Values match with precision of 2 decimal places.\n");
    }
    else
    {
        printf("Values do not match with precision of 2 decimal places.\n");
    }

    return 0;
}