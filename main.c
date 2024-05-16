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

typedef struct eq {
    double **K;
    double k0[2];

} Equation;
static Equation *eqAddress;


void Initialize(Setup *set, Equation *eq) {
    // static address
    setAddress = set;
    eqAddress = eq;
    // default

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
    eqAddress->K = (double**)malloc(length * sizeof(double*));
    for (int i = 0; i < length; ++i) {
       eqAddress-> K[i] = (double*)malloc(length * sizeof(double));
        for (int j = 0; j < length; ++j) {
            eqAddress->K[i][j] = kernel(points[i], points[j]) * (2 * points[i][2] - 1) * (2 * points[j][2] - 1);
        }
    }
    return eqAddress->K;
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

double * getk0(double *lambdas, int idxM, int idxL) {
    eqAddress->k0[0] = eqAddress->k0[1] = 1.0;
    for (int i = 0; i < sizeof(lambdas[0])/sizeof(double *); ++i) {
        eqAddress->k0[0] -= lambdas[i] * eqAddress->K[idxM][i];
        eqAddress->k0[1] -= lambdas[i] * eqAddress->K[idxL][i];
    }

}

int main()
{
    // Init
    Setup set;
    Equation eq;
    Initialize(&set, &eq);

    // Setup
    set.kernelType = LINEAR;




    return 0;
}
