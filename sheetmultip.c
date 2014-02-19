#include <math.h>
#include "mex.h"
#include "blas.h"

bool mxUnshareArray(mxArray *array_ptr, bool noDeepCopy);

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    /* sheetmulti(A,R,P,beta)
     * returns P(:,i) = A'*R(:,:,i) + beta*P(:,i) for i=1:Kr
     * where
     *     size(P) = [Kth, Kr] 
     *     size(R) = [MN, Kth, Kr]
     *     size(A) = [MN, 1]
     * 
     * Saves values in place
     */

    double *R, *P, *A;
    double *Rr, *Pr;
    double beta;
    ptrdiff_t MN,Kr,Kth;;

    int r;
    
    const mwSize* dimR = mxGetDimensions(prhs[1]);

    char *chn = "N";
    char *cht = "T";
    /* scalar values to use in dgemm */
    double one = 1.0, zero = 0.0;
    ptrdiff_t ione = 1;

    if(nrhs != 4){
          mexErrMsgIdAndTxt( "MATLAB:convec:invalidNumInputs", "Four inputs required.");
    }


    plhs[0] = (mxArray*) prhs[2];
    /* Make sure array is not waiting for COW */
    mxUnshareArray(plhs[0], true); 

    /* mexPrintf("r = %d\n",r); */
    MN = dimR[0];
    Kth = dimR[1];
    Kr = dimR[2];

    A = mxGetPr(prhs[0]);
    R = mxGetPr(prhs[1]); /* N*M x Kth x Kr */

    P = mxGetPr(plhs[0]);

    beta = mxGetScalar(prhs[3]);
    /* mexPrintf("beta = %f\n",beta); */

    for(r=0;r<Kr;r++) {
        Rr = R + r*Kth*MN; /* rth sheet of R. ie R(:,:,r) */
        Pr = P + r*Kth; /* rth column of P. ie P(:,r); */
        dgemv(cht, &MN, &Kth, &one, Rr, &MN, A, &ione, &beta,Pr, &ione);
    }

}
