/*
 * Copyright (c) 2019-2020 Jakub Kozłowicz
 * All rights reserved.
 */

#include "images.h"
#include "options.h"
#include "struct.h"

int main(int argc, char **argv) {
    w_options options;
    t_image image;

    /* If no arguments were given when calling the program */
    if (argc == 1) {
        menu(&options, &image);
    }

        /* Otherwise */
    else {
        /* Make image processing and display state from function */
        printf("%d\n", handleOptions(argc, argv, &options, &image));
    }

    return 0;
}