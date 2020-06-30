/*
 * Copyright (c) 2019-2020 Jakub Kozłowicz
 * All rights reserved.
 */

#ifndef IMAGE_PROCESSING_2_STRUCT_H
#define IMAGE_PROCESSING_2_STRUCT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define ALL_OK 0
#define E_INCORRECT_OPTION -1
#define E_NO_NAME   -2
#define E_NO_VALUES  -3
#define E_NO_FILE   -4
#define E_INCORRECT_DIMENSIONS -5
#define E_PASSING_FILE -6
#define E_OPENING_FILE -7
#define E_INCORRECT_FILE -8
#define E_LOADING_PIXELS -9
#define E_ALLOCATE_MEMORY -10
#define E_DEALLOCATE_MEMORY -11

/**
 * Structure containing data of image
 * @param magicNumber contain number connected to type of image
 * @param xSize horizontal size of image
 * @param ySize vertical size of image
 * @param colorScale number of shades of color in image
 * @param pixels pointer handling memory allocation for PGM image
 * @param r pointer handling memory allocation for red color of PPM image
 * @param g pointer handling memory allocation for green color of PPM image
 * @param b pointer handling memory allocation for blue color of PPM image
 * @param color contain value which color will be processing
 */
typedef struct {
    char magicNumber;
    int xSize, ySize, colorScale;
    void *pixels;
    void *r, *g, *b;
    char *color;
} t_image;

/**
 * Structure containing data of image processing
 * @param pixelsNumber number of read or saved pixels
 * @param inputFile input file handle
 * @param outputFile output file handle
 * @param inputFilename name of input file
 * @param outputFilename name of output file
 * @param thresholdValue threshold value in thresholding filter
 * @param thresholdWhite threshold value in thresholding white filter
 * @param thresholdBlack threshold value in thresholding black filter
 */
typedef struct {
    int pixelsNumber;
    FILE *inputFile, *outputFile;
    char *inputFilename, *outputFilename;
    int thresholdValue, thresholdWhite, thresholdBlack;
} w_options;

#endif //IMAGE_PROCESSING_2_STRUCT_H