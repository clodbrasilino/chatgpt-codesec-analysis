#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static size_t count_digits(size_t n)
{
    size_t d = 1;

    while (n >= 10) {
        n /= 10;
        d++;
    }
    return d;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected '123456789101110987654321', got (null)
  */

char *find_demlo(const char *str)
{
    size_t len;
    size_t i;
    size_t pos;
    size_t bufsize;
    size_t start;
    size_t end;
    char *result;
    int written;

    if (str == NULL) {
        return NULL;
    }

    start = 0;
    while (str[start] != '\0' && isspace((unsigned char)str[start])) {
        start++;
    }

    end = strlen(str);
    /* Possible weaknesses found:
     *  Assuming that condition 'end>start' is not redundant
     */
    while (end > start && isspace((unsigned char)str[end - 1])) {
        end--;
    }

    /* Possible weaknesses found:
     *  Assignment 'len=end-start', assigned value is less than 1
     */
    len = end - start;
    /* Possible weaknesses found:
     *  Condition 'len==0' is always true
     *  Condition 'len==0' is always true [knownConditionTrueFalse]
     */
    if (len == 0) {
        return NULL;
    }

    for (i = start; i < end; i++) {
        if (str[i] != '1') {
            return NULL;
        }
    }

    bufsize = 1;
    for (i = 1; i <= len; i++) {
        bufsize += count_digits(i);
        if (i < len) {
            bufsize += count_digits(i);
        }
    }

    result = malloc(bufsize);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 1; i <= len; i++) {
        written = sprintf(result + pos, "%zu", i);
        if (written < 0) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
    }

    for (i = len; i > 1; i--) {
        written = sprintf(result + pos, "%zu", i - 1);
        if (written < 0) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
    }

    result[pos] = '\0';

    return result;
}

int main(void)
{
    char input[64];
    char *demlo;

    printf("Enter a repunit number (only 1s): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\r\n")] = '\0';

    demlo = find_demlo(input);
    if (demlo == NULL) {
        fprintf(stderr, "Invalid input: must be a repunit of one or more 1s\n");
        return EXIT_FAILURE;
    }

    printf("Demlo number: %s\n", demlo);
    free(demlo);

    return EXIT_SUCCESS;
}