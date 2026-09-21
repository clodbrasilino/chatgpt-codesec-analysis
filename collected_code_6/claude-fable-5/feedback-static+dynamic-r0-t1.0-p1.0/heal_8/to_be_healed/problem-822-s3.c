#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MIN_LENGTH 8
#define MAX_LENGTH 64
#define BUFFER_SIZE 128
#define MAX_DISCARD 4096

static void secure_clear(void *ptr, size_t size)
{
    volatile unsigned char *p;

    if (ptr == NULL || size == 0) {
        return;
    }

    p = (volatile unsigned char *)ptr;

    while (size--) {
        *p++ = 0;
    }
}

static bool flush_stdin(void)
{
    int ch;
    bool discarded = false;
    size_t count = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            discarded = true;
        }
        count++;
    } while (ch != '\n' && ch != EOF && count < MAX_DISCARD);

    return discarded;
}

static bool is_valid_password(const char *password, size_t max_size)
{
    size_t length;
    size_t i;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL || max_size == 0) {
        return false;
    }

    length = strnlen(password, max_size);

    if (length == max_size) {
        return false;
    }

    if (length < MIN_LENGTH || length > MAX_LENGTH) {
        return false;
    }

    for (i = 0; i < length; i++) {
        unsigned char c = (unsigned char)password[i];

        if (!isprint(c)) {
            return false;
        }

        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else if (ispunct(c)) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t length;
    bool truncated = false;

    printf("Enter password: ");

    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return 1;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        secure_clear(buffer, sizeof(buffer));
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    length = strnlen(buffer, sizeof(buffer));

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        truncated = flush_stdin();
    }

    if (!truncated && is_valid_password(buffer, sizeof(buffer))) {
        printf("Password is valid\n");
    } else {
        printf("Password is invalid\n");
    }

    secure_clear(buffer, sizeof(buffer));

    return 0;
}