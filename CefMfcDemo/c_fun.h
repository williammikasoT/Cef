#pragma once
struct gas_concentration
{
	float  *datax;		//X轴数据矩阵
	float *datay;		//Y轴数据矩阵
	float data_max;		//Y轴最'值'
	float data_max_num;	//Y轴最'值'坐标
	int  len;			//矩阵数据长度

};

struct sample
{
	float  sampleMax;
	int  number;

};

//D1：标准样本结构体指针
//D2：测量数据结构体指针
//D3：修正后的曲线数据矩阵
void Correction_curve(struct gas_concentration *D1, struct gas_concentration *D2, struct gas_concentration *D3);		// 修正曲线
//D1：标准样本结构体指针
//D2：测量数据结构体指针
//D3：差异检测结果曲线
float Comparative_data(struct gas_concentration *D1, struct gas_concentration *D2, struct gas_concentration *D3);		// 比较数据


