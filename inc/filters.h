/*
 * Copyright (c) 2019-2020 Jakub Kozłowicz
 * All rights reserved.
 */

#ifndef IMAGE_PROCESSING_2_FILTERS_H
#define IMAGE_PROCESSING_2_FILTERS_H

#include "struct.h"

/**
 * Add contouring filter to PGM image
 * @param pgm structure with PGM image
 */
void contouring(t_image *pgm);

/**
 * Add negative filter to PGM image
 * @param pgm structure with PGM image
 */
void negative(t_image *pgm);

/**
 * Add thresholding filter to PGM image
 * @param pgm structure with PGM image
 * @param thresholdValue contain threshold value
 */
void thresholding(t_image *pgm, int thresholdValue);

/**
 * Add thresholding black filter to PGM image
 * @param pgm structure with PGM image
 * @param thresholdValue contain threshold value
 */
void thresholdingBlack(t_image *pgm, int thresholdValue);

/**
 * Add thresholding white filter to PGM image
 * @param pgm structure with PGM image
 * @param thresholdValue contain threshold value
 */
void thresholdingWhite(t_image *pgm, int thresholdValue);

/**
 * Add horizontal blur filter to PGM image
 * @param pgm structure with PGM image
 */
void horizontalBlur(t_image *pgm);

/**
 * Add vertical blur filter to PGM image
 * @param pgm structure with PGM image
 */
void verticalBlur(t_image *pgm);

/**
 * Add histogram filter to PGM image
 * @param pgm structure with PGM image
 */
void histogram(t_image *pgm);

/**
 * Convert PPM to PGM image
 * @param ppm structure with PPM image
 */
void conversion(t_image *ppm);

/**
 * Add negative filter to PPM image
 * @param ppm structure with PPM image
 */
void negativePPM(t_image *ppm);

/**
 * Add histogram filter to PPM image
 * @param ppm structure with PPM image
 */
void histogramPPM(t_image *ppm);

/**
 * Add thresholding filter to PPM image
 * @param ppm structure with PPM image
 * @param thresholdValue contain threshold value
 */
void thresholdingPPM(t_image *ppm, int thresholdValue);

/**
 * Add thresholding black filter to PPM image
 * @param ppm structure with PPM image
 * @param thresholdValue contain threshold value
 */
void thresholdingBlackPPM(t_image *ppm, int thresholdValue);

/**
 * Add thresholding white filter to PPM image
 * @param ppm structure with PPM image
 * @param thresholdValue contain threshold value
 */
void thresholdingWhitePPM(t_image *ppm, int thresholdValue);

/**
 * Add contouring filter to PPM image
 * @param ppm structure with PPM image
 */
void contouringPPM(t_image *ppm);

/**
 * Add horizontal blur filter to PPM image
 * @param ppm structure with PPM image
 */
void horizontalBlurPPM(t_image *ppm);

/**
 * Add vertical blur filter to PPM image
 * @param ppm structure with PPM image
 */
void verticalBlurPPM(t_image *ppm);

#endif //IMAGE_PROCESSING_2_FILTERS_H