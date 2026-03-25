#include "cblas.h"
#include <string.h>

void cblas_dgemm(const int layout, const int transa, const int transb,
                 const int m, const int n, const int k,
                 const double alpha, const double *a, const int lda,
                 const double *b, const int ldb,
                 const double beta, double *c, const int ldc)
{

    if (layout != CblasRowMajor)
        return;

    int transA = (transa == CblasTrans);
    int transB = (transb == CblasTrans);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double sum = 0.0;

            for (int t = 0; t < k; t++)
            {
                double a_val, b_val;

                if (transA)
                {
                    a_val = a[t * lda + i];
                }
                else
                {
                    a_val = a[i * lda + t];
                }

                if (transB)
                {
                    b_val = b[j * ldb + t];
                }
                else
                {
                    b_val = b[t * ldb + j];
                }

                sum += a_val * b_val;
            }

            if (beta == 0.0)
            {
                c[i * ldc + j] = alpha * sum;
            }
            else
            {
                c[i * ldc + j] = alpha * sum + beta * c[i * ldc + j];
            }
        }
    }
}