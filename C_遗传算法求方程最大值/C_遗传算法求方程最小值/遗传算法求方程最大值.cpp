#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define N1 100
#define N2  33
#define PI  3.1415926
double evalf(int T[N1][N2], int n);
double qiumax(double f[N1], int n3);
int select(int T[N1][N2], double f[]);
void main()
{
	clock_t start, finish;
	int num = 100;         //初始化种群数量
	int crosspoint = 3;//定点交叉第crosspoint个点
	int temps = 1000;//迭代次数
	double pc = 0.25;//交叉概率
	double pm = 0.05;//变异概率
	start = clock();
	int T[N1][N2];
	srand((unsigned)time(NULL));//初始化随机数
	for (int i = 0; i<N1; i++)
	{
		for (int j = 0; j<N2; j++)
		{
			T[i][j] = rand() % 2;
		}
	}
	double f[N1];
	double max1[100000];
	int cho[N1][N2];
	for (int j4 = 0; j4<temps; j4++)
	{
		//double f[N1];


		for (int i1 = 0; i1<N1; i1++)
		{
			f[i1] = evalf(T, i1);
		}
		max1[j4] = qiumax(f, N1);
		double sum = 0;//*************************************选择部分
		float p[N1];
		float q[N1];
		for (int i = 0; i<N1; i++)
		{
			sum = sum + f[i];
		}
		for (int j = 0; j<N1; j++)
		{
			p[j] = f[j] / sum;
			if (j == 0)
				q[j] = p[j];
			if (j>0)
				q[j] = p[j] + q[j - 1];
		}
		for (int i1 = 0; i1<100; i1++)
		{
			float r;
			r = rand() % 100 / 100.0;
			for (int j1 = 0; j1<100; j1++)
			{
				if (j1 == 0)
				if (r<q[j1])
				for (int i2 = 0; i2<N2; i2++)
				{
					cho[i1][i2] = T[j1][i2];
				}
				if (j1>0)
				if (q[j1 - 1]<r<q[j1])
				{
					for (int i2 = 0; i2<N2; i2++)
					{
						cho[i1][i2] = T[j1][i2];
					}
					break;
				}
			}
		}//****************************************以上为select部分
		int r2 = crosspoint;//***********************以下部分为交叉部分
		int ru[N1];//讲double改为int之后，cho[ru[c1]]错误消失
		int count1 = 0, c1, c2;
		int cho2[N1][N2];
		for (int i9 = 0; i9<N1; i9++)
		{
			double ran[N1];
			ran[i9] = rand() % 100 / 100.0;
			if (ran[i9]<pc)
			{

				ru[count1] = i9;
				count1++;
			}
		}
		for (int k = 0; k<(N1 / 2); k++)
		{
			c1 = count1*(rand() % 100 / 100.0);
			c2 = count1*(rand() % 100 / 100.0);
			if ((c1 != c2) && (c1<count1) && (c2<count1))
			{
				for (int k1 = 0; k1<N2; k1++)
				{
					if (k1<crosspoint)
					{
						cho[ru[c1]][k1] = cho[ru[c2]][k1];
					}
					else
					{
						cho[ru[c2]][k1] = cho[ru[c1]][k1];
					}
				}
			}
		}//************************************************以上部分为交叉部分
		//int m=N1,n=N2;//**********************************以下部分为变异部分
		double ran[N2];
		int mu[N2];
		for (int i2 = 0; i2<N1; i2++)
		{
			int count = 0;
			for (int i8 = 0; i8<N2; i8++)
			{
				ran[i8] = (rand() % 100 / 100.0);
				if (ran[i8]<pm)
				{

					mu[count] = i8;
					count++;
				}
			}
			for (int j2 = 0; j2<count; j2++)
			{
				if (cho[i2][mu[j2]] == 0)
					cho[i2][mu[j2]] = 1;
				else
					cho[i2][mu[j2]] = 0;
			}
		}
		for (int m4 = 0; m4<N1; m4++)
		{
			for (int n4 = 0; n4<N2; n4++)
			{
				T[m4][n4] = cho[m4][n4];
			}
		}
	}
	finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f seconds\n", duration);
	double zhi = qiumax(max1, 1000);
	printf("输出函数的最大值：%f\n", zhi);
	getchar();
}
double qiumax(double f[N1], int n3)//******************************	求最大值函数
{
	double max = f[0];
	int i5;
	for (i5 = 1; i5<n3; i5++)
	{
		if (max<f[i5])
		{
			max = f[i5];
		}
	}
	return max;
}
double evalf(int T[N1][N2], int n)//**************************计算适应度函数
{
	double x1;
	double x2;
	double f;
	int i, j;
	double sum1 = 0, sum2 = 0;
	for (j = 0; j<N2; j++)
	{
		int p = 1;//需要注意sum1和sum2和p、p1的位置
		int p1 = 1;
		if (j<18)
		{
			for (int k2 = 1; k2<(18 - j); k2++)
			{
				p *= 2;
			}
			p *= T[n][j];
			sum1 = sum1 + p;
		}
		else
		{
			for (int k3 = 1; k3<(33 - j); k3++)
			{
				p1 *= 2;
			}
			p1 *= T[n][j];
			sum2 = sum2 + p1;
		}

	}
	int s1 = 1;
	for (int k4 = 0; k4<18; k4++)
	{
		s1 *= 2;
	}
	int s2 = 1;
	for (int k5 = 0; k5<15; k5++)
	{
		s2 *= 2;
	}
	x1 = (-3.0) + sum1*(12.1 - (-3)) / (s1 - 1);
	x2 = (4.1) + sum2*(5.8 - (4.1)) / (s2 - 1);
	f = 21.5 + x1*sin(4 * PI*x1) + x2*sin(20 * PI*x2);
	return f;

}
