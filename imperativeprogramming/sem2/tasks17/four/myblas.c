#include "cblas.h"
#include <string.h>

void cblas_dgemm(const int layout, const int transa, const int transb,
                 const int m, const int n, const int k,
                 const double alpha, const double *a, const int lda,
                 const double *b, const int ldb,
                 const double beta, double *c, const int ldc)
// const int layout - CblasRowMajor (построчно) или CblasColMajor (постолбцово)
// const int transa - CblasNoTrans или CblasTrans (транспонировать A)
// const int transb - CblasNoTrans или CblasTrans (транспонировать B)
// const int m - количество строк в A и C
// const int n - количество столбцов в B и C
// const int k - количество столбцов в A и строк в B
// const double alpha - множитель для произведения
// const double *a - матрица A (размер m×k)
// const int lda - ведущая размерность A (шаг между строками)
// const double *b - матрица B (размер k×n)
// const int ldb - ведущая размерность B
// const double beta - множитель для C
// double *c - матрица C (размер m×n)
// const int ldc - ведущая размерность C
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