/*
 * Copyright (c) 2019-2020 Jakub Kozłowicz
 * All rights reserved.
 */

#include "filters.h"
#include "images.h"

int handleOptions(int argc, char **argv, w_options *options, t_image *image) {
    options->outputFile = stdout;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            return E_INCORRECT_OPTION;
        }

        switch (argv[i][1]) {
            case 'i': { // Load image from file
                if (++i < argc) {
                    options->inputFilename = argv[i];
                    if (strcmp(options->inputFilename, "-") == 0)
                        options->inputFile = stdin;
                    else {
                        /* Open file and check if it is correct */
                        options->inputFile = fopen(options->inputFilename, "r");
                        if (options->inputFile == NULL) {
                            return E_OPENING_FILE;
                        }

                        /* Load image to program */
                        options->pixelsNumber = readImage(options->inputFile, image);
                        fclose(options->inputFile);
                    }
                } else
                    return E_NO_NAME;
                break;
            }
            case 'm': { // Conversion from PPM to PGM
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    if (++i < argc) {
                        image->color = argv[i];
                        if (strcmp(image->color, "s") == 0) {
                            /* Make conversion and change magic number */
                            conversion(image);
                            image->magicNumber = '2';
                        }
                    } else {
                        return E_NO_VALUES;
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 't': { // Add thresholding
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Check if there is threshold value */
                    if (++i < argc) {
                        /* Check if this value is read correctly */
                        if (sscanf(argv[i], "%d", &options->thresholdValue) == 1) {
                            /* Thresholding filter for PGM image */
                            if (image->magicNumber == '2') {
                                thresholding(image, options->thresholdValue);
                            }

                            /* Thresholding filter for PPM image */
                            if (image->magicNumber == '3') {
                                thresholdingPPM(image, options->thresholdValue);
                            }
                        } else {
                            return E_NO_VALUES;
                        }
                    } else {
                        return E_NO_VALUES;
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'tw': { // Add white thresholding
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Check if there is threshold value */
                    if (++i < argc) {
                        /* Check if this value is read correctly */
                        if (sscanf(argv[i], "%d", &options->thresholdWhite) == 1) {
                            /* Thresholding filter for PGM image */
                            if (image->magicNumber == '2') {
                                thresholdingWhite(image, options->thresholdWhite);
                            }

                            /* Thresholding filter for PPM image */
                            if (image->magicNumber == '3') {
                                thresholdingWhitePPM(image, options->thresholdWhite);
                            }
                        } else {
                            return E_NO_VALUES;
                        }
                    } else {
                        return E_NO_VALUES;
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'tb': { // Add black thresholding
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Check if there is threshold value */
                    if (++i < argc) {
                        /* Check if this value is read correctly */
                        if (sscanf(argv[i], "%d", &options->thresholdBlack) == 1) {
                            /* Thresholding filter for PGM image */
                            if (image->magicNumber == '2') {
                                thresholdingBlack(image, options->thresholdBlack);
                            }

                            /* Thresholding filter for PPM image */
                            if (image->magicNumber == '3') {
                                thresholdingBlackPPM(image, options->thresholdBlack);
                            }
                        } else {
                            return E_NO_VALUES;
                        }
                    } else {
                        return E_NO_VALUES;
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'n': { // Add negative
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Negative filter for PGM image */
                    if (image->magicNumber == '2') {
                        negative(image);
                    }

                    /* Negative filter for PPM image */
                    if (image->magicNumber == '3') {
                        negativePPM(image);
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'k': { // Add contouring
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Contouring filter for PGM image */
                    if (image->magicNumber == '2') {
                        contouring(image);
                    }

                    /* Contouring filter for PPM image */
                    if (image->magicNumber == '3') {
                        contouringPPM(image);
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'h': { // Add histogram
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Histogram filter for PGM image */
                    if (image->magicNumber == '2') {
                        histogram(image);
                    }

                    /* Histogram filter for PPM image */
                    if (image->magicNumber == '3') {
                        histogramPPM(image);
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'x': { // Add horizontal blur
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Horizontal blur filter for PGM image */
                    if (image->magicNumber == '2') {
                        horizontalBlur(image);
                    }

                    /* Horizontal blur filter for PPM image */
                    if (image->magicNumber == '3') {
                        horizontalBlurPPM(image);
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'y': { // Add vertical blur
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Vertical blur filter for PGM image */
                    if (image->magicNumber == '2') {
                        verticalBlur(image);
                    }

                    /* Vertical blur filter for PPM image */
                    if (image->magicNumber == '3') {
                        verticalBlurPPM(image);
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'o': { // Save image to result file
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Check if there is name for result file */
                    if (++i < argc) {
                        options->outputFilename = argv[i];
                        if (strcmp(options->outputFilename, "-") == 0) {
                            options->outputFile = stdout;
                        } else {
                            /* Open result file and check if it is opened correctly */
                            options->outputFile = fopen(options->outputFilename, "w");
                            if (options->outputFile == NULL) {
                                return E_NO_FILE;
                            }

                            /* Save image and close file */
                            options->pixelsNumber = saveImage(options->outputFile, image);
                            fclose(options->outputFile);
                        }
                    } else {
                        return E_NO_NAME;
                    }
                } else {
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case 'd': { // Display both images
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    display(options->inputFilename);
                    display(options->outputFilename);
                }
                break;
            }
            default: {
                return E_INCORRECT_OPTION;
            }
        }
    }

    /* Deallocate memory from PGM image */
    if (image->magicNumber == '2')
        deallocatePGM(image);

    /* Deallocate memory from PPM image */
    if (image->magicNumber == '3')
        deallocatePPM(image);

    return ALL_OK;
}

int menu(w_options *options, t_image *image) {
    char inputFilename[100], outputFilename[100];

    char choice[3] = " ";
    while (choice[0] != '0') {
        printf("Menu options:\n");
        printf("\t1. Load image\n");
        printf("\t2. Negative\n");
        printf("\t3. Thresholding\n");
        printf("\t4. Contouring\n");
        printf("\t5. Histogram\n");
        printf("\t6. Horizontal blur\n");
        printf("\t7. Vertical blur\n");
        printf("\t8. Save image\n");
        printf("\t9. Display image\n");
        printf("\t0. End program\n");
        printf("Your choice: ");
        scanf("%1s", choice);

        switch (choice[0]) {
            case '1': { // Read image
                printf("Enter the file name: ");
                scanf("%s", inputFilename);
                options->inputFile = fopen(inputFilename, "r");

                /* Check if file is open correctly */
                if (options->inputFile == NULL) {
                    fprintf(stderr, "\t\tERROR: Incorrect open input file.\n");
                    return E_NO_FILE;
                }

                /* Load image and close file */
                options->pixelsNumber = readImage(options->inputFile, image);
                fclose(options->inputFile);

                if (image->magicNumber == '3') {
                    printf("PPM image need to choose color of image processing.\n");
                    printf("Available options:\n");
                    printf("\t[ r ] - red,\n");
                    printf("\t[ g ] - green,\n");
                    printf("\t[ b ] - blue,\n");
                    printf("\t[ w ] - all colors.\n");
                    printf("Your choice: ");
                    scanf("%s", image->color);
                }
                break;
            }
            case '2': { // Add negative
                printf("You have chosen the negative filter\n");

                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Negative filter for PGM image */
                    if (image->magicNumber == '2') {
                        negative(image);
                    }

                    /* Negative filter for PPM image */
                    if (image->magicNumber == '3') {
                        negativePPM(image);
                    }

                    printf("The negative filter worked correctly\n");
                } else {
                    fprintf(stderr, "\t\tERROR: File error.\n");
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case '3': { // Add thresholding
                printf("You have chosen the thresholding filter\n");

                /* Get threshold value */
                printf("Enter threshold value in percentage: ");
                scanf("%d", &(options->thresholdValue));

                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Thresholding filter for PGM image */
                    if (image->magicNumber == '2') {
                        thresholding(image, options->thresholdValue);
                    }

                    /* Thresholding filter for PPM image */
                    if (image->magicNumber == '3') {
                        thresholdingPPM(image, options->thresholdValue);
                    }

                    printf("The thresholding filter worked correctly\n");
                } else {
                    fprintf(stderr, "\t\tERROR: File error.\n");
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case '4': { // Add contouring
                printf("You have chosen the contouring filter\n");

                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Contouring filter for PGM image */
                    if (image->magicNumber == '2') {
                        contouring(image);
                    }

                    /* Contouring filter for PPM image */
                    if (image->magicNumber == '3') {
                        contouringPPM(image);
                    }

                    printf("The contouring filter worked correctly\n");
                } else {
                    fprintf(stderr, "\t\tERROR: File error.\n");
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case '5': { // Add histogram
                printf("You have chosen the histogram filter\n");

                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Histogram filter for PGM image */
                    if (image->magicNumber == '2') {
                        histogram(image);
                    }

                    /* Histogram filter for PPM image */
                    if (image->magicNumber == '3') {
                        histogramPPM(image);
                    }

                    printf("The histogram filter worked correctly\n");
                } else {
                    fprintf(stderr, "\t\tERROR: File error.\n");
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case '6': { // Add horizontal blur
                printf("You have chosen the horizontal blur filter\n");

                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Horizontal blur filter for PGM image */
                    if (image->magicNumber == '2') {
                        horizontalBlur(image);
                    }

                    /* Horizontal blur filter for PPM image */
                    if (image->magicNumber == '3') {
                        horizontalBlurPPM(image);
                    }

                    printf("The horizontal blur filter worked correctly\n");
                } else {
                    fprintf(stderr, "\t\tERROR: File error.\n");
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case '7': { // Add vertical blur
                printf("You have chosen the vertical blur filter\n");

                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    /* Vertical blur filter for PGM image */
                    if (image->magicNumber == '2') {
                        verticalBlur(image);
                    }

                    /* Vertical blur filter for PPM image */
                    if (image->magicNumber == '3') {
                        verticalBlurPPM(image);
                    }

                    printf("The vertical blur filter worked correctly\n");
                } else {
                    fprintf(stderr, "\t\tERROR: File error.\n");
                    return E_INCORRECT_DIMENSIONS;
                }
                break;
            }
            case '8': { // Save image to result file
                printf("Enter the result file name: ");
                scanf("%s", outputFilename);
                options->outputFile = fopen(outputFilename, "w");

                /* Check if file is open correctly */
                if (options->outputFile == NULL) {
                    fprintf(stderr, "\t\tERROR: Incorrect open output file.\n");
                    return E_NO_FILE;
                }

                /* Save image and close file */
                options->pixelsNumber = saveImage(options->outputFile, image);
                fclose(options->outputFile);

                break;
            }
            case '9': { // Display saved image
                /* Check if there is correct number of pixels */
                if (options->pixelsNumber > 0) {
                    display(inputFilename);
                    display(outputFilename);
                }
                break;
            }
            case '0': { // Deallocate memory and end program
                /* Deallocate memory from PGM image */
                if (image->magicNumber == '2') {
                    if (deallocatePGM(image) != 0) {
                        fprintf(stderr, "\t\tERROR: Incorrect deallocate memory.\n");
                    }
                }

                /* Deallocate memory from PPM image */
                if (image->magicNumber == '3') {
                    if (deallocatePPM(image) != 0) {
                        fprintf(stderr, "\t\tERROR: Incorrect deallocate memory.\n");
                    }
                }
                printf("\tProgram ends... ");
                break;
            }
            default : {
                printf("\t\tUNRECOGNIZED\n");
                break;
            }
        }
    }
    return ALL_OK;
}