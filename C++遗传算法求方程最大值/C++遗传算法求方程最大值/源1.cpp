#include <iostream>  
#include <armadillo>  
#define PI 3.1415926
#define N1 30
#define N2 33
using namespace std;
using namespace arma;
void main()
{
	clock_t start, finish;
	int num=N1;
    int crosspoint=3;
    int temps=100000;
    float pc=0.25;
    float pm=0.05;
 	arma_rng::set_seed_random();
	mat T =round(randu<mat>(N1,N2));
	mat f(1,N1);
	mat max1(1,100000);
	mat x1zhi(1,100000);
	mat x2zhi(1,100000);
	rowvec a(1);
	start=clock();
	for(int k=0;k<temps;k++)
	{
		fmat x1(1,N1);
	    fmat x2(1,N2);
		for(int i1=0;i1<N1;i1++)
		{
		    int i,j;
	        float sum1=0,sum2=0;
	        for( j=0;j<N2;j++)
	        {
	        	int p=1;//需要注意sum1和sum2和p、p1的位置
	        	int p1=1;
				
	        	if(j<18)
	        	{
	        		for(int k2=1;k2<(18-j);k2++)
	        		{
	        			p*=2;
	        		}
	        		p*=T(i1,j);
	        		sum1=sum1+p;
	        	}
	        	else
	        	{
	        		for(int k3=1;k3<(33-j);k3++)
	        		{
	        			p1*=2;
	        		}
	        		p1*=T(i1,j);
	        		sum2=sum2+p1;
	            }
	        }
	        int s1=1;
	        for(int k4=0;k4<18;k4++)
	        {
	        	s1*=2;
	        }
	        int s2=1;
	        for(int k5=0;k5<15;k5++)
	        {
	        	s2*=2;
	        }
	        x1(i1)=(-3.0)+sum1*(12.1-(-3))/(s1-1);
	        x2(i1)=(4.1)+sum2*(5.8-(4.1))/(s2-1);
            f(i1)=21.50+x1(i1)*sin(4*PI*x1(i1))+x2(i1)*sin(20*PI*x2(i1));
		}
		uword index1=f.index_max();
		max1(k)=f(index1);
		x1zhi(k)=x1(index1);
		x2zhi(k)=x2(index1);
		//mat F=f.t();//求转置
		a=sum(f);//必须是MAT型才可以求和，而fmat定义的求和失败，mat F
		mat p1(1,N1);
		mat q1(1,N1);
		for( int i2=0;i2<N1;i2++)
		{
			 p1(i2)=f(i2)/a(0);
			 if(i2==0)
			 {
				 q1(i2)=p1(i2);
			 }
			 if(i2>0)
			 {
				 q1(i2)=p1(i2)+q1(i2-1);
			 }
		}
		//mat cho(N1,N2);
		for( int j2=0;j2<N1;j2++)
		{
			mat rand1=randu<mat>(1,1);
			for(int j3=0;j3<N1;j3++)
			{
				if(j3==0)
				{
					if(rand1(0)<q1(j3))
					    T.row(j2)=T.row(j3);
					else
						T.row(j2)=T.row(j2);
				}
				if(j3>0)
				{
					if(q1(j3-1)<rand1(0)<q1(j3))
					{
						T.row(j2)=T.row(j3);
						break;
					}
				}
			}
		}
		mat rand2=randu<mat>(1,N1);
		uvec q11=find(rand2<pc);
		//q11.print("q11	 = \n");
		if(q11.n_elem!=0)
		{
		    for(int m1=0;m1<(N1/2);m1++)
		    {
		    	mat rand3=randu<mat>(1,2);
		    	int c1=rand3(0)*q11.n_elem;
		    	int c2=rand3(1)*q11.n_elem;
		    	if(c1!=c2)
		    	{
		    		T.row(q11(c1)).cols(crosspoint,32)=T.row(q11(c2)).cols(crosspoint,32);
		    		T.row(q11(c2)).cols(crosspoint,32)=T.row(q11(c1)).cols(crosspoint,32);
		    	}
		    }
		}
		for(int m2=0;m2<N1;m2++)
		{
			mat rand3=randu<mat>(1,N2);
			uvec q12=find(rand3<pm);
			if(q12.n_elem!=0)
			{
				for(int j2=0;j2<q12.n_elem;j2++)
				{
					if(T(m2,q12(j2))==0)
					T(m2,q12(j2))=1;
					else
					T(m2,q12(j2))=0;
				}
			}
		}
	}
	uword index2=max1.index_max();
	double summax=max1(index2);
	double X1=x1zhi(index2);
	double X2=x2zhi(index2);
	finish=clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;  
    printf( "%f seconds\n", duration ); 

	printf("迭代100000次之后得到函数最大值为：%f\n对应的x1为：%f\n对应的x2为：%f\n",summax,X1,X2);
	getchar();

}
