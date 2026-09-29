#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} PointPair;

static int choose_points(int start1, int end1, int start2, int end2,
                         PointPair *result)
{
    if (result == NULL || start1 > end1 || start2 > end2) {
        return 0;
    }

    if (start1 != start2) {
        result->first = start1;
        result->second = start2;
        return 1;
    }

    if (start1 < end1) {
        result->first = start1 + 1;
        result->second = start2;
        return 1;
    }

    if (start2 < end2) {
        result->first = start1;
        result->second = start2 + 1;
        return 1;
    }

    return 0;
}

static int read_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int main(int argc, const char *argv[])
{
    int start1;
    int end1;
    int start2;
    int end2;
    PointPair result;

    if (argc != 5) {
        fprintf(stderr, "Usage: %s <start1> <end1> <start2> <end2>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (!read_int(argv[1], &start1) ||
        !read_int(argv[2], &end1) ||
        !read_int(argv[3], &start2) ||
        !read_int(argv[4], &end2)) {
        fprintf(stderr, "All range endpoints must be valid integers.\n");
        return EXIT_FAILURE;
    }

    if (start1 > end1 || start2 > end2) {
        fprintf(stderr, "Each range start must not exceed its end.\n");
        return EXIT_FAILURE;
    }

    if (!choose_points(start1, end1, start2, end2, &result)) {
        fprintf(stderr, "No distinct points can be chosen.\n");
        return EXIT_FAILURE;
    }

    printf("%d %d\n", result.first, result.second);
    return EXIT_SUCCESS;
}