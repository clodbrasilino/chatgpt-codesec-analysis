#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REPUNIT_LEN 9
#define INPUT_BUF_SIZE 32

#if MAX_REPUNIT_LEN > 9
#error "MAX_REPUNIT_LEN must not exceed 9"
#endif

static char *find_demlo(const char *str, size_t max_len)
{
    size_t len;
    size_t i;
    size_t pos;
    char *result;

    if (str == NULL || max_len == 0 || max_len > 9) {
        return NULL;
    }

    len = strnlen(str, max_len + 1);
    if (len == 0 || len > max_len) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] != '1') {
            return NULL;
        }
    }

    result = malloc(2 * len);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 1; i <= len; i++) {
        result[pos++] = (char)('0' + i);
    }
    for (i = len; i > 1; i--) {
        result[pos++] = (char)('0' + (i - 1));
    }
    result[pos] = '\0';

    return result;
}

static int read_line(char *buf, size_t size)
{
    size_t len;
    int ch;

    if (buf == NULL || size < 2) {
        return -1;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    buf[size - 1] = '\0';

    len = strcspn(buf, "\n");
    if (buf[len] != '\n' && len == size - 1) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -2;
    }
    buf[len] = '\0';

    return 0;
}

int main(void)
{
    char input[INPUT_BUF_SIZE];
    char *demlo;
    int rc;

    printf("Enter a repunit number (only 1s, max %d digits): ", MAX_REPUNIT_LEN);
    fflush(stdout);

    rc = read_line(input, sizeof(input));
    if (rc == -1) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (rc == -2) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    demlo = find_demlo(input, MAX_REPUNIT_LEN);
    if (demlo == NULL) {
        fprintf(stderr, "Invalid input: must be a repunit of 1 to %d ones\n", MAX_REPUNIT_LEN);
        return EXIT_FAILURE;
    }

    printf("Demlo number: %s\n", demlo);
    free(demlo);

    return EXIT_SUCCESS;
}