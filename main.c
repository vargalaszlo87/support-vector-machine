#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct se {
    int kernelType;
    enum {
        LINEAR = 1,
        POLYNOMAL = 2,
        RADIAL_BASIS_FUNCTION = 3
    };


} Setup;
static Setup *setAddress;

void Initialize(Setup *set) {
    setAddress = set;
}


double kernel(double *x, double *y) {
    switch (setAddress->kernelType) {
    case 1:
        return x[0] * y[0] + x[1] * y[1];
        break;
    default:
        break;

    }
}

// K mátrix lekérdezése
double** get_K_matrix(double points[][3], int length) {
    double** K = (double**)malloc(length * sizeof(double*));
    for (int i = 0; i < length; ++i) {
        K[i] = (double*)malloc(length * sizeof(double));
        for (int j = 0; j < length; ++j) {
            K[i][j] = kernel(points[i], points[j]) * (2 * points[i][2] - 1) * (2 * points[j][2] - 1);
        }
    }
    return K;
}


double** getKMatrix(double **points, int size) {
    if (size < 1)
        return 0;
    double **K = (double **)calloc(size, sizeof(double *) + size * sizeof(double));
    if (!K) {
        #ifdef NDEBUG
            printf ("Problem with allocation (K)");
        #endif
    }
    for (int i = 0; i < size; ++i)
        *(K+i) = (double *)(K + size) + i + size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            K[i][j] = kernel(points[i], points[j]) * (2 * points[i][2] - 1) * (2 * points[j][2] - 1);
    }
    return K;
}

int main()
{
    // Init
    Setup set;
    Initialize(&set);

    // Setup
    set.kernelType = LINEAR;




    return 0;
}
