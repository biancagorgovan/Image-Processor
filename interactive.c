#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "imageprocessing.h"
#include "bmp.h"

int main() {
    const int LUNGMAX = 100;
    char path[LUNGMAX];
    int ind = 0, inf = 0;  // inf contorizeaza nr filtrelor, ind al imaginilor
    int *width = 0;  // vectorul care salveaza lungimea fiecarei imagini
    int *height = 0;  // vectorul care salveaza latimea fiecarei imagini
    int *lf = 0;  // vectorul care salveaza lungimea fiecarui filtru
    int ****image = 0;  // tablou de 4 dimensiuni in care sunt salvate imaginile
    float ***f = 0;  // tablou de 3 dimensiuni in care se alveaza filtrele
    char comanda[3];
    while (1) {
        scanf("%s" , comanda);
        // comparam sirul de caratere citit pt a identifica ce se executa
        if (comanda[0] == 'e') {
            int i = 0, p = 0, j = 0;
            // se dezaloca toate imaginile si filtrele si se iese din program
            if (ind > 0) {
                for (p = 0; p < ind; p++) {
                    for (i = 0; i < height[p]; i++) {
                        for (j = 0; j < width[p]; j++) {
                            free(image[p][i][j]);
                        }
                    }
                    for (i = 0; i < height[p]; i++) {
                        free(image[p][i]);
                    }
                    free(image[p]);
                }
                free(image);
                free(height);
                free(width);
            }
            if (inf > 0) {
                for (p = 0; p < inf; p++) {
                    for (j = 0; j < lf[p]; j++) {
                        free(f[p][j]);
                    }
                    free(f[p]);
                }
            free(f);
            free(lf);
            }
            break;
        }
        if (comanda[0] == 'l') {
            int i = 0, j = 0;
            int N = 0, M = 0;
            int *auxh = 0;
            int *auxw = 0;
            int ****tmp = 0;
            scanf("%d", &N);
            scanf("%d", &M);
            scanf("%s", path);
            // se aloca dinamica prima matrice
            if (ind == 0) {
                image = (int****)malloc(sizeof(int***));
                if (!image)
                    printf("NU1");
                image[ind] = (int***)malloc(N*sizeof(int**));
                if (!image[ind])
                    printf("NU2");
                for (i = 0; i < N; i++) {
                    image[ind][i] = (int**)malloc(M*sizeof(int*));
                    if (!image[ind][i])
                        printf("NU3");
                    for (j = 0; j < M; j++) {
                        image[ind][i][j] = (int*)malloc(3*sizeof(int));
                        if (!image[ind][i][j])
                            printf("NU4");
                    }
                }
                height = malloc(sizeof(int));
                width = malloc(sizeof(int));
            } else {
                // se realoca tabloul image pt a avea capacitate pt noua img
                tmp = realloc(image, (ind+1)*sizeof(int***));
                tmp[ind] = (int***)malloc(N*sizeof(int**));
                for (i = 0; i < N; i++) {
                tmp[ind][i] = (int**)malloc(M*sizeof(int*));
                }
                for (i = 0; i < N; i++) {
                    for (j = 0; j < M; j++) {
                        tmp[ind][i][j] = (int*)malloc(3*sizeof(int));
                    }
                }
                if (tmp != NULL) {
                    image = tmp;
                }
                auxh = realloc(height, (ind+1)*sizeof(int));
                auxw = realloc(width, (ind+1)*sizeof(int));
                if (auxh != NULL) {
                    height = auxh;
                }
                if (auxw != NULL) {
                    width = auxw;
                }
            }
            height[ind] = N;
            width[ind] = M;
            read_from_bmp(image[ind], N, M, path);
            ind++;  // se incrementeaza nr de img
        }
        if (strcmp(comanda, "s") == 0) {
            int index = 0;
            scanf("%d", &index);
            scanf("%s", path);
            write_to_bmp(image[index], height[index], width[index], path);
        }
        if (strcmp(comanda, "ah") == 0) {
            int index = 0;
            scanf("%d", &index);
            image[index] = flip_horizontal(image[index], height[index], width[index]);
        }
        if (strcmp(comanda, "ar") == 0) {
            int index = 0, i = 0, j = 0, p = 0;
            int ***rot = 0;
            scanf("%d", &index);
            rot = rotate_left(image[index], height[index], width[index]);
            image[index] = (int***)malloc(width[index]*sizeof(int**));
            for (i = 0; i < width[index]; i++) {
                image[index][i] = (int**)malloc(height[index]*sizeof(int*));
                for (j = 0; j < height[index]; j++) {
                    image[index][i][j] = (int*)malloc(3*sizeof(int));
                }
            }
            for (i = 0; i < width[index]; i++) {
                for (j = 0; j < height[index]; j++) {
                    for (p = 0; p < 3; p++) {
                        image[index][i][j][p] = rot[i][j][p];
                    }
                }
            }
            for (p = 0; p < width[index]; p++) {
                for (j = 0; j < height[index]; j++) {
                    free(rot[p][j]);
                }
                free(rot[p]);
            }
            free(rot);
            int aux = height[index];
            height[index] = width[index];
            width[index] = aux;
        }
        if (strcmp(comanda, "ac") == 0) {
            int index = 0, x = 0, y = 0, w = 0, h = 0, i = 0, j = 0, p = 0;
            int ***matcrop = 0;
            scanf("%d", &index);
            scanf("%d", &x);
            scanf("%d", &y);
            scanf("%d", &w);
            scanf("%d", &h);
            matcrop = crop(image[index], height[index], width[index], x, y, h, w);
            image[index] = (int ***)malloc(h*sizeof(int**));
            for (i = 0; i < h; i++) {
                image[index][i] = (int**)malloc(w*sizeof(int*));
             }
            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
                     image[index][i][j] = (int *)malloc(3*sizeof(int));
                }
            }
            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
                    for (p = 0; p < 3; p++) {
                        image[index][i][j][p] = matcrop[i][j][p];
                    }
                }
            }
            for (p = 0; p < h; p++) {
                for (j = 0; j < w; j++) {
                    free(matcrop[p][j]);
                }
                free(matcrop[p]);
            }
            free(matcrop);
            height[index] = h;
            width[index] = w;
        }
        if (strcmp(comanda, "ae") == 0) {
            int rows = 0, cols = 0, R = 0, G = 0, B = 0, index = 0, i = 0, j = 0, p = 0;
            int h = 0, w = 0;
            int ***auxae = 0;
            scanf("%d", &index);
            scanf("%d", &rows);
            scanf("%d", &cols);
            scanf("%d", &R);
            scanf("%d", &G);
            scanf("%d", &B);
            auxae = extend(image[index], height[index], width[index], rows, cols, R, G, B);
            h = height[index] + 2*rows;
            w = width[index] + 2*cols;
            image[index] = (int ***)malloc(h*sizeof(int**));
            for (i = 0; i < h; i++) {
                image[index][i] = (int**)malloc(w*sizeof(int*));
             }
            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
                     image[index][i][j] = (int *)malloc(3*sizeof(int));
                }
            }
            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
                    for (p = 0; p < 3; p++) {
                        image[index][i][j][p] = auxae[i][j][p];
                    }
                }
            }
            for (p = 0; p < h; p++) {
                for (j = 0; j < w; j++) {
                    free(auxae[p][j]);
                }
                free(auxae[p]);
            }
            free(auxae);
            height[index] += 2*rows;
            width[index] += 2*cols;
        }
        if (strcmp(comanda, "ap") == 0) {
            int index_dst = 0, index_src = 0, x = 0, y = 0, hs = 0, ws = 0, hd = 0, wd = 0;
            scanf("%d", &index_dst);
            scanf("%d", &index_src);
            scanf("%d", &x);
            scanf("%d", &y);
            hd = height[index_dst];
            wd = width[index_dst];
            hs = height[index_src];
            ws = width[index_src];
            image[index_dst] = paste(image[index_dst], hd, wd, image[index_src], hs, ws, x, y);
        }
        if (strcmp(comanda, "cf") == 0) {
            int i = 0, j = 0;
            int size = 0;
            int *auxlf = 0;
            float ***auxf = 0;
            scanf("%d", &size);
            if (inf == 0) {
                lf = malloc(sizeof(int));
                f = (float***)malloc(sizeof(float**));
                f[inf] = (float **)malloc(size*sizeof(float*));
                for (i = 0; i < size; i++) {
                f[inf][i] = (float*)malloc(size*sizeof(float));
                }
            } else {
                auxf = realloc(f, (inf+1)*sizeof(float**));
                auxf[inf] = (float**)malloc(size*sizeof(float*));
                for (i = 0; i < size; i++) {
                    auxf[inf][i] = (float*)malloc(size*sizeof(float));
                }
                if (auxf != NULL) {
                    f = auxf;
                }
                auxlf = realloc(lf, (inf+1)*sizeof(float));
                if (auxlf != NULL) {
                    lf = auxlf;
                }
            }
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    scanf("%f", &f[inf][i][j]);
                }
            }
            lf[inf] = size;
            inf++;
        }
        if (strcmp(comanda, "af") == 0) {
            int index_img = 0, index_filter = 0, hi = 0, wi = 0, wf = 0;
            scanf("%d", &index_img);
            scanf("%d", &index_filter);
            hi = height[index_img];
            wi = width[index_img];
            wf = lf[index_filter];
            image[index_img] = apply_filter(image[index_img], hi, wi, f[index_filter], wf);
        }
        if (strcmp(comanda, "df") == 0) {
            int i = 0, j = 0, p = 0, k = 0;
            int index_filter = 0;
            float ***tmpf = 0;
            int *tmlf = 0;
            scanf("%d", &index_filter);
            for (i = index_filter; i < inf-1; i++) {
                for (k = 0; k < lf[i]; k++) {
                    free(f[i][k]);
                }
                free(f[i]);
                lf[i] = 0;
                f[i] = (float **)malloc(lf[i+1]*sizeof(float*));
                for (j = 0; j < lf[i+1]; j++) {
                    f[i][j] = (float *)malloc(lf[i+1]*sizeof(float));
                }
                for (j = 0; j < lf[i+1]; j++) {
                    for (p = 0; p < lf[i+1]; p++) {
                        f[i][j][p] = f[i+1][j][p];
                    }
                }
                lf[i] = lf[i+1];
            }
            for (k = 0; k < lf[inf-1]; k++) {
                    free(f[inf-1][k]);
                }
            free(f[inf-1]);
            lf[inf-1] = 0;
            inf--;
            tmpf = realloc(f, inf*sizeof(float**));
            if (tmpf != NULL) {
                f = tmpf;
            }
            tmlf = realloc(lf, inf*sizeof(int));
             if (tmlf != NULL) {
                lf = tmlf;
            }
        }
        if (strcmp(comanda, "di") == 0) {
            int i = 0, p = 0, j = 0, k = 0;
            int index_img = 0;
            int ****tmpm = 0;
            int *tmh = 0;
            int *tmw = 0;
            scanf("%d", &index_img);
            for (k = index_img; k < ind-1; k++) {
                for (i = 0; i < height[k]; i++) {
                    for (j = 0; j < width[k]; j++) {
                        free(image[k][i][j]);
                    }
                }
                for (i = 0; i < height[k]; i++) {
                    free(image[k][i]);
                }
                free(image[k]);
                height[k] = 0;
                width[k] = 0;
                image[k] = (int***)malloc(height[k+1]*sizeof(int**));
                for (p = 0; p < height[k+1]; p++) {
                    image[k][p] = (int**)malloc(width[k+1]*sizeof(int*));
                    for (j = 0; j < width[k+1]; j++) {
                        image[k][p][j] = (int*)malloc(3*sizeof(int));
                    }
                }
                for (i = 0; i < height[k+1]; i++) {
                    for (j = 0; j < width[k+1]; j++) {
                        for (p = 0; p < 3; p++) {
                            image[k][i][j][p] = image[k+1][i][j][p];
                        }
                    }
                }
                height[k] = height[k+1];
                width[k] = width[k+1];
            }
            for (i = 0; i < height[ind-1]; i++) {
                for (j = 0; j < width[ind-1]; j++) {
                    free(image[ind-1][i][j]);
                 }
             }
            for (i = 0; i < height[ind-1]; i++) {
                free(image[ind-1][i]);
            }
            free(image[ind-1]);
            height[ind-1] = 0;
            width[ind-1] = 0;
            ind--;
            tmpm = realloc(image, ind*sizeof(int***));
            if (tmpm != NULL) {
                image = tmpm;
            }
            tmw = realloc(width, ind*sizeof(int));
            if (tmw != NULL) {
                width = tmw;
            }
            tmh = realloc(height, ind*sizeof(int));
            if (tmh != NULL) {
                height = tmh;
            }
        }
    }
    return 0;
}
