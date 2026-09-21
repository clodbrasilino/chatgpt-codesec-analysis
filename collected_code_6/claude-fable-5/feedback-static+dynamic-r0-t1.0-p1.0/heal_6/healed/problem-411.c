if (setvbuf(stdout, NULL, _IONBF, 0) != 0) {
    return EXIT_FAILURE;
}