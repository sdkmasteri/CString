#include "cstring.h"

//REGION @CASE
void toupperex(PCString self)
{
	if (self)
	{
		do {
			if (*self->str >= 'a' && *self->str <= 'z')
				*self->str -= 32;
		} while (*self->str++);
		self->str -= self->length + 1;
	}
}
void tolowerex(PCString self)
{
	if (self)
	{
		do {
			if (*self->str >= 'A' && *self->str <= 'Z')
				*self->str += 32;
		} while (*self->str++);
		self->str -= self->length + 1;
	};
}
void capitalize(char* str)
{
	if (*str >= 'a' && *str <= 'z')
	{
		*str -= 32;
	}
}
void capitalizeex(PCString self)
{
	capitalize(self->str);
}
int findi(char* str, char ch)
{
	for (int i = 0;; i++)
	{
		if (*(str + i) == '\0') break;
		if (*(str + i) == ch) return i;
	}
	return -1;
}
int length(char* str)
{
	int len = 0;
	while (str[len]) len++;
	return len;
}

char* findchr(char* str, char ch)
{
	int i = findi(str, ch);
	return i >= 0 ? (char*)(str + i) : NULL;
}

int findiex(PCString self, char ch)
{
	return findi(self->str, ch);
}
char* findchrex(PCString self, char ch)
{
	return findchr(self->str, ch);
}

void capall(PCString self)
{
	char* ptr = self->str;
	while (1)
	{
		capitalize(ptr);
		ptr = findchr(ptr, ' ');
		if (ptr == NULL || *(++ptr) == '\0') break;
		//int lendif = self->length - length(ptr);
		//if (lendif >= 0 && lendif < self->length) ptr++;
	} 
}
//REGION END @CASE

//REGION @MEMORY
BOOL swap(PCString self, PCString csptr)
{
	PCString tmp = malloc(sizeof(CString));
	if (tmp)
	{
		tmp->str = self->str;
		tmp->length = self->length;

		self->str = csptr->str;
		self->length = csptr->length;

		csptr->str = tmp->str;
		csptr->length = tmp->length;
		free(tmp);
		return TRUE;
	}
	return FALSE;
}

PCString duple(PCString cstr)
{
	PCString ptr = cstring(cstr->str);
	return ptr;
}
PCString makeptr(PCString cstr)
{
	char* ptr = malloc(sizeof(CString));
	if (!ptr) return NULL;

	char* csptr = (char*)cstr;

	for (int i = 0; i < sizeof(CString); i++)
		ptr[i] = csptr[i];

	return (PCString)ptr;
}
//REGION END @MEMORY

//REGION @EDIT
BOOL removeex(PCString self, char ch)
{
	int ind = findiex(self, ch);

	if (ind < 0) return FALSE;

	//char* result = malloc(self->length);

	char* ptr = self->str;
	for (int i = 0; i < self->length; i++)
	{
		if (i != ind)
			*ptr++ = self->str[i];
	}
	*ptr = '\0';
	//free(self->str);
	self->length--;
	self->str = realloc(self->str, self->length);

	//self->str = result;

	return TRUE;
}

int removemulti(PCString self, char ch, int count)
{
	int removed = 0;
	if (count == 0) return count;
	if (count < 0)
		while (removeex(self, ch)) removed++;
	else
		for (removed; removed < count; removed++)
		{
			if (!removeex(self, ch)) break;
		}
	return removed;
}
int removeall(PCString self, char ch)
{
	return removemulti(self, ch, -1);
}

BOOL replaceex(PCString self, char ch, char rpl)
{
	int ind = findiex(self, ch);

	if (ind < 0) return FALSE;

	self->str[ind] = rpl;
	return TRUE;
}

int replacemulti(PCString self, char ch, char rpl, int count)
{
	int replaced = 0;
	if (count == 0) return 0;
	if (count < 0)
	{
		while (replaceex(self, ch, rpl)) replaced++;
	}
	else
	{
		for (replaced; replaced < count; replaced++)
		{
			if (!replaceex(self, ch, rpl)) break;
		}
	}
	return replaced;
}
int replaceall(PCString self, char ch, char rpl)
{
	return replacemulti(self, ch, rpl, -1);
}
//REGION END @EDIT

//REGION @INIT_DESTROY
void csdestroy(PCString self)
{
	free(self);
	self = NULL;
}
PCString cstring(const char* str)
{
	PCString cstr = malloc(sizeof(CString));
	if (cstr)
	{
		int len = length(str);

		cstr->str = malloc(len + 1);
		cstr->length = len;
		cstr->ToUpper = toupperex;
		cstr->ToLower = tolowerex;
		cstr->Capitalize = capitalizeex;
		cstr->Free = csdestroy;
		cstr->Find = findchrex;
		cstr->FindInd = findiex;
		cstr->Capall = capall;
		cstr->Swap = swap;
		cstr->Remove = removeex;
		cstr->RemoveMulti = removemulti;
		cstr->RemoveAll = removeall;
		cstr->Replace = replaceex;
		cstr->ReplaceMulti = replacemulti;
		cstr->ReplaceAll = replaceall;

		char* p = cstr->str;
		while (*str)
			*p++ = *str++;
		*p = '\0';
		return cstr;
	}
	free(cstr);
	return NULL;
}
//REGION END @INIT_DESTROY
