#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int substring_in_list(const char *substring, const char *list[], size_t count)
{
    size_t i;

    if (substring == NULL || list == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            continue;
        }
        if (strstr(list[i], substring) != NULL) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const char *strings[] = {
        "hello world",
        "embedded systems",
        "c programming",
        "secure coding"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    const char *search = "program";
    int result;

    result = substring_in_list(search, strings, count);

    if (result < 0) {
        fprintf(stderr, "Error: invalid input provided\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("Substring \"%s\" found in the list.\n", search);
    } else {
        printf("Substring \"%s\" not found in the list.\n", search);
    }

    return EXIT_SUCCESS;
}