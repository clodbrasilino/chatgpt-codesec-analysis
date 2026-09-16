#include <stdio.h>

int get_ascii_value(char c)
{
    return (int)(unsigned char)c;
}

int main(void)
{
    char c;
    int result;

    printf("Enter a character: ");
    result = scanf("%c", &c);
    if (result != 1) {
        fprintf(stderr, "Error: failed to read input\n");
        return 1;
    }

    printf("The ASCII value of '%c' is %d\n", c, get_ascii_value(c));

    return 0;
}