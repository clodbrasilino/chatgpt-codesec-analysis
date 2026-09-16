#include <stdio.h>

int get_ascii_value(char c)
{
    return (int)(unsigned char)c;
}

int main(void)
{
    int input;

    printf("Enter a character: ");

    input = getchar();
    if (input == EOF) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    printf("The ASCII value of '%c' is %d\n", (char)input, get_ascii_value((char)input));

    return 0;
}