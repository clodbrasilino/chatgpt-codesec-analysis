#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_numbers_with_positions(const char *str);

void print_numbers_with_positions(const char *str)
{
    size_t i;
    size_t len;
    size_t start;

    if (str == NULL) {
        fprintf(stderr, "Error: NULL string provided\n");
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    i = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }
            printf("Number: ");
            if (fwrite(&str[start], sizeof(char), i - start, stdout) != (i - start)) {
                fprintf(stderr, "Error: failed to write output\n");
                return;
            }
            printf(", Position: %zu\n", start);
        } else {
            i++;
        }
    }
}

int main(void)
{
    const char *input = "abc123def45gh6789xyz0";

    printf("Input string: %s\n", input);
    print_numbers_with_positions(input);

    return 0;
}