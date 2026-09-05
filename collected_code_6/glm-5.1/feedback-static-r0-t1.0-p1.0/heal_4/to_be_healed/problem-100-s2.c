#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* find_next_smallest_palindrome(const char* num_str) {
    int len = strlen(num_str);
    if (len == 0) {
        char* res = malloc(2);
        if (!res) return NULL;
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    for (int i = 0; i < len; i++) {
        if (num_str[i] < '0' || num_str[i] > '9') return NULL;
    }

    char* result = malloc(len + 2);
    if (!result) return NULL;

    bool all_nines = true;
    for (int i = 0; i < len; i++) {
        if (num_str[i] != '9') {
            all_nines = false;
            break;
        }
    }

    if (all_nines) {
        result[0] = '1';
        for (int i = 1; i < len; i++) result[i] = '0';
        result[len] = '1';
        result[len + 1] = '\0';
        return result;
    }

    memcpy(result, num_str, len + 1);
    int left = 0;
    int right = len - 1;

    while (left < right) {
        if (result[left] < result[right]) {
            result[right] = result[left];
            int i = right - 1;
            while (i >= 0 && result[i] == '9') {
                result[i] = '0';
                i--;
            }
            if (i >= 0) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* const argv[const]) {
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