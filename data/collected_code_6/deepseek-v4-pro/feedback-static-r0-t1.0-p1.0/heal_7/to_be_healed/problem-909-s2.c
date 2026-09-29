#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_palindrome(const char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) return false;
    }
    return true;
}

static void decrement_str(char *str, size_t len) {
    size_t i = len - 1;
    while (i < len && str[i] == '0') {
        str[i] = '9';
        i--;
    }
    if (i < len) str[i]--;
}

static void make_palindrome(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        str[len - 1 - i] = str[i];
    }
}

static size_t safe_strnlen(const char *str, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && str[len] != '\0') len++;
    return len;
}

static void safe_memcpy(char *dest, size_t dest_size, const char *src, size_t src_len) {
    if (dest_size == 0) return;
    size_t copy_len = src_len;
    if (copy_len >= dest_size) copy_len = dest_size - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';
}

static bool handle_smaller(char *str, size_t len, size_t capacity) {
    size_t half = (len + 1) / 2;
    char *left = (char *)malloc(half + 1);
    if (left == NULL) exit(EXIT_FAILURE);
    
    if (half > 0 && half <= len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(left, str, half);
    }
    left[half] = '\0';
    decrement_str(left, half);
    
    if (left[0] == '0') {
        free(left);
        if (len == 1) {
            if (capacity >= 2) {
                str[0] = '0';
                str[1] = '\0';
            } else if (capacity == 1) {
                str[0] = '\0';
            }
            return true;
        }
        size_t nines = len - 1;
        if (nines >= capacity) nines = capacity > 0 ? capacity - 1 : 0;
        for (size_t i = 0; i < nines; i++) str[i] = '9';
        if (nines < capacity) str[nines] = '\0';
        return true;
    }
    
    size_t new_len = half;
    if (new_len >= capacity) new_len = capacity > 0 ? capacity - 1 : 0;
    
    if (capacity > 0) {
        for (size_t i = 0; i < capacity; i++) str[i] = '0';
        str[capacity - 1] = '\0';
    }
    
    size_t copy_limit = new_len;
    if (copy_limit >= capacity) copy_limit = capacity > 0 ? capacity - 1 : 0;
    for (size_t i = 0; i < copy_limit; i++) str[i] = left[i];
    
    make_palindrome(str, new_len);
    free(left);
    return true;
}

static void previous_palindrome(char *num, size_t capacity) {
    if (capacity == 0) return;
    
    size_t len = safe_strnlen(num, capacity);
    if (len == 0 || len >= capacity) return;

    char *tmp = (char *)malloc(capacity);
    if (tmp == NULL) exit(EXIT_FAILURE);
    
    size_t copy_limit = len + 1;
    if (copy_limit > capacity) copy_limit = capacity;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tmp, num, copy_limit);
    if (capacity > 0) tmp[capacity - 1] = '\0';

    if (is_palindrome(tmp, len)) {
        decrement_str(tmp, len);
        size_t new_len = safe_strnlen(tmp, capacity);
        
        if (tmp[0] == '0') {
            if (new_len == 1) {
                if (capacity >= 2) {
                    num[0] = '0';
                    num[1] = '\0';
                } else if (capacity == 1) {
                    num[0] = '\0';
                }
            } else {
                size_t fill_len = new_len - 1;
                if (fill_len >= capacity) fill_len = capacity > 0 ? capacity - 1 : 0;
                for (size_t i = 0; i < fill_len; i++) num[i] = '9';
                if (fill_len < capacity) num[fill_len] = '\0';
            }
        } else {
            if (new_len >= capacity) new_len = capacity > 0 ? capacity - 1 : 0;
            safe_memcpy(num, capacity, tmp, new_len);
            if (!is_palindrome(num, new_len)) {
                handle_smaller(num, new_len, capacity);
            }
        }
        free(tmp);
        return;
    }

    make_palindrome(tmp, len);
    if (strcmp(tmp, num) < 0) {
        safe_memcpy(num, capacity, tmp, len);
        free(tmp);
        return;
    }

    if (!handle_smaller(tmp, len, capacity)) {
        size_t updated_len = safe_strnlen(tmp, capacity);
        safe_memcpy(num, capacity, tmp, updated_len);
    } else {
        size_t updated_len = safe_strnlen(tmp, capacity);
        safe_memcpy(num, capacity, tmp, updated_len);
    }
    free(tmp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    
    if (fgets(input, sizeof(input), stdin) == NULL) return EXIT_FAILURE;
    
    size_t newline_pos = 0;
    while (newline_pos < sizeof(input) && input[newline_pos] != '\0') {
        if (input[newline_pos] == '\n') {
            input[newline_pos] = '\0';
            break;
        }
        newline_pos++;
    }
    
    size_t input_len = safe_strnlen(input, sizeof(input));
    if (input_len == 0 || input_len >= sizeof(input) - 1) return EXIT_FAILURE;
    
    for (size_t i = 0; i < input_len; i++) {
        if (input[i] < '0' || input[i] > '9') return EXIT_FAILURE;
    }
    
    previous_palindrome(input, sizeof(input));
    printf("%s\n", input);
    return EXIT_SUCCESS;
}