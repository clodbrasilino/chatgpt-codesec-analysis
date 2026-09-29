#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *find_first_max_even_word(const char *str)
{
    size_t i = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     *  Variable 'start' is assigned a value that is never used. [unreadVariable]
     */
    size_t start = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     *  Variable 'len' is assigned a value that is never used. [unreadVariable]
     */
    size_t len = 0;
    size_t best_start = 0;
    size_t best_len = 0;
    char *result = NULL;

    if (str == NULL)
    {
        return NULL;
    }

    while (str[i] != '\0')
    {
        while (str[i] != '\0' && isspace((unsigned char)str[i]))
        {
            i++;
        }

        if (str[i] == '\0')
        {
            break;
        }

        start = i;
        len = 0;

        while (str[i] != '\0' && !isspace((unsigned char)str[i]))
        {
            i++;
            len++;
        }

        if (len % 2 == 0 && len > best_len)
        {
            best_start = start;
            best_len = len;
        }
    }

    if (best_len == 0)
    {
        return NULL;
    }

    result = (char *)malloc(best_len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, str + best_start, best_len);
    result[best_len] = '\0';

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    char *word = NULL;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    word = find_first_max_even_word(buffer);

    if (word == NULL)
    {
        printf("No even-length word found.\n");
        return EXIT_SUCCESS;
    }

    printf("First maximum length even word: %s\n", word);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Length: %zu\n", strlen(word));

    free(word);
    word = NULL;

    return EXIT_SUCCESS;
}