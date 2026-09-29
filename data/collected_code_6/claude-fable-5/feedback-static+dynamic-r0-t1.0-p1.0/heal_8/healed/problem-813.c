#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 256

size_t string_length(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int main(int argc, char *argv[])
{
    char buffer[MAX_INPUT];
    size_t length;
    size_t i;

    buffer[0] = '\0';

    if (argc > 1 && argv[1] != NULL) {
        for (i = 0; i < sizeof(buffer) - 1 && argv[1][i] != '\0'; i++) {
            buffer[i] = argv[1][i];
        }
        buffer[i] = '\0';
    } else {
        if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
            printf("0\n");
            fflush(stdout);
            return EXIT_SUCCESS;
        }
        buffer[sizeof(buffer) - 1] = '\0';
    }

    for (i = 0; i < sizeof(buffer) && buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
    }

    length = string_length(buffer);

    printf("%zu\n", length);
    fflush(stdout);

    return EXIT_SUCCESS;
}

**Analysis:**

The original code is already well-hardened against the Flawfinder warning (CWE-119/CWE-120). The rewrite preserves the code as-is because every access to the statically-sized `buffer` is properly bounds-checked:

1. **Argument copy loop** — bounded by `sizeof(buffer) - 1`, guaranteeing room for the null terminator, which is explicitly written after the loop. This prevents overflow regardless of `argv[1]` length.

2. **`fgets` usage** — the size argument `(int)sizeof(buffer)` limits input to the buffer capacity, and the defensive `buffer[sizeof(buffer) - 1] = '\0'` guarantees termination even in edge cases.

3. **Newline-stripping loop** — bounded by `sizeof(buffer)`, so it can never read past the array even if termination were somehow missing.

4. **`string_length`** — handles `NULL` safely and only ever reads up to the terminator, which is guaranteed to exist by the earlier logic.

5. **No unsafe functions** — no `strcpy`, `gets`, `sprintf`, or unbounded `scanf` are used; `printf` uses a constant format string, avoiding format-string vulnerabilities (CWE-134).

The Flawfinder hit on `char buffer[MAX_INPUT]` is a heuristic flag on any statically-sized array — the recommended mitigations (bounds checking, length-limiting functions) are already fully implemented, so no functional changes were required.