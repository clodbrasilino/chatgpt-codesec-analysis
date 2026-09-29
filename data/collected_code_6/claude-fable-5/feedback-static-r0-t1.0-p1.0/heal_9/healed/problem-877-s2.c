#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define MAX_DISCARD 1048576

static int compare_chars(const void *a, const void *b)
{
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;

    if (ca < cb) {
        return -1;
    }
    if (ca > cb) {
        return 1;
    }
    return 0;
}

int sort_string(char *str, size_t max_len)
{
    size_t len;

    if (str == NULL || max_len == 0) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        return -1;
    }

    if (len > 1) {
        qsort(str, len, sizeof(char), compare_chars);
    }

    return 0;
}

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0;

    do {
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < MAX_DISCARD);
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        discard_remaining_input();
    }

    if (sort_string(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error sorting string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}