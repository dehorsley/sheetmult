#include <math.h>
#include "mex.h"
#include "blas.h"

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    /* P = sheetmult(A,R)
     * where
     *     size(P) = [Kth, Kr] 
     *     size(R) = [MN, Kth, Kr]
     *     size(A) = [MN, 1]
     */

    double *R, *P, *A;
    double *Rr, *Pr;
    ptrdiff_t MN, Kr,Kth;
    int r;
    const mwSize* dimR = mxGetDimensions(prhs[1]);

    const char *chn = "N";
    const char *cht = "T";

    /* scalar values to use in dgemm */
    const double one = 1.0, zero = 0.0;
    const ptrdiff_t ione = 1;


    /* mexPrintf("r = %d\n",r); */
    MN = dimR[0];
    Kth = dimR[1];
    Kr = dimR[2];

    A = mxGetPr(prhs[0]);
    R = mxGetPr(prhs[1]); /* N*M x Kth x Kr */

    plhs[0] = mxCreateDoubleMatrix(Kth,Kr,mxREAL);

    P = mxGetPr(plhs[0]);

    /*rth sheet*/
    for(r=0;r<Kr;r++) { 
        Rr = R + r*Kth*MN; /*rth sheet of R. ie R(:,:,r)*/
        Pr = P + r*Kth; /*rth column of P. ie P(:,r);*/
        dgemv(cht, &MN, &Kth, &one, R + r*Kth*MN, &MN, A, &ione, &zero,P+r*Kth, &ione);
    }

}
