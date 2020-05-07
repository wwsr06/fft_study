#include "stdio.h"
#include "cplx.h"
#include "math.h"
extern int dft_trans(int Point,CPLX_T *insamp,CPLX_T *Res);
extern int f_trans(int Point, CPLX_T *insamp, CPLX_T *Res);
extern int fft_trans(int Point, CPLX_T *insamp, CPLX_T *Res);
extern int butfly2(int w,int wN,CPLX_T A,CPLX_T B,CPLX_T *ResA,CPLX_T *ResB);
extern int butfly4(CPLX_T *insamp,CPLX_T *Res);
extern int butfly8(CPLX_T *insamp,CPLX_T *Res);
extern int log2calc(int A);

#define 	N		128
#define 	PI	3.1415926

CPLX_T sampledata[N];
CPLX_T Results[N];

int main()
{
		int i;
		
		CPLX_T m,n,q;
		
		printf("start trans:\n");
		
		sampledata[0].real=10;sampledata[0].imag=0;
		sampledata[1].real=60;sampledata[1].imag=0;
		sampledata[2].real=60;sampledata[2].imag=0;
		sampledata[3].real=60;sampledata[3].imag=0;
		sampledata[4].real=60;sampledata[4].imag=0;
		sampledata[5].real=60;sampledata[5].imag=0;
		sampledata[6].real=10;sampledata[6].imag=0;
		sampledata[7].real=10;sampledata[7].imag=0;
		
		//f_trans(N, sampledata, Results);
		//dft_trans(N,sampledata,Results);
		fft_trans(N, sampledata, Results);
		
		
		/*
		for(i=0;i<N;i++)
		{
				printf("%f , %f\n",Results[i].real,Results[i].imag);
		}
		*/
		
}

int dft_trans(int Point,CPLX_T *insamp,CPLX_T *Res)
{
		int k,n;
		CPLX_T WN;
		
		for(k=0;k<Point;k++)
		{
				Res[k].real = 0;
				Res[k].imag = 0;
				for(n=0;n<Point;n++)
				{
						WN.real = cos(2*PI*k*n/Point);
						WN.imag = sin(2*PI*k*n/Point);
						Res[k] = cplx_add(Res[k] , cplx_mul(insamp[n], WN));
				}
		}
	
		return 1;
}

int fft_trans(int Point, CPLX_T *insamp, CPLX_T *Res)
{
	int b,i,j,blocks;
	int base,intl;
	CPLX_T WN, tmp;
	CPLX_T BufPingPong[2][N];
	int bitwidth;
	int newseq[N];
	int ppflg = 0;
	
	//Gen new seq
	bitwidth = log2calc(Point);
	for(i=0;i<N;i++)
	{
			newseq[i] = genrevbit(bitwidth,i);
	}

	//base = 2;
	base = 2;
	for(i=0;i<Point/2;i++)
	{
			butfly2(0,Point,insamp[newseq[2*i]],insamp[newseq[2*i+1]],&BufPingPong[ppflg][2*i],&BufPingPong[ppflg][2*i+1]);
	}
	
	while(1)
	{
			base = base*2;
			if(base>Point)break;
			
			printf("Base is : %d\n",base);
			
			blocks = Point/base;
			intl = base/2;
			
			for(b=0;b<blocks;b++)
			{
					for(i=0;i<intl;i++)
					{
							butfly2(i,base,BufPingPong[ppflg][b*base+i],BufPingPong[ppflg][b*base+i+intl],&BufPingPong[!ppflg][b*base+i],&BufPingPong[!ppflg][b*base+i+intl]);
					}
					
			}
			
			ppflg = !ppflg;
	
	}
	
	
	
	for (i = 0; i < N; i++)
	{
		Res[i] = BufPingPong[ppflg][i];
	}
	
	
	Point = 8;
	
	
	
	
	

	
}

int f_trans(int Point, CPLX_T *insamp, CPLX_T *Res)
{
	int i;
	CPLX_T WN,tmp;
	CPLX_T B2[8],B4[8],B8[8],PRes[8];
	
	
	butfly2(0,8,insamp[0],insamp[4],&B2[0],&B2[1]);
	butfly2(0,8,insamp[2],insamp[6],&B2[2],&B2[3]);
	butfly2(0,8,insamp[1],insamp[5],&B2[4],&B2[5]);
	butfly2(0,8,insamp[3],insamp[7],&B2[6],&B2[7]);
	
	butfly2(0,8,B2[0],B2[2],&B4[0],&B4[2]);
	butfly2(2,8,B2[1],B2[3],&B4[1],&B4[3]);
	butfly2(0,8,B2[4],B2[6],&B4[4],&B4[6]);
	butfly2(2,8,B2[5],B2[7],&B4[5],&B4[7]);

	butfly2(0,8,B4[0],B4[4],&PRes[0],&PRes[4]);
	butfly2(1,8,B4[1],B4[5],&PRes[1],&PRes[5]);
	butfly2(2,8,B4[2],B4[6],&PRes[2],&PRes[6]);
	butfly2(3,8,B4[3],B4[7],&PRes[3],&PRes[7]);
	
		
	for (i = 0; i < 8; i++)
	{
		printf("%f,%f\n", PRes[i].real, PRes[i].imag);
	}

}

int butfly2(int w,int wN,CPLX_T A,CPLX_T B,CPLX_T *ResA,CPLX_T *ResB)
{
		CPLX_T WN,tmp;
		
		WN.real = cos(2*PI*w/wN);
		WN.imag = sin(2*PI*w/wN);
		tmp = cplx_mul(B,WN);
		
		*ResA = cplx_add(A,tmp);
		*ResB = cplx_sub(A,tmp);
		
}

int log2calc(int A)
{
		int i=0;
		int tmp=2;
		
		while(1)
		{
				tmp = tmp<<1;
				i += 1;
				
				if(tmp>=A)break;
		}
		
		return (i+1);
}

int genrevbit(int bitw,int A)
{
		int i;
		int val;
		int Res;
		
		Res=0;
		for(i=0;i<bitw;i++)
		{
				val = (A & (1<<(bitw-i-1)));
				if(val!=0)
				{
						Res |= (1<<i);
				}
		}
		
		return Res;
}
