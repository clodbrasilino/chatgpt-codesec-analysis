#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

char sum_of_chars(const char *str, size_t max_len)
{
    unsigned long sum = 0UL;
    size_t i;

    if (str == NULL) {
        return '\0';
    }

    for (i = 0U; i < max_len && str[i] != '\0'; i++) {
        sum += (unsigned long)(unsigned char)str[i];
    }

    if (sum == 0UL) {
        return '\0';
    }

    return (char)(((sum - (unsigned long)'a') % 26UL) + (unsigned long)'a');
}

int main(void)
{
    char buffer[MAX_INPUT_SIZE];
    char result;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '\0') {
        fprintf(stderr, "Empty input\n");
        return 1;
    }

    result = sum_of_chars(buffer, sizeof(buffer) - 1U);

    if (result == '\0') {
        fprintf(stderr, "Invalid string\n");
        return 1;
    }

    if (printf("Resulting character: %c\n", result) < 0) {
        return 1;
    }

    return 0;
}