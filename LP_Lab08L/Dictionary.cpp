#include <iostream>
#include <locale>
#include "Dictionary.h"

namespace Dictionary
{
	Instance Create(const char name[DICTNAMEMAXSIZE], int size)
	{
		if (strlen(name) + 1 > DICTNAMEMAXSIZE) throw THROW01;
		if (size > DICTMAXSIZE) throw THROW02;
		Instance newDictinary;
		strcpy_s(newDictinary.name, name);
		newDictinary.maxsize = size;
		newDictinary.size = 0;
		newDictinary.Dictinary = new Entry[size];
		return newDictinary;
	}

	void AddEntry(Instance& inst, Entry ed)
	{
		if (inst.size + 1 > inst.maxsize) throw THROW03;
		for (int index = 0; index < inst.size; index++)
		{
			Entry entry = *(inst.Dictinary + index);
			if (entry.id == ed.id) throw THROW04;
		}
		*(inst.Dictinary + inst.size++) = ed;
	}

	void DelEntry(Instance& inst, int id)
	{
		for (int index = 0; index < inst.size; index++)
		{
			Entry entry = *(inst.Dictinary + index);
			if (entry.id == id)
			{
				for (int shifted = index + 1; shifted < inst.size; shifted++)
					*(inst.Dictinary + shifted - 1) = *(inst.Dictinary + shifted);
				inst.size--;
				return;
			}
		}
		throw THROW07;
	}

	Entry GetEntry(Instance& inst, int id)
	{
		for (int index = 0; index < inst.size; index++)
		{
			Entry entry = *(inst.Dictinary + index);
			if (entry.id == id) return entry;
		}
		throw THROW05;
	}

	void UpdateEntry(Instance& inst, int id, Entry new_entry)
	{
		for (int index = 0; index < inst.size; index++)
		{
			Entry entry = *(inst.Dictinary + index);
			if (entry.id == id)
			{
				if (new_entry.id == entry.id) throw THROW08;
				*(inst.Dictinary + index) = new_entry;
				return;
			}
		}
		throw THROW06;
	}

	void Print(Instance& inst)
	{
		printf("%-3s | %-30s\n", "ID", "Запись");
		for (int index = 0; index < inst.size; index++)
		{
			Entry entry = *(inst.Dictinary + index);
			printf("%-3d | %-30s\n", entry.id, entry.name);
		}
	}

	void Delete(Instance& inst)
	{
		/*delete[] inst.Dictinary;
		inst.Dictinary = NULL;*/
		for (int index = 0; index < inst.size; index++)
		{
			Entry entry = *(inst.Dictinary + index);
			entry.id = 0;
			entry.name[0] = 0;
		}
		inst.size = 0;
	}
}