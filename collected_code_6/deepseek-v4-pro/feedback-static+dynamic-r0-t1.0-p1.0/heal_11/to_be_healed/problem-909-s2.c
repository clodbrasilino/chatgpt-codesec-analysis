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

static size_t decrement_str(char *str, size_t len) {
    size_t i = len;
    while (i > 0 && str[i - 1] == '0') {
        str[i - 1] = '9';
        i--;
    }
    if (i > 0) {
        str[i - 1]--;
    }
    if (str[0] == '0' && len > 1) {
        memmove(str, str + 1, len - 1);
        str[len - 1] = '\0';
        return len - 1;
    }
    return len;
}

static void make_palindrome(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        str[len - 1 - i] = str[i];
    }
}

static bool handle_smaller(char *str, size_t len, size_t capacity) {
    size_t half = (len + 1) / 2;
    /* Possible weaknesses found:
     *  If condition 'half>capacity' is true, the function will return/exit
     */
    if (half > capacity) {
        return false;
    }

    char *left = (char *)malloc(half + 1);
    if (left == NULL) exit(EXIT_FAILURE);

    if (half > 0) {
        /* Possible weaknesses found:
         *  Testing identical condition 'half>capacity'
         *  Identical condition 'half>capacity', second condition is always false [identicalConditionAfterEarlyExit]
         */
        if (half > capacity) {
            free(left);
            return false;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(left, str, half);
    }
    left[half] = '\0';
    
    size_t left_len = decrement_str(left, half);
    
    /* Possible weaknesses found:
     *  Assuming that condition 'left_len==0' is not redundant
     */
    if (left_len == 0 || (left_len == 1 && left[0] == '0')) {
        free(left);
        /* Possible weaknesses found:
         *  Assuming that condition 'len==1' is not redundant
         */
        if (len == 1) {
            if (2 <= capacity) {
                str[0] = '0';
                str[1] = '\0';
            }
            return true;
        }
        if (len > 0 && len - 1 < capacity) {
            /* Possible weaknesses found:
             *  Condition 'len-1>0' is always true
             *  Condition 'len-1>0' is always true [knownConditionTrueFalse]
             */
            if (len - 1 > 0) {
                memset(str, '9', len - 1);
            }
            str[len - 1] = '\0';
        }
        return true;
    }
    
    size_t total_len = left_len + (len - half);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (total_len >= capacity) {
        free(left);
        return false;
    }
    
    memset(str, 0, capacity);
    /* Possible weaknesses found:
     *  Condition 'left_len>0' is always true [knownConditionTrueFalse]
     *  Condition 'left_len>0' is always true
     */
    if (left_len > 0) {
        if (left_len > capacity) {
            free(left);
            return false;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str, left, left_len);
    }
    make_palindrome(str, total_len);
    str[total_len] = '\0';
    
    free(left);
    return true;
}

static void previous_palindrome(char *num, size_t capacity) {
    size_t len = 0;
    while (len < capacity && num[len] != '\0') {
        len++;
    }
    if (len == 0 || len >= capacity) return;

    char *tmp = (char *)malloc(capacity);
    if (tmp == NULL) exit(EXIT_FAILURE);
    
    /* Possible weaknesses found:
     *  Assignment 'copy_len=(len+1<=capacity)?len+1:capacity', assigned value is less than symbolic=capacity+1
     */
    size_t copy_len = (len + 1 <= capacity) ? len + 1 : capacity;
    if (copy_len > 0) {
        /* Possible weaknesses found:
         *  Condition 'copy_len>capacity' is always false [knownConditionTrueFalse]
         *  Condition 'copy_len>capacity' is always false
         */
        if (copy_len > capacity) {
            free(tmp);
            return;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tmp, num, copy_len);
    }
    if (copy_len == capacity) {
        tmp[capacity - 1] = '\0';
        len = capacity - 1;
    }

    if (is_palindrome(tmp, len)) {
        size_t new_len = decrement_str(tmp, len);
        if (new_len == 1 && tmp[0] == '0') {
            /* Possible weaknesses found:
             *  outer condition: 2<=capacity
             */
            if (2 <= capacity) {
                /* Possible weaknesses found:
                 *  opposite inner condition: 2>capacity
                 *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
                 */
                if (2 > capacity) {
                    free(tmp);
                    return;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(num, "0", 2);
            }
        } else if (new_len < len) {
            if (new_len < capacity) {
                if (new_len > 0) {
                    memset(num, '9', new_len);
                }
                num[new_len] = '\0';
            }
        } else {
            /* Possible weaknesses found:
             *  outer condition: new_len+1<=capacity
             */
            if (new_len + 1 <= capacity) {
                /* Possible weaknesses found:
                 *  opposite inner condition: new_len+1>capacity
                 *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
                 */
                if (new_len + 1 > capacity) {
                    free(tmp);
                    return;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(num, tmp, new_len + 1);
                if (!is_palindrome(num, new_len)) {
                    handle_smaller(num, new_len, capacity);
                }
            }
        }
        free(tmp);
        return;
    }

    make_palindrome(tmp, len);
    if (strcmp(tmp, num) < 0) {
        /* Possible weaknesses found:
         *  outer condition: len+1<=capacity
         */
        if (len + 1 <= capacity) {
            /* Possible weaknesses found:
             *  opposite inner condition: len+1>capacity
             *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
             */
            if (len + 1 > capacity) {
                free(tmp);
                return;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num, tmp, len + 1);
        }
        free(tmp);
        return;
    }

    if (!handle_smaller(tmp, len, capacity)) {
        /* Possible weaknesses found:
         *  outer condition: len+1<=capacity
         */
        if (len + 1 <= capacity) {
            /* Possible weaknesses found:
             *  opposite inner condition: len+1>capacity
             *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
             */
            if (len + 1 > capacity) {
                free(tmp);
                return;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num, tmp, len + 1);
        }
    } else {
        /* Possible weaknesses found:
         *  outer condition: len+1<=capacity
         */
        if (len + 1 <= capacity) {
            /* Possible weaknesses found:
             *  opposite inner condition: len+1>capacity
             *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
             */
            if (len + 1 > capacity) {
                free(tmp);
                return;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num, tmp, len + 1);
        }
    }
    free(tmp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1025];
    if (fgets(input, (int)sizeof(input), stdin) == NULL) return EXIT_FAILURE;
    
    input[strcspn(input, "\n")] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    if (len == 0 || len >= sizeof(input) - 1) return EXIT_FAILURE;
    
    for (size_t i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '9') return EXIT_FAILURE;
    }
    
    previous_palindrome(input, sizeof(input));
    printf("%s\n", input);
    return EXIT_SUCCESS;
}