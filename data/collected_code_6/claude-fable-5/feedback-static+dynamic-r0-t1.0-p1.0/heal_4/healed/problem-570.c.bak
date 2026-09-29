#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_line(FILE *fp)
{
    size_t capacity = 128;
    size_t len = 0;
    char *line;
    int c;
    int got_any = 0;

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    while ((c = fgetc(fp)) != EOF) {
        got_any = 1;
        if (c == '\n') {
            break;
        }
        if (len + 1 >= capacity) {
            size_t new_capacity = capac