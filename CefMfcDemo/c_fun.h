#pragma once
struct gas_concentration
{
	float  *datax;		//X�����ݾ���
	float *datay;		//Y�����ݾ���
	float data_max;		//Y����'ֵ'
	float data_max_num;	//Y����'ֵ'����
	int  len;			//�������ݳ���

};

struct sample
{
	float  sampleMax;
	int  number;

};

//D1����׼�����ṹ��ָ��
//D2���������ݽṹ��ָ��
//D3����������������ݾ���
void Correction_curve(struct gas_concentration *D1, struct gas_concentration *D2, struct gas_concentration *D3);		// ��������
//D1����׼�����ṹ��ָ��
//D2���������ݽṹ��ָ��
//D3��������������
float Comparative_data(struct gas_concentration *D1, struct gas_concentration *D2, struct gas_concentration *D3);		// �Ƚ�����


