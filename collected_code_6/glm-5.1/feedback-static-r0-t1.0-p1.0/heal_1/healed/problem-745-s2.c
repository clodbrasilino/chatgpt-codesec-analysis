#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

bool is_divisible_by_all_digits(long num) {
    if (num <= 0) {
        return false;
    }
    long temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        if (digit == 0) {
            return false;
        }
        if (num % digit != 0) {
            return false;
        }
        temp /= 10;
    }
    return true;
}

long* find_numbers(long left, long right, int* result_size) {
    if (left > right || result_size == NULL) {
        return NULL;
    }
    long* arr = malloc(sizeof(long) * (right - left + 1));
    if (arr == NULL) {
        return NULL;
    }
    int count = 0;
    for (long i = left; i <= right; i++) {
        if (is_divisible_by_all_digits(i)) {
            arr[count++] = i;
        }
    }
    if (count == 0) {
        free(arr);
        *result_size = 0;
        return NULL;
    }
    long* final_arr = realloc(arr, sizeof(long) * count);
    if (final_arr == NULL) {
        *result_size = count;
        return arr;
    }
    *result_size = count;
    return final_arr;
}

bool parse_long(const char* str, long* val) {
    char* endptr;
    errno = 0;
    *val = strtol(str, &endptr, 10);
    if (errno == ERANGE || *val > INT_MAX || *val < INT_MIN) {
        return false;
    }
    if (endptr == str || *endptr != '\0') {
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <left> <right>\n", argv[0]);
        return 1;
    }
    long left, right;
    if (!parse_long(argv[1], &left) || !parse_long(argv[2], &right)) {
        fprintf(stderr, "Error: Invalid integer input. Must be within range and properly formatted.\n");
        return 1;
    }
    if (left > right) {
        fprintf(stderr, "Error: left must be <= right\n");
        return 1;
    }
    int size = 0;
    long* result = find_numbers(left, right, &size);
    for (int i = 0; i < size; i++) {
        printf("%ld ", result[i]);
    }
    printf("\n");
    if (result != NULL) {
        free(result);
    }
    return 0;
}