#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_binary_string(const char *str)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return false;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char buffer[256];
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (is_binary_string(buffer)) {
        printf("\"%s\" is a binary string\n", buffer);
    } else {
        printf("\"%s\" is not a binary string\n", buffer);
    }

    return 0;
}