#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32
#define MAX_STRINGS 5

void reverse_string(char *str, size_t max_len) {
    size_t left = 0;
    size_t right = 0;

    if (str == NULL || max_len == 0) {
        return;
    }

    while (right < max_len && str[right] != '\0') {
        right++;
    }

    if (right == 0) {
        return;
    }
    right--;

    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

int reverse_string_list(char **list, size_t count, size_t max_len) {
    size_t i;

    if (list == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (list[i] != NULL) {
            reverse_string(list[i], max_len);
        }
    }

    return 0;
}

int main(void) {
    char strings[][BUFFER_SIZE] = {"hello", "world", "programming", "c", "developer"};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *string_ptrs[MAX_STRINGS];
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t i;
    int result;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;

    if (count > MAX_STRINGS) {
        fprintf(stderr, "Error: Too many strings\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        len = 0;
        while (len < BUFFER_SIZE && strings[i][len] != '\0') {
            len++;
        }
        if (len >= BUFFER_SIZE) {
            fprintf(stderr, "Error: String too long or not null-terminated\n");
            return EXIT_FAILURE;
        }
        string_ptrs[i] = strings[i];
    }

    printf("Original strings:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", string_ptrs[i]);
    }

    result = reverse_string_list(string_ptrs, count, BUFFER_SIZE);
    if (result != 0) {
        fprintf(stderr, "Error: Failed to reverse string list\n");
        return EXIT_FAILURE;
    }

    printf("\nReversed strings:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", string_ptrs[i]);
    }

    return EXIT_SUCCESS;
}