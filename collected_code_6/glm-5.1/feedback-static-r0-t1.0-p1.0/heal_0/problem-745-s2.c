#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_divisible_by_all_digits(int num) {
    if (num <= 0) {
        return false;
    }
    int temp = num;
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

int* find_numbers(int left, int right, int* result_size) {
    if (left > right || result_size == NULL) {
        return NULL;
    }
    int* arr = malloc(sizeof(int) * (right - left + 1));
    if (arr == NULL) {
        return NULL;
    }
    int count = 0;
    for (int i = left; i <= right; i++) {
        if (is_divisible_by_all_digits(i)) {
            arr[count++] = i;
        }
    }
    if (count == 0) {
        free(arr);
        *result_size = 0;
        return NULL;
    }
    int* final_arr = realloc(arr, sizeof(int) * count);
    if (final_arr == NULL) {
        *result_size = count;
        return arr;
    }
    *result_size = count;
    return final_arr;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <left> <right>\n", argv[0]);
        return 1;
    }
    int left = atoi(argv[1]);
    int right = atoi(argv[2]);
    if (left > right) {
        fprintf(stderr, "Error: left must be <= right\n");
        return 1;
    }
    int size = 0;
    int* result = find_numbers(left, right, &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    if (result != NULL) {
        free(result);
    }
    return 0;
}