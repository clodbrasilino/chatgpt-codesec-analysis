#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 64

int main(void)
{
    char buffer[BUFFER_SIZE];
    int result;

    memset(buffer, 0, sizeof(buffer));

    result = snprintf(buffer, sizeof(buffer), "%s", "Hello, world!");
    if (result < 0 || (size_t)result >= sizeof(buffer)) {
        fprintf(stderr, "Error: string truncated or encoding failure\n");
        return 1;
    }

    printf("%s\n", buffer);
    return 0;
}