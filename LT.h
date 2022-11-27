#pragma once
#define	LEXEMA_FIXSIZE   1	    //размер лексемы
#define	MAXSIZE_LT		 4096	//максимальное количество строк в ТЛ
#define	NULLDX_TI	 0xffffffff	//нет элемента ТИ
#define LEX_INTEGER	     't'	// разделители
#define	LEX_STRING 	     't'	// типы данных		
#define	LEX_ID			 'i'	// идентификаторы		
#define	LEX_LITERAL		 'l'	// литералы		
#define	LEX_FUNCTION     'f'	// function			
#define	LEX_DECLARE		 'd'	// declare			
#define LEX_RETURN		 'r'	// выход из процедуры/функции
#define LEX_PRINT		 'p'	// print
#define LEX_SEMICOLON	 ';'	// разделитель инструкций
#define	LEX_COMMA		 ','	// разделитель параметров 		
#define	LEX_LEFTBRACE	 '{'	// начало блока		
#define	LEX_BRACELET	 '}'	// конец блока		
#define	LEX_LEFTHESIS	 '('	// начало списка параметров		
#define	LEX_RIGHTTHESIS	 ')'	// конец списка параметров		
#define	LEX_PLUS		 'v'	// сложение	
#define	LEX_MINUS		 'v'	// вычитание
#define	LEX_STAR		 'v'	// умножение
#define LEX_DIRSLASH	 'v'	// деление


namespace LT	//таблица лексем
{
	struct Entry
	{
		char lexema[LEXEMA_FIXSIZE];					//лексема
		int sn;											//номер строки в исходном тексте
		int idxTI;										//индекс в ТИ

		Entry(char lexema[], int sn, int idxTI = NULLDX_TI);
	};

	struct LexTable						//экземпляр таблицы лексем
	{
		int maxsize;					//ёмкость таблицы лексем
		int size;						//текущий размер таблицы лексем
		Entry* table;					//массив строк ТЛ
	};

	LexTable Create(int size);		            //ёмкость < LT_MAXSIZE
	void Add(LexTable& lextable, Entry entry);	//добавить строку в таблицу лексем. Экземпляр ТЛ, строка ТЛ
	Entry GetEntry(LexTable& lextable, int n);  //получить строку ТЛ. экзепмляр ТЛ, номер строки
	void Delete(LexTable& lextable);  //удалить таблицу лексем (освободить память)
};
