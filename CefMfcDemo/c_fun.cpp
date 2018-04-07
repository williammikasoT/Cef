
#include"c_fun.h"
#include<stdio.h>
#include<math.h>
#include <malloc.h>


int  samplex[]={35,40,45,50,55,60,65,70,75,80,85,90,95};
int  sampley[]={0,3,9,17,23,25,23,20,15,10,4,0,0};

int  datax[]={35,40,45,50,55,60,65,70,75,80,85,90,95};
int  datay[]={3,10,15,20,26,24,21,12,11,4,0,0,0};

int  tmpx[13];
int  tmpy[13];
int  D_valuex[13];
int  D_valuey[13];
//float value[sizeof(samplex)+sizeof(datax)];


/***********
author:	陈松健
Time:2017-11-22
Describe:
Parameter:
D1：标准样本结构体指针
D2：测量数据结构体指针
D3：修正后的曲线数据矩阵
Correction_curve
Comparative_data


*/
void Correction_curve(struct gas_concentration *D1,struct gas_concentration *D2,struct gas_concentration *D3)
{

	int  i;
	struct sample  sampleMax1,dataMax2;
	struct gas_concentration tmp_data;
	float time_difference;
	D1->data_max		=	0;
	D1->data_max_num	=	0;
	D2->data_max		=	0;
	D2->data_max_num	=	0;

	
	//检测最高点 s
	for(i=0;i<D1->len;i++)
	{
	
		if(D1->data_max  <D1->datay[i])
		{
		D1->data_max=D1->datay[i];
		D1->data_max_num=i;
		
		}
	}
	for(i=0;i<D2->len;i++)
	{
		if(D2->data_max<D2->datay[i])
		{
		D2->data_max		=	D2->datay[i];
		D2->data_max_num	=	i;
		}
	}
	tmp_data.datax	=	(float*)malloc(D1->len*sizeof(float));
	tmp_data.datay	=	(float*)malloc(D1->len*sizeof(float));



		//样本峰值靠后
		if(D1->data_max_num>D2->data_max_num)
		{
			int i;
			int ret;
			ret=D1->data_max_num-D2->data_max_num;
			for(i=0;i<ret;i++)
			{
				tmp_data.datay[i]=0;
			}

			for(i=0;i<(D1->len-ret);i++)
			{
				tmp_data.datay[ret+i]=D2->datay[i];
			}
		}
		if((D1->data_max_num<D2->data_max_num))
		{
			int i;
			int ret;
			ret=D2->data_max_num-D1->data_max_num;
			for(i=0;i<(D1->len-ret);i++)
			{
				tmp_data.datay[i]=D2->datay[ret+i];
			}

			for(i=(D1->len-ret);i<D1->len;i++)
			{
				tmp_data.datay[i]=0;
			}
		}


		//样本峰值相等
		if((D1->data_max_num==D2->data_max_num))
		{
			int i;
			for(i=0;i<(D1->len);i++)
			{
				tmp_data.datay[i]=D2->datay[i];
			}
		}

		for(i=0;i<(D1->len);i++)
		{
			tmp_data.datax[i]=D1->datax[i];

			D3->datax[i]=D1->datax[i];

			D3->datay[i]=tmp_data.datay[i];
		}

		D3->len=D1->len;
		D3->data_max=D2->data_max;
		D3->data_max_num=D1->data_max_num;
		free(tmp_data.datax);//释放掉使用的内存地址
		free(tmp_data.datay);//释放掉使用的内存地址

	//开始计算误差

	
	


}





/***********
author:	陈松健
Time:2017-11-22
Describe:
Parameter:
D1：标准样本结构体指针
D2：测量数据结构体指针
D3：差异检测结果曲线

Comparative_data
*/

float Comparative_data(struct gas_concentration *D1,struct gas_concentration *D2,struct gas_concentration *D3)
{


	float*len;
	float tmp;
	int i;
	float sum=0;
	len		=	(float*)malloc(D1->len*sizeof(float));

	float *value=(float*)malloc(D1->len * sizeof(float));

	for(i=0;i<D1->len;i++)
	{
		len[i]=D1->datay[i]-D2->datay[i];
		tmp = len[i];
		printf("%f\n",tmp);
	}
	D3->datax[0] = D1->datax[0];
	//value[0] = 0;
	for(i=1;i<D1->len;i++)
	{
		if(len[i-1]>=0)
			{
			if(len[i]>=0)	//++
				{
				value[i]		=	(len[i-1]+len[i])*(D1->datax[i]-D1->datax[i-1])/2;
				}
			else			//+-
				{
				value[i]=(len[i-1]*len[i-1]-len[i]*len[i])*(D1->datax[i]-D1->datax[i-1])/(2*(fabs(len[i-1])+fabs(len[i])));
				}
			}
	
		else//len[i]<0
			{
			if(len[i]>=0)	//-+
				{
				value[i]		=	(len[i]*len[i]-len[i-1]*len[i-1])*(D1->datax[i]-D1->datax[i-1])/(2*(fabs(len[i-1])+fabs(len[i])));
				}
			else			//--
				{
				value[i]		=	(len[i-1]+len[i])*(D1->datax[i]-D1->datax[i-1])/2;
				}
			}

		D3->datax[i]=D1->datax[i];
		D3->datay[i]=-value[i];
		sum+=fabs(D3->datay[i]);
	}

	D3->datay[0] = D3->datay[1];


	if(D1->len>D2->len)
	D3->len = D1->len;
	else
	D3->len = D2->len;




	free(len);
	free(value);

/******************************在这里做曲线修正****************************************/


return sum;


}

/*
void main()
{
	int  i;
	int len[sizeof(sampley)];
	float value[sizeof(sampley)];
	long int tmp_sum;
	struct gas_concentration smp,dat,tmp,D_value;

	

	smp.datax=samplex;
	smp.datay=sampley;
	smp.len=sizeof(samplex)/sizeof(int);
	dat.datax=datax;
	dat.datay=datay;
	dat.len=sizeof(datax)/sizeof(int);
	tmp.datax=tmpx;
	tmp.datay=tmpy;
	tmp.len=sizeof(tmpy)/sizeof(int);
	D_value.datax=D_valuex;
	D_value.datay=D_valuey;
	D_value.len=sizeof(D_valuey)/sizeof(int);

//去向修正

Correction_curve(&smp,&dat,&tmp);	


//计算差异值
tmp_sum=Comparative_data(&smp,&tmp,&D_value);	


printf(" %d \n",tmp_sum);

}
*/
