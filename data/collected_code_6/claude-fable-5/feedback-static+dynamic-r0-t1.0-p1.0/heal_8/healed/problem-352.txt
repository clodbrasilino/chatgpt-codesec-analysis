#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#define BUFFER_SIZE 256

bool all_chars_unique(const char *str, size_t max_len)
{
    bool seen[256] = { false };
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, max_len);

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = true;
    }

    return true;
}

int main(void)
{
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    if (all_chars_unique(buffer, sizeof(buffer))) {
        printf("All characters are unique\n");
    } else {
        printf("Duplicate characters found\n");
    }

    return 0;
}

The source code was already well-hardened against the identified weakness (CWE-119/CWE-120), so the rewrite preserves the existing mitigations:

**Buffer overflow protections in place:**
- `fgets(buffer, sizeof(buffer), stdin)` limits input to the buffer size, unlike unsafe alternatives such as `gets()` or unbounded `scanf("%s", ...)`.
- `sizeof(buffer)` is used consistently rather than a repeated magic number, so the size argument can never drift out of sync with the actual array size.
- `buffer[sizeof(buffer) - 1] = '\0'` guarantees null-termination defensively, even though `fgets` already terminates.
- `memset` zero-initializes the buffer before use, avoiding reads of indeterminate memory.

**Safe string handling:**
- `strnlen(str, max_len)` (available via `_POSIX_C_SOURCE 200809L`) is used instead of `strlen`, bounding the scan even if a non-terminated buffer were ever passed.
- `strcspn` safely strips the trailing newline without risk of out-of-bounds access, and works correctly even when no newline is present.

**Robustness checks:**
- The `NULL` check in `all_chars_unique` guards against invalid pointers.
- The cast to `unsigned char` before indexing `seen[]` prevents negative-index undefined behavior when `char` is signed.
- The `fgets` return value is checked, handling EOF/read errors gracefully.

The static array flagged by Flawfinder is a low-risk finding; all accesses are bounds-checked, so no changes were required.