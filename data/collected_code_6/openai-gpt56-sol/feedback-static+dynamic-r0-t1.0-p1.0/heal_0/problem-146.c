#include <stdio.h>
#include <string.h>

void print_ascii_values(const char *string)
{
    size_t index;

    if (string == NULL) {
        return;
    }

    for (index = 0; string[index] != '\0'; ++index) {
        printf("%u\n", (unsigned int)(unsigned char)string[index]);
    }
}

int main(void)
{
    char string[1024];

    if (fgets(string, sizeof string, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }
        return 0;
    }

    string[strcspn(string, "\n")] = '\0';
    print_ascii_values(string);

    if (ferror(stdout)) {
        return 1;
    }

    return 0;
}