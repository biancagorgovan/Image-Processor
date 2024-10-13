#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

int ***flip_horizontal(int ***image, int N, int M) {
    int i = 0, j = 0;
    // aux este folosit pt a crea o copie vect cu val R, G, B pt fiecare pixel
    int *aux = NULL;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M/2; j++) {
            aux = image[i][M-j-1];
            image[i][M-j-1] = image[i][j];
            image[i][j] = aux;
        }
    }
    return image;
}

int ***rotate_left(int ***image, int N, int M) {
    int ***b = NULL;
    int i = 0, j = 0, k = 0;
    // aloc matricea b cu dimensiunile lui image rotita
    b = (int ***)malloc(M*sizeof(int**));
    for (i = 0; i < M; i++) {
        b[i] = (int**)malloc(N*sizeof(int*));
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            b[i][j] = (int *)malloc(3*sizeof(int));
        }
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < 3; k++) {
                b[i][j][k] = image[j][M-1-i][k];
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
    }
    for (i = 0; i < N; i++) {
        free(image[i]);
    }
    free(image);
    return b;
}

int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    if (x >= M || y >= N) {
        return NULL;
    }
    if ((y + h) > N+1) {
        return NULL;
    }
    if ((x + w) > M+1) {
        return NULL;
    }
    int ***b = NULL;
    int i = 0, j = 0, k = 0;
    b = (int ***)malloc(h*sizeof(int**));
    for (i = 0; i < h; i++) {
        b[i] = (int**)malloc(w*sizeof(int*));
    }
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            b[i][j] = (int *)malloc(3*sizeof(int));
        }
    }
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            for (k = 0; k < 3; k++) {
                b[i][j][k] = image[y+i][x+j][k];
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
    }
    for (i = 0; i < N; i++) {
        free(image[i]);
    }
    free(image);
    return b;
}

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int ***b = NULL;
    int i = 0, j = 0, k = 0;
    b = (int ***)malloc((N + 2*rows)*sizeof(int**));
    for (i = 0; i < N + 2*rows; i++) {
        b[i] = (int**)malloc((M + 2*cols)*sizeof(int*));
    }
    for (i = 0; i < N + 2*rows; i++) {
        for (j = 0; j < M + 2*cols; j++) {
            b[i][j] = (int *)malloc(3*sizeof(int));
        }
    }
    for (i = 0; i < N + 2*rows; i++) {
        for (j = 0; j < M + 2*cols; j++) {
            if ((i < rows) || (i >= rows + N) || (j < cols) || (j >= cols + M)) {
                b[i][j][0] = new_R;
                b[i][j][1] = new_G;
                b[i][j][2] = new_B;
            } else {
                for (k = 0; k < 3; k++) {
                b[i][j][k] = image[i - rows][j - cols][k];
                }
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
    }
    for (i = 0; i < N; i++) {
        free(image[i]);
    }
    free(image);
    return b;
}

int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    int i = 0, j = 0, k = 0;
    for (i = y; i < N_dst; i++) {
        for (j = x; j < M_dst; j++) {
            if ((i-y < N_src) && (j-x < M_src)) {
                for (k = 0; k < 3; k++) {
                    image_dst[i][j][k] = image_src[i-y][j-x][k];
                }
            }
        }
    }
    return image_dst;
}

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    #define MAXC 255
    int i = 0, j = 0, k = 0, p = 0, f = 0, b = 0, a = 0;
    float  sr = 0, sg = 0, sb = 0;
    f = filter_size/2;
    int ***copie = 0;
    copie = (int ***)malloc(N*sizeof(int**));
    for (i = 0; i < N; i++) {
        copie[i] = (int**)malloc(M*sizeof(int*));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            copie[i][j] = (int*)malloc(3*sizeof(int));
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < 3; k++) {
                copie[i][j][k] = image[i][j][k];
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            sg = 0;  // salveaza noua valoare pt G
            sr = 0;  // salveaza noua valoare pt R
            sb = 0;  // salveaza noua valoare pt B
            for (p = 0; p < filter_size; p++) {
                for (k = 0; k < filter_size; k++) {
                    a = i-f+p;  // linia vecinului
                    b = j-f+k;  // coloana vecinului
                    if ((a >= 0) && (a < N) && (b >= 0) && (b < M)) {
                        sr = sr + filter[p][k]*(float)copie[a][b][0];
                        sg = sg + filter[p][k]*(float)copie[a][b][1];
                        sb = sb + filter[p][k]*(float)copie[a][b][2];
                    }
                }
            }
            int sri = (int)sr, sgi = (int)sg, sbi = (int)sb;
            if (sri < 0) {
                sri = 0;
            }
            if (sri > MAXC) {
                sri = MAXC;
            }
            if (sgi < 0) {
                sgi = 0;
            }
            if (sgi > MAXC) {
                sgi = MAXC;
            }
            if (sbi < 0) {
                sbi = 0;
            }
            if (sbi > MAXC) {
                sbi = MAXC;
            }
            image[i][j][0] = sri;
            image[i][j][1] = sgi;
            image[i][j][2] = sbi;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(copie[i][j]);
        }
    }
    for (i = 0; i < N; i++) {
        free(copie[i]);
    }
    free(copie);
    return image;
}
