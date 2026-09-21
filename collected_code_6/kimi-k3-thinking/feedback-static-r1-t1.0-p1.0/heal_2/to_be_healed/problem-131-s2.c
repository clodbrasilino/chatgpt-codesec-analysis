#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_CAPACITY 256U

static bool is_vowel(char c)
{
    return strchr("aeiouAEIOU", c) != NULL;
}

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t length = 0U;

    if (str == NULL) {
        return 0U;
    }

    while (length < max_len && str[length] != '\0') {
        length++;
    }

    return length;
}

void reverse_vowels(char *str, size_t max_len)
{
    if (str == NULL || max_len == 0U) {
        return;
    }

    size_t length = bounded_strlen(str, max_len);
    if (length < 2U) {
        return;
    }

    size_t left = 0U;
    size_t right = length - 1U;

    while (left < right) {
        while (left < right && !is_vowel(str[left])) {
            left++;
        }
        while (left < right && !is_vowel(str[right])) {
            right--;
        }
        if (left < right) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];

    printf("Enter a string: ");
    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    input[sizeof input - 1U] = '\0';

    size_t input_length = bounded_strlen(input, sizeof input);
    if (input_length > 0U && input[input_length - 1U] == '\n') {
        input[input_length - 1U] = '\0';
    }

    printf("Original: %s\n", input);
    reverse_vowels(input, sizeof input);
    printf("Vowels reversed: %s\n", input);

    return EXIT_SUCCESS;
}