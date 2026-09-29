#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 64

static char buffer[BUFFER_SIZE];

int main(void)
{
    strncpy(buffer, "Hello, world!", sizeof(buffer) - 1U);
    buffer[sizeof(buffer) - 1U] = '\0';
    printf("%s\n", buffer);
    return 0;
}