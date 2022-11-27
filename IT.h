#pragma once
#include <iostream>

#define MAXSIZE_ID	8					//���� ����� �������� ��������������
#define SCOPED_ID_MAXSIZE   MAXSIZE_ID*2 //���� ����� �������� ������������� + ������� ���������
#define MAXSIZE_TI		4096			//���� ����� ���������� ����� � ������� ���������������
#define NUM_DEFAULT	0x00000000		//�������� �� ��������� ��� int
#define STR_DEFAULT	0x00			//�������� �� ��������� ��� sting
#define NULLIDX_TI		0xffffffff		//��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255				//������������ ����� ���������� ��������
#define NUM_MAXSIZE   127		//������������ �������� ��� ���� number
#define NUM_MINSIZE  -128		//����������� �������� ��� ���� number
#define MAX_PARAMS_COUNT 3				//������������ ���������� ���������� � �������
#define CONCAT_PARAMS_CNT 2			//���-�� ���������� � ������� concat
#define LENGHT_PARAMS_CNT 1	//���-�� ���������� � ������� lenght
#define ATOII_PARAMS_CNT 1 //���-�� ���������� � ������� atoii



namespace IT
{
	enum IDDATATYPE { NUM = 1, STR = 2, PROC = 3, UNDEF };//���� ������ ���������������: ��������, ���������, ��� ����(��� ��������), ��������������
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, S = 5 };	//���� ���������������: ����������, �������, ��������, �������, ����������� �������
	enum STDFNC { F_CONCAT, F_LENGHT, F_ATOII, F_NOT_STD };	//����������� �������

	static const IDDATATYPE CONCAT_PARAMS[] = { IT::IDDATATYPE::STR, IT::IDDATATYPE::STR };//��������� �������  concatstr
	static const IDDATATYPE LENGHT_PARAMS[] = { IT::IDDATATYPE::STR };//��������� ������� strlen
	static const IDDATATYPE ATOII_PARAMS[] = { IT::IDDATATYPE::STR };//��������� �-��� atoi

	struct Entry //������ ������� ������
	{
		int			idxfirstLE;				//������ � ������� ������		
		char		id[SCOPED_ID_MAXSIZE];	//�������������
		IDDATATYPE	iddatatype;				//��� ������
		IDTYPE		idtype;					//��� ��������������

		union
		{
			int	vint;            			//�������� integer

			struct
			{
				int len;					//���������� �������� � string
				char str[TI_STR_MAXSIZE - 1];  //������� � string
			} vstr[TI_STR_MAXSIZE];							//�������� ������

			struct
			{
				int count;					// ���������� ���������� �������
				IDDATATYPE* types;			//���� ���������� �������
			} params;
		} value;						//�������� ��������������
	};


	struct IdTable		//��������� ������� ���������������
	{
		int maxsize;	//������� ������� ��������������� < TI_MAXSIZE
		int size;		//������� ������ ������� ��������������� < maxsize
		Entry* table;	//������ ����� ������� ���������������
	};


	IdTable Create(int size = NULL);	//������� ������� ��������������� < TI_MAXSIZE

	void Add(					//�������� ������ � ������� ���������������
		IdTable& idtable,		//��������� ������� ���������������
		Entry entry				//������ ������� ��������������� 
	);			

	int isId(						//�������: ����� ������(���� ����), TI_NULLIDX(���� ����)
		IdTable& idtable,			//��������� ������� ���������������
		char id[SCOPED_ID_MAXSIZE]	//�������������
	);	

	void Delete(IdTable& idtable);	//������� ������� ������ (���������� ������)
};