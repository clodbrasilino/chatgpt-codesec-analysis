#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int max_occurring_char(const char *str, char *result)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t i;
    unsigned char best = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    if (str[0] == '\0') {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
            best = c;
        }
    }

    *result = (char)best;
    return 0;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char max_char = '\0';
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
    }

    if (max_occurring_char(buffer, &max_char) != 0) {
        fprintf(stderr, "Invalid or empty input\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum occurring character: %c\n", max_char) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

**Analysis notes:**

The original code already addresses the Flawfinder warning (CWE-119/CWE-120) correctly, so the rewrite preserves the existing mitigations:

1. **Bounded input reading** — `fgets(buffer, (int)sizeof(buffer), stdin)` limits the read to the buffer size, preventing overflow of the statically-sized array.
2. **Guaranteed null termination** — `buffer[sizeof(buffer) - 1] = '\0'` is defensive (though `fgets` already null-terminates), and `memset` zero-initializes the buffer.
3. **Bounded length calculation** — `strnlen` with `sizeof(buffer)` is used instead of `strlen`, avoiding a read past the buffer even if termination somehow failed.
4. **Safe indexing in the counting logic** — casting to `unsigned char` before indexing `counts[UCHAR_MAX + 1]` prevents negative-index undefined behavior on platforms where `char` is signed.
5. **NULL and empty-string checks** — `max_occurring_char` validates both pointers and rejects empty input, with all error paths checked (`fgets`, `printf` return values).

No functional changes were required; the statically-sized buffer is safe because every access is bounds-limited.