/* 
    Please include compiler name below (you may also include any other modules you would like to be loaded)

COMPILER= gnu

    Please include All compiler flags and libraries as you want them run. You can simply copy this over from the Makefile's first few lines
 
CC = cc
OPT = -O3
CFLAGS = -Wall -std=gnu99 $(OPT)
MKLROOT = /opt/intel/composer_xe_2013.1.117/mkl
LDLIBS = -lrt -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_sequential.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm

*/

const char* dgemm_desc = "Naive, three-loop dgemm.";

/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format.
 * On exit, A and B maintain their input values. */    
void square_dgemm (int n, double* A, double* B, double* C)
{
  int s = 2;
  s = s * (n/s);
  // TODO: Implement the blocking optimization
  for (int i_b = 0; i_b < n; i_b += s)
  {
    for (int j_b = 0; j_b < n; i_b += s)
    {
      for (int k_b = 0; k_b < n; k_b += s)
      {

        /* For each row i of A_ */
        for (int i = i_b; i < i_b + s; i++)
        {
          /* For each column j of B_ */
          for (int j = j_b; j < j_b + s; j++)
          {
            /* Compute C_(i,j) */
            double cij = C[i + j*n];
            for( int k = k_b; k < k_b + s; k++)
              {cij += A[i + k * n] * B[k + j * n];}

            C[i + j*n] = cij;
          }
        }
      }

    }
  }
}
