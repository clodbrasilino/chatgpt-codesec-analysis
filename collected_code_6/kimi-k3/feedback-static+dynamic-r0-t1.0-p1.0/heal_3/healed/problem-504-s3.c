#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static int64_t cube_sum(int64_t n)
{
    if (n < 0 || n > 1290) {
        return -1;
    }
    
    int64_t sum = n * (n + 1) / 2;
    return sum * sum;
}

int main(void)
{
    char buffer[64];
    char *endptr;
    int64_t n;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    
    errno = 0;
    n = strtoimax(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 1;
    }
    
    int64_t result = cube_sum(n);
    if (result == -1) {
        return 1;
    }
    
    printf("%" PRId64 "\n", result);
    return 0;
}