/*
 * Copyright (c) 2019-2020 Jakub Kozłowicz
 * All rights reserved.
 */

#ifndef IMAGE_PROCESSING_2_OPTIONS_H
#define IMAGE_PROCESSING_2_OPTIONS_H

#include "struct.h"

/**
 * Handle options given when executing a program
 * @param argc number of arguments
 * @param argv table with saved arguments
 * @param options structure with image processing options
 * @param image structure with image
 * @return state of processing image
 */
int handleOptions(int argc, char **argv, w_options *options, t_image *image);

/**
 * Handle options of image processing if no arguments were given when executing a program
 * @param options structure with image processing options
 * @param image structure with image
 */
int menu(w_options *options, t_image *image);

#endif //IMAGE_PROCESSING_2_OPTIONS_H