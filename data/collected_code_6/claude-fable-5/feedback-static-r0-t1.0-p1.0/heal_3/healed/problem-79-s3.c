#include <stdio.h>

#define BUFFER_SIZE 64

static char buffer[BUFFER_SIZE];

int main(void)
{
    int result;

    result = snprintf(buffer, sizeof(buffer), "%s", "Hello, world!");
    if (result < 0 || (size_t)result >= sizeof(buffer)) {
        fprintf(stderr, "Error: string truncated or encoding failure\n");
        return 1;
    }

    printf("%s\n", buffer);
    return 0;
}