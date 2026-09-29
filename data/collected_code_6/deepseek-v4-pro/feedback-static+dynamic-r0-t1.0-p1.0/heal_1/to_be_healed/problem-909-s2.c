#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_palindrome(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) return false;
    }
    return true;
}

static void decrement_str(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int i = len - 1;
    while (i >= 0 && str[i] == '0') {
        str[i] = '9';
        i--;
    }
    if (i >= 0) str[i]--;
}

static void make_palindrome(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        str[len - 1 - i] = str[i];
    }
}

static bool handle_smaller(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    char *left = (char *)malloc(len + 1);
    if (left == NULL) exit(EXIT_FAILURE);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(left, str, (len + 1) / 2);
    left[(len + 1) / 2] = '\0';
    decrement_str(left);
    if (left[0] == '0') {
        free(left);
        if (len == 1) {
            str[0] = '0';
            str[1] = '\0';
            return true;
        }
        for (int i = 0; i < len - 1; i++) str[i] = '9';
        str[len - 1] = '\0';
        return true;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int new_len = strlen(left);
    for (int i = 0; i < len; i++) str[i] = '0';
    str[len] = '\0';
    for (int i = 0; i < new_len; i++) str[i] = left[i];
    make_palindrome(str);
    free(left);
    return true;
}

static void previous_palindrome(char *num) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(num);
    if (len == 0) return;

    char *tmp = (char *)malloc(len + 1);
    if (tmp == NULL) exit(EXIT_FAILURE);
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(tmp, num);

    if (is_palindrome(tmp)) {
        decrement_str(tmp);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        int new_len = strlen(tmp);
        if (tmp[0] == '0') {
            if (new_len == 1) {
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strcpy(num, "0");
            } else {
                for (int i = 0; i < new_len - 1; i++) num[i] = '9';
                num[new_len - 1] = '\0';
            }
        } else {
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(num, tmp);
            if (!is_palindrome(num)) {
                handle_smaller(num);
            }
        }
        free(tmp);
        return;
    }

    make_palindrome(tmp);
    if (strcmp(tmp, num) < 0) {
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(num, tmp);
        free(tmp);
        return;
    }

    if (!handle_smaller(tmp)) {
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(num, tmp);
    } else {
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(num, tmp);
    }
    free(tmp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    if (fgets(input, sizeof(input), stdin) == NULL) return EXIT_FAILURE;
    input[strcspn(input, "\n")] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) == 0) return EXIT_FAILURE;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (size_t i = 0; i < strlen(input); i++) {
        if (input[i] < '0' || input[i] > '9') return EXIT_FAILURE;
    }
    previous_palindrome(input);
    printf("%s\n", input);
    return EXIT_SUCCESS;
}