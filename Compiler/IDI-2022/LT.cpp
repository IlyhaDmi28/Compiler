#include "LT.h"

namespace LT
{

	Entry::Entry(char lexema[], int sn, int idxTI)
	{
		this->lexema = lexema;
		this->sn = sn;
		this->idxTI = idxTI;
	}

	void Add(LexTable& lextable, Entry entry)
	{

	}

	LexTable Create(int size)
	{
		for (short i = 0; i < size; i++)
		{

		}
	}
}