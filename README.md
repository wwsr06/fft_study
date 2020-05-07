# fft_study
dft,fft implement


# cplx.x/cplx.h
封装的复数运算

# dftdemo.c

dft_trans(int Point,CPLX_T *insamp,CPLX_T *Res)
原始的暴力DFT计算

fft_trans(int Point, CPLX_T *insamp, CPLX_T *Res)
FFT计算.

1. bit反序
2. 逐级buttterfly运算
