#include <ctype.h>
#include <stdio.h>

int main(void)
{
    size_t longest = 0;
    size_t current = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (isalnum((unsigned char)ch)) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    printf("%zu\n", longest);
    return 0;
}