typedef struct complex_d
{
	float real;
	float imag;
}CPLX_T;

extern CPLX_T cplx_add(CPLX_T A, CPLX_T B);
extern CPLX_T cplx_sub(CPLX_T A, CPLX_T B);
extern CPLX_T cplx_mul(CPLX_T A, CPLX_T B);
