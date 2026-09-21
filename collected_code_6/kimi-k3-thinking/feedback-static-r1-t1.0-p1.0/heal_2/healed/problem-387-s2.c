const char *nul = memchr(buffer, '\0', sizeof(buffer));
if (nul == NULL)
{
    fprintf(stderr, "Failed to read input.\n");
    return EXIT_FAILURE;
}
length = (size_t)(nul - buffer);