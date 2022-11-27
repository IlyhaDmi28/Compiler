#pragma once
#include <iostream>

#define MAXSIZE_ID	8					//макс число символов идентификатора
#define SCOPED_ID_MAXSIZE   MAXSIZE_ID*2 //макс число символов идентификатор + область видимости
#define MAXSIZE_TI		4096			//макс число количество строк в таблице идентификаторов
#define NUM_DEFAULT	0x00000000		//значение по умолчанию дл€ int
#define STR_DEFAULT	0x00			//значение по умолчанию дл€ sting
#define NULLIDX_TI		0xffffffff		//нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255				//максимальна€ длина строкового литерала
#define NUM_MAXSIZE   127		//максимальное значение дл€ типа number
#define NUM_MINSIZE  -128		//минимальное значение дл€ типа number
#define MAX_PARAMS_COUNT 3				//максимальное количество параметров у функции
#define CONCAT_PARAMS_CNT 2			//кол-во параметров у функции concat
#define LENGHT_PARAMS_CNT 1	//кол-во параметров у функции lenght
#define ATOII_PARAMS_CNT 1 //кол-во параметров у функции atoii



namespace IT
{
	enum IDDATATYPE { NUM = 1, STR = 2, PROC = 3, UNDEF };//типы данных идентификаторов: числовой, строковый, без типа(дл€ процедур), неопределенный
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, S = 5 };	//типы идентификаторов: переменна€, функци€, параметр, литерал, стандартна€ функци€
	enum STDFNC { F_CONCAT, F_LENGHT, F_ATOII, F_NOT_STD };	//стандартные функции

	static const IDDATATYPE CONCAT_PARAMS[] = { IT::IDDATATYPE::STR, IT::IDDATATYPE::STR };//параметры функции  concatstr
	static const IDDATATYPE LENGHT_PARAMS[] = { IT::IDDATATYPE::STR };//параметры функции strlen
	static const IDDATATYPE ATOII_PARAMS[] = { IT::IDDATATYPE::STR };//параметры ф-ции atoi

	struct Entry //строка таблицы лексем
	{
		int			idxfirstLE;				//индекс в таблице лексем		
		char		id[SCOPED_ID_MAXSIZE];	//идентификатор
		IDDATATYPE	iddatatype;				//тип данных
		IDTYPE		idtype;					//тип идентификатора

		union
		{
			int	vint;            			//значение integer

			struct
			{
				int len;					//количество символов в string
				char str[TI_STR_MAXSIZE - 1];  //символы в string
			} vstr[TI_STR_MAXSIZE];							//значение строки

			struct
			{
				int count;					// количество параметров функции
				IDDATATYPE* types;			//типы параметров функции
			} params;
		} value;						//значение идентификатора
	};


	struct IdTable		//экземпл€р таблицы идентификаторов
	{
		int maxsize;	//Ємкость таблицы идентификаторов < TI_MAXSIZE
		int size;		//текущий размер таблицы идентификаторов < maxsize
		Entry* table;	//массив строк таблицы идентификаторов
	};


	IdTable Create(int size = NULL);	//Ємкость таблицы идентификаторов < TI_MAXSIZE

	void Add(					//добавить строку в таблицу идентификаторов
		IdTable& idtable,		//экземпл€р таблицы идентификаторов
		Entry entry				//строка таблицы идентификаторов 
	);			

	int isId(						//возврат: номер строки(если есть), TI_NULLIDX(если есть)
		IdTable& idtable,			//экземпл€р таблицы идентификаторов
		char id[SCOPED_ID_MAXSIZE]	//идентификатор
	);	

	void Delete(IdTable& idtable);	//удалить таблицу лексем (освободить пам€ть)
};