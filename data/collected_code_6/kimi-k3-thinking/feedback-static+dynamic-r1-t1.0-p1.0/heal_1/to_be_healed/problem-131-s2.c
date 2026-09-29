#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_vowel(char c)
{
    return strchr("aeiouAEIOU", c) != NULL;
}

void reverse_vowels(char *str)
{
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);
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
    char input[256];

    printf("Enter a string: ");
    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    printf("Original: %s\n", input);
    reverse_vowels(input);
    printf("Vowels reversed: %s\n", input);

    return EXIT_SUCCESS;
}