#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

char* find_next_smallest_palindrome(const char* num_str) {
    size_t len = strnlen(num_str, SIZE_MAX);
    if (len == 0) {
        char* res = malloc(2);
        if (!res) return NULL;
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    for (size_t i = 0; i < len; i++) {
        if (num_str[i] < '0' || num_str[i] > '9') return NULL;
    }

    char* result = malloc(len + 2);
    if (!result) return NULL;

    bool all_nines = true;
    for (size_t i = 0; i < len; i++) {
        if (num_str[i] != '9') {
            all_nines = false;
            break;
        }
    }

    if (all_nines) {
        result[0] = '1';
        for (size_t i = 1; i < len; i++) result[i] = '0';
        result[len] = '1';
        result[len + 1] = '\0';
        return result;
    }

    memcpy(result, num_str, len + 1);
    size_t left = 0;
    size_t right = len - 1;

    while (left < right) {
        if (result[left] < result[right]) {
            result[right] = result[left];
            size_t i = right - 1;
            while (i >= 0 && result[i] == '9') {
                result[i] = '0';
                if (i == 0) break;
                i--;
            }
            if (result[i] == '9' && i == 0) {
                result[i] = '0';
            } else {
                result[i]++;
            }
        } else {
            result[right] = result[left];
        }
        left++;
        right--;
    }

    return result;
}

int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char* palindrome = find_next_smallest_palindrome(argv[1]);
    if (!palindrome) {
        fprintf(stderr, "Invalid input or memory allocation failed.\n");
        return 1;
    }

    printf("%s\n", palindrome);
    free(palindrome);
    palindrome = NULL;

    return 0;
}