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

static bool handle_smaller(char *str, size_t len) {
    size_t half = (len + 1) / 2;
    char *left = (char *)malloc(half + 1);
    if (left == NULL) exit(EXIT_FAILURE);
    memcpy(left, str, half);
    left[half] = '\0';
    decrement_str(left, half);
    if (left[0] == '0') {
        free(left);
        if (len == 1) {
            str[0] = '0';
            str[1] = '\0';
            return true;
        }
        for (size_t i = 0; i < len - 1; i++) str[i] = '9';
        str[len - 1] = '\0';
        return true;
    }
    size_t new_len = strlen(left);
    for (size_t i = 0; i < len; i++) str[i] = '0';
    str[len] = '\0';
    for (size_t i = 0; i < new_len; i++) str[i] = left[i];
    make_palindrome(str, new_len);
    free(left);
    return true;
}

static void previous_palindrome(char *num) {
    size_t len = strlen(num);
    if (len == 0) return;

    char *tmp = (char *)malloc(len + 1);
    if (tmp == NULL) exit(EXIT_FAILURE);
    memcpy(tmp, num, len + 1);

    if (is_palindrome(tmp, len)) {
        decrement_str(tmp, len);
        size_t new_len = strlen(tmp);
        if (tmp[0] == '0') {
            if (new_len == 1) {
                memcpy(num, "0", 2);
            } else {
                for (size_t i = 0; i < new_len - 1; i++) num[i] = '9';
                num[new_len - 1] = '\0';
            }
        } else {
            memcpy(num, tmp, new_len + 1);
            if (!is_palindrome(num, new_len)) {
                handle_smaller(num, new_len);
            }
        }
        free(tmp);
        return;
    }

    make_palindrome(tmp, len);
    if (strcmp(tmp, num) < 0) {
        memcpy(num, tmp, len + 1);
        free(tmp);
        return;
    }

    if (!handle_smaller(tmp, len)) {
        size_t updated_len = strlen(tmp);
        memcpy(num, tmp, updated_len + 1);
    } else {
        size_t updated_len = strlen(tmp);
        memcpy(num, tmp, updated_len + 1);
    }
    free(tmp);
}

int main(void) {
    char input[1024];
    if (fgets(input, sizeof(input), stdin) == NULL) return EXIT_FAILURE;
    input[strcspn(input, "\n")] = '\0';
    size_t input_len = strlen(input);
    if (input_len == 0) return EXIT_FAILURE;
    for (size_t i = 0; i < input_len; i++) {
        if (input[i] < '0' || input[i] > '9') return EXIT_FAILURE;
    }
    previous_palindrome(input);
    printf("%s\n", input);
    return EXIT_SUCCESS;
}