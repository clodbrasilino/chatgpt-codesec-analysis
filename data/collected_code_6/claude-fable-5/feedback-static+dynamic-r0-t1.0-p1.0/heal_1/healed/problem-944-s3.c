#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

void print_numbers_with_positions(const char *str)
{
    size_t i;
    size_t len;
    size_t start;

    if (str == NULL) {
        fprintf(stderr, "Error: NULL string passed\n");
        return;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    i = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }
            printf("Number: %.*s, Position: %zu\n",
                   (int)(i - start), &str[start], start);
        } else {
            i++;
        }
    }
}

int main(void)
{
    const char *test = "abc123def45gh6789xyz0";

    print_numbers_with_positions(test);

    return 0;
}