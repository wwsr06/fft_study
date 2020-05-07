#include "stdio.h"
#include "cplx.h"


CPLX_T cplx_add(CPLX_T A, CPLX_T B)
{
	CPLX_T res;
	
	res.real = A.real+B.real;
	res.imag = A.imag+B.imag;
	
	return res;
	
}

CPLX_T cplx_sub(CPLX_T A, CPLX_T B)
{
	CPLX_T res;
	
	res.real = A.real-B.real;
	res.imag = A.imag-B.imag;
	
	return res;
	
}

CPLX_T cplx_mul(CPLX_T A, CPLX_T B)
{
	CPLX_T res;

	res.real = A.real*B.real - A.imag*B.imag;
	res.imag = A.real*B.imag + A.imag*B.real;

	return res;
}