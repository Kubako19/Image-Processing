/*
 * Copyright (c) 2019-2020 Jakub Kozłowicz
 * All rights reserved.
 */

#include "filters.h"

void contouring(t_image *pgm) {
    int (*pgmImage)[pgm->xSize];
    pgmImage = (int (*)[pgm->xSize]) pgm->pixels;

    for (int i = 0; i < pgm->ySize - 1; i++) {
        for (int j = 0; j < pgm->xSize - 1; j++) {
            pgmImage[i][j] = (abs(pgmImage[i + 1][j] - pgmImage[i][j]) + abs(pgmImage[i][j + 1] - pgmImage[i][j]));
        }
    }
}

void negative(t_image *pgm) {
    int (*pgmImage)[pgm->xSize];
    pgmImage = (int (*)[pgm->xSize]) pgm->pixels;

    for (int i = 0; i < pgm->ySize; i++) {
        for (int j = 0; j < pgm->xSize; j++) {
            pgmImage[i][j] = pgm->colorScale - pgmImage[i][j];
        }
    }
}

void thresholding(t_image *pgm, int thresholdValue) {
    double threshold = pgm->colorScale * (thresholdValue / 100.0);

    int (*pgmImage)[pgm->xSize];
    pgmImage = (int (*)[pgm->xSize]) pgm->pixels;

    for (int i = 0; i < pgm->ySize; i++) {
        for (int j = 0; j < pgm->xSize; j++) {
            if (pgmImage[i][j] <= threshold)
                pgmImage[i][j] = 0;
            else {
                pgmImage[i][j] = pgm->colorScale;
            }
        }
    }
}

void thresholdingBlack(t_image *pgm, int thresholdValue) {
    double threshold = pgm->colorScale * (thresholdValue / 100.0);

    int (*pgmImage)[pgm->xSize];
    pgmImage = (int (*)[pgm->xSize]) pgm->pixels;

    for (int i = 0; i < pgm->ySize; i++) {
        for (int j = 0; j < pgm->xSize; j++) {
            if (pgmImage[i][j] <= threshold)
                pgmImage[i][j] = 0;
        }
    }
}

void thresholdingWhite(t_image *pgm, int thresholdValue) {
    double threshold = pgm->colorScale * (thresholdValue / 100.0);

    int (*pgmImage)[pgm->xSize];
    pgmImage = (int (*)[pgm->xSize]) pgm->pixels;

    for (int i = 0; i < pgm->ySize; i++) {
        for (int j = 0; j < pgm->xSize; j++) {
            if (pgmImage[i][j] > threshold)
                pgmImage[i][j] = pgm->colorScale;
        }
    }
}

void horizontalBlur(t_image *pgm) {
    int (*pgmImage)[pgm->xSize];
    pgmImage = (int (*)[pgm->xSize]) pgm->pixels;
    for (int i = 1; i < pgm->ySize; i++) {
        for (int j = 1; j < pgm->xSize - 1; j++) {
            pgmImage[i][j] = (pgmImage[i - 1][j] + pgmImage[i][j] + pgmImage[i + 1][j]) / 3;
        }
    }
}

void verticalBlur(t_image *pgm) {
    int (*pgmImage)[pgm->xSize];
    pgmImage = (int (*)[pgm->xSize]) pgm->pixels;
    for (int i = 1; i < pgm->ySize - 1; i++) {
        for (int j = 1; j < pgm->xSize; j++) {
            pgmImage[i][j] = (pgmImage[i][j - 1] + pgmImage[i][j] + pgmImage[i][j + 1]) / 3;
        }
    }
}

void histogram(t_image *pgm) {
    int (*pgmImage)[pgm->xSize];
    pgmImage = (int (*)[pgm->xSize]) pgm->pixels;
    int min = 0, max = 0;
    for (int i = 0; i < pgm->ySize; i++) {
        for (int j = 0; j < pgm->xSize; j++) {
            if (max < pgmImage[i][j]) max = pgmImage[i][j];
            if (min > pgmImage[i][j]) min = pgmImage[i][j];
        }
    }
    for (int i = 0; i < pgm->ySize; i++) {
        for (int j = 0; j < pgm->xSize; j++) {
            pgmImage[i][j] = (pgmImage[i][j] - min) * (pgm->colorScale / (max - min));
        }
    }
}

void conversion(t_image *ppm) {
    ppm->pixels = malloc(ppm->xSize * ppm->ySize * sizeof(int));
    int (*pgmImage)[ppm->xSize];
    pgmImage = (int (*)[ppm->xSize]) ppm->pixels;

    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 0; i < ppm->ySize - 2; i++) {
        for (int j = 0; j < ppm->xSize; j++) {
            pgmImage[i][j] = (r[i][j] + g[i][j] + b[i][j]) / 3;
        }
    }

    free(r);
    free(g);
    free(b);
}

void negativePPM(t_image *ppm) {
    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 0; i < ppm->ySize; i++) {
        for (int j = 0; j < ppm->xSize; j++) {
            if (strcmp(ppm->color, "r") == 0) {
                r[i][j] = ppm->colorScale - r[i][j];
            } else if (strcmp(ppm->color, "g") == 0) {
                g[i][j] = ppm->colorScale - g[i][j];
            } else if (strcmp(ppm->color, "b") == 0) {
                b[i][j] = ppm->colorScale - b[i][j];
            } else if (strcmp(ppm->color, "w") == 0) {
                r[i][j] = ppm->colorScale - r[i][j];
                g[i][j] = ppm->colorScale - g[i][j];
                b[i][j] = ppm->colorScale - b[i][j];
            }
        }
    }
}

void histogramPPM(t_image *ppm) {
    int rMax = 0, rMin = 0, gMax = 0, gMin = 0, bMax = 0, bMin = 0;

    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 0; i < ppm->ySize; i++) {
        for (int j = 0; j < ppm->xSize; j++) {
            if (rMax < r[i][j]) rMax = r[i][j];
            if (rMin > r[i][j]) rMin = r[i][j];

            if (gMax < g[i][j]) gMax = g[i][j];
            if (gMin > g[i][j]) gMin = g[i][j];

            if (bMax < b[i][j]) bMax = b[i][j];
            if (bMin > b[i][j]) bMin = b[i][j];
        }
    }
    for (int i = 0; i < ppm->ySize; i++) {
        for (int j = 0; j < ppm->xSize; j++) {
            if (strcmp(ppm->color, "r") == 0) {
                r[i][j] = (r[i][j] - rMin) * (ppm->colorScale / (rMax - rMin));
            } else if (strcmp(ppm->color, "g") == 0) {
                g[i][j] = (g[i][j] - gMin) * (ppm->colorScale / (gMax - gMin));
            } else if (strcmp(ppm->color, "b") == 0) {
                b[i][j] = (b[i][j] - bMin) * (ppm->colorScale / (bMax - bMin));
            } else if (strcmp(ppm->color, "w") == 0) {
                r[i][j] = (r[i][j] - rMin) * (ppm->colorScale / (rMax - rMin));
                g[i][j] = (g[i][j] - gMin) * (ppm->colorScale / (gMax - gMin));
                b[i][j] = (b[i][j] - bMin) * (ppm->colorScale / (bMax - bMin));
            }
        }
    }
}

void thresholdingPPM(t_image *ppm, int thresholdValue) {
    double threshold = ppm->colorScale * (thresholdValue / 100.0);

    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 0; i < ppm->ySize; i++) {
        for (int j = 0; j < ppm->xSize; j++) {
            if (strcmp(ppm->color, "r") == 0) {
                if (r[i][j] <= threshold)
                    r[i][j] = 0;
                else {
                    r[i][j] = ppm->colorScale;
                }
            } else if (strcmp(ppm->color, "g") == 0) {
                if (g[i][j] <= threshold)
                    g[i][j] = 0;
                else {
                    g[i][j] = ppm->colorScale;
                }
            } else if (strcmp(ppm->color, "b") == 0) {
                if (b[i][j] <= threshold)
                    b[i][j] = 0;
                else {
                    b[i][j] = ppm->colorScale;
                }
            } else if (strcmp(ppm->color, "w") == 0) {
                if (r[i][j] <= threshold)
                    r[i][j] = 0;
                else {
                    r[i][j] = ppm->colorScale;
                }
                if (g[i][j] <= threshold)
                    g[i][j] = 0;
                else {
                    g[i][j] = ppm->colorScale;
                }
                if (b[i][j] <= threshold)
                    b[i][j] = 0;
                else {
                    b[i][j] = ppm->colorScale;
                }
            }
        }
    }
}

void thresholdingBlackPPM(t_image *ppm, int thresholdValue) {
    double threshold = ppm->colorScale * (thresholdValue / 100.0);

    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 0; i < ppm->ySize; i++) {
        for (int j = 0; j < ppm->xSize; j++) {
            if (strcmp(ppm->color, "r") == 0) {
                if (r[i][j] <= threshold)
                    r[i][j] = 0;
            } else if (strcmp(ppm->color, "g") == 0) {
                if (g[i][j] <= threshold)
                    g[i][j] = 0;
            } else if (strcmp(ppm->color, "b") == 0) {
                if (b[i][j] <= threshold)
                    b[i][j] = 0;
            } else if (strcmp(ppm->color, "w") == 0) {
                if (r[i][j] <= threshold) r[i][j] = 0;
                if (g[i][j] <= threshold) g[i][j] = 0;
                if (b[i][j] <= threshold) b[i][j] = 0;
            }
        }
    }
}

void thresholdingWhitePPM(t_image *ppm, int thresholdValue) {
    double threshold = ppm->colorScale * (thresholdValue / 100.0);

    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 0; i < ppm->ySize; i++) {
        for (int j = 0; j < ppm->xSize; j++) {
            if (strcmp(ppm->color, "r") == 0) {
                if (r[i][j] > threshold)
                    r[i][j] = ppm->colorScale;
            } else if (strcmp(ppm->color, "g") == 0) {
                if (g[i][j] > threshold)
                    g[i][j] = ppm->colorScale;
            } else if (strcmp(ppm->color, "b") == 0) {
                if (b[i][j] > threshold)
                    b[i][j] = ppm->colorScale;
            } else if (strcmp(ppm->color, "w") == 0) {
                if (r[i][j] > threshold) r[i][j] = ppm->colorScale;
                if (g[i][j] > threshold) g[i][j] = ppm->colorScale;
                if (b[i][j] > threshold) b[i][j] = ppm->colorScale;
            }
        }
    }
}

void contouringPPM(t_image *ppm) {
    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 0; i < ppm->ySize - 1; i++) {
        for (int j = 0; j < ppm->xSize - 1; j++) {
            if (strcmp(ppm->color, "r") == 0)
                r[i][j] = (abs(r[i + 1][j] - r[i][j]) + abs(r[i][j + 1] - r[i][j]));
            else if (strcmp(ppm->color, "g") == 0)
                g[i][j] = (abs(g[i + 1][j] - g[i][j]) + abs(g[i][j + 1] - g[i][j]));
            else if (strcmp(ppm->color, "b") == 0)
                b[i][j] = (abs(b[i + 1][j] - b[i][j]) + abs(b[i][j + 1] - b[i][j]));
            else if (strcmp(ppm->color, "w") == 0) {
                r[i][j] = (abs(r[i + 1][j] - r[i][j]) + abs(r[i][j + 1] - r[i][j]));
                g[i][j] = (abs(g[i + 1][j] - g[i][j]) + abs(g[i][j + 1] - g[i][j]));
                b[i][j] = (abs(b[i + 1][j] - b[i][j]) + abs(b[i][j + 1] - b[i][j]));
            }
        }
    }
}

void horizontalBlurPPM(t_image *ppm) {
    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 1; i < ppm->ySize; i++) {
        for (int j = 1; j < ppm->xSize - 1; j++) {
            if (strcmp(ppm->color, "r") == 0)
                r[i][j] = (r[i - 1][j] + r[i][j] + r[i + 1][j]) / 3;
            else if (strcmp(ppm->color, "g") == 0)
                g[i][j] = (g[i - 1][j] + g[i][j] + g[i + 1][j]) / 3;
            else if (strcmp(ppm->color, "b") == 0)
                b[i][j] = (b[i - 1][j] + b[i][j] + b[i + 1][j]) / 3;
            else if (strcmp(ppm->color, "w") == 0) {
                r[i][j] = (r[i - 1][j] + r[i][j] + r[i + 1][j]) / 3;
                g[i][j] = (g[i - 1][j] + g[i][j] + g[i + 1][j]) / 3;
                b[i][j] = (b[i - 1][j] + b[i][j] + b[i + 1][j]) / 3;
            }
        }
    }
}

void verticalBlurPPM(t_image *ppm) {
    int (*r)[ppm->xSize];
    r = (int (*)[ppm->xSize]) ppm->r;

    int (*g)[ppm->xSize];
    g = (int (*)[ppm->xSize]) ppm->g;

    int (*b)[ppm->xSize];
    b = (int (*)[ppm->xSize]) ppm->b;

    for (int i = 1; i < ppm->ySize - 1; i++) {
        for (int j = 1; j < ppm->xSize; j++) {
            if (strcmp(ppm->color, "r") == 0)
                r[i][j] = (r[i][j - 1] + r[i][j] + r[i][j + 1]) / 3;
            else if (strcmp(ppm->color, "g") == 0)
                g[i][j] = (g[i][j - 1] + g[i][j] + g[i][j + 1]) / 3;
            else if (strcmp(ppm->color, "b") == 0)
                b[i][j] = (b[i][j - 1] + b[i][j] + b[i][j + 1]) / 3;
            else if (strcmp(ppm->color, "w") == 0) {
                r[i][j] = (r[i][j - 1] + r[i][j] + r[i][j + 1]) / 3;
                g[i][j] = (g[i][j - 1] + g[i][j] + g[i][j + 1]) / 3;
                b[i][j] = (b[i][j - 1] + b[i][j] + b[i][j + 1]) / 3;
            }
        }
    }
}