#include <stdio.h>
#include <string.h>

void remove_first_last(char *str, char ch)
{
    size_t len;
    char *first;
    char *last;
    size_t pos;

    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0) {
        return;
    }

    first = strchr(str, ch);
    if (first == NULL) {
        return;
    }

    last = strrchr(str, ch);

    if (last != NULL && last != first) {
        pos = (size_t)(last - str);
        memmove(str + pos, str + pos + 1, len - pos);
        len--;
    }

    pos = (size_t)(first - str);
    memmove(str + pos, str + pos + 1, len - pos);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char ch;
    int c;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    printf("Enter a character to remove: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error reading character\n");
        return 1;
    }
    ch = (char)c;

    remove_first_last(buffer, ch);

    printf("Result: %s\n", buffer);

    return 0;
}