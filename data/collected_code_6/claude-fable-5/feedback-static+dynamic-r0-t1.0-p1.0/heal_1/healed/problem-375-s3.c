#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned long long_abs(long value)
{
    if (value < 0) {
        return (unsigned long)(-(value + 1)) + 1UL;
    }
    return (unsigned long)value;
}

long round_to_nearest_multiple(long number, long multiple, int *error)
{
    if (multiple == 0) {
        *error = 1;
        return 0;
    }

    *error = 0;

    unsigned long abs_multiple = long_abs(multiple);
    unsigned long abs_number = long_abs(number);
    unsigned long remainder = abs_number % abs_multiple;

    if (remainder == 0) {
        return number;
    }

    unsigned long toward_zero = abs_number - remainder;
    unsigned long away_from_zero = toward_zero + abs_multiple;
    unsigned long dist_toward = remainder;
    unsigned long dist_away = abs_multiple - remainder;
    unsigned long result_mag;

    if (number < 0) {
        if (dist_away < dist_toward) {
            result_mag = away_from_zero;
        } else {
            result_mag = toward_zero;
        }

        if (result_mag > (unsigned long)LONG_MAX + 1UL) {