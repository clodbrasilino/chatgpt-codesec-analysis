#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_spaces(char *str, size_t max_len)
{
    size_t i;
    size_t j;

    if (str == NULL || max_len == 0) {
        return;
    }

    j = 0;
    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j] = str[i];
            j++;
        }
    }

    if (j < max_len) {
        str[j] = '\0';
    } else {
        str[max_len - 1] = '\0';
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return 1;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    remove_spaces(buffer, sizeof(buffer));

    printf("Result: %s\n", buffer);

    return 0;
}