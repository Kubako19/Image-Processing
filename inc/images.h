/*
 * Copyright (c) 2019-2020 Jakub Kozłowicz
 * All rights reserved.
 */

#ifndef IMAGE_PROCESSING_2_IMAGES_H
#define IMAGE_PROCESSING_2_IMAGES_H

#include "struct.h"

/**
 * Load image to program
 * @param inputFile file with image to be loaded
 * @param image structure to which image will be saved
 * @return number of loaded pixels
 */
int readImage(FILE *inputFile, t_image *image);

/**
 * Save image to result file
 * @param outputFile file to which image will be saved
 * @param image structure with image
 * @return number of pixels im saved image
 */
int saveImage(FILE *outputFile, t_image *image);

/**
 * Display image
 * @param filename name of file to be displayed
 */
void display(char *filename);

/**
 * Free memory of PGM image
 * @param pgm structure with PGM image
 * @return state of deallocate memory
 */
int deallocatePGM(t_image *pgm);

/**
 * Free memory of PGM image
 * @param ppm structure with PPM image
 * @return state of deallocate memory
 */
int deallocatePPM(t_image *ppm);

#endif //IMAGE_PROCESSING_2_IMAGES_H