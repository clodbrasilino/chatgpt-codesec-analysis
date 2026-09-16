#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_added_char(const char *str, char *result)
{
    unsigned long sum;
    size_t i;
    size_t len;

    if (str == NULL || result == NULL) {
        return -1;
    }

    len = strlen(str);
    if (len == 0U) {
        return -1;
    }

    sum = 0UL;
    for (i = 0U; i < len; i++) {
        sum += (unsigned long)(unsigned char)str[i];
    }

    *result = (char)((sum % 26UL) + (unsigned long)'a');
    return 0;
}

int main(void)
{
    char buffer[256];
    char result;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    }

    if (get_added_char(buffer, &result) != 0) {
        fprintf(stderr, "Invalid or empty input.\n");
        return EXIT_FAILURE;
    }

    printf("Resulting character: %c\n", result);
    return EXIT_SUCCESS;
}