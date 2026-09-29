#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_tuples(const char *s, size_t len, int k) {
    if (s == NULL || k <= 0) {
        return NULL;
    }
    size_t kk = (size_t)k;
    if (kk == 1) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }
    char *stack = malloc(len + 1);
    if (stack == NULL) {
        return NULL;
    }
    size_t *count = NULL;
    if (len > 0) {
        if (len > SIZE_MAX / sizeof(size_t)) {
            free(stack);
            return NULL;
        }
        count = malloc(len * sizeof(size_t));
        if (count == NULL) {
            free(stack);
            return NULL;
        }
    }
    size_t top = 0;
    for (size_t i = 0; i < len; ++i) {
        char c = s[i];
        if (top > 0 && stack[top - 1] == c) {
            count[top - 1]++;
            if (count[top - 1] == kk) {
                top--;
            }
        } else {
            stack[top] = c;
            count[top] = 1;
            top++;
        }
    }
    stack[top] = '\0';
    free(count);
    return stack;
}

int main(void) {
    const char input[] = "deeedbbcccbdaa";
    int k = 3;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = remove_tuples(input, strlen(input), k);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}