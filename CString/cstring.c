#include "cstring.h"

//REGION @UTILS

//since char is 1 byte long we can just use pointer diff to calc length
size_t length(char* str)
{
	char* ptr = str;
	while (*++ptr);
	return ptr - str;
}
char* findchr(char* str, char ch)
{
	int i = findi(str, ch);
	return i >= 0 ? (char*)(str + i) : NULL;
}
char* findbetween(char* str, char ch1, char ch2)
{
	for (int i = 0;; i++)
	{
		if (*(str + i) == '\0') break;
		if (*(str + i) >= ch1 && *(str + i) <= ch2) return (char*)(str + i);
	}
	return NULL;
}
int findiex(PCString self, char ch)
{
	return findi(self->str, ch);
}
char* findchrex(PCString self, char ch)
{
	return findchr(self->str, ch);
}

char* startex(PCString self)
{
	return self->str;
}

char* endex(PCString self)
{
	return self->str + self->length;
}
//REGION END @UTILS

//REGION @CASE
void toupperex(PCString self)
{
	do {
		if (*self->str >= 'a' && *self->str <= 'z')
			*self->str -= 32;
	} while (*self->str++);
	self->str -= self->length + 1;
}
void tolowerex(PCString self)
{
	do {
		if (*self->str >= 'A' && *self->str <= 'Z')
			*self->str += 32;
	} while (*self->str++);
	self->str -= self->length + 1;
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
	if (!tmp)
	{
		free(tmp);
		return FALSE;
	}

	tmp->str = self->str;
	tmp->length = self->length;

	self->str = csptr->str;
	self->length = csptr->length;

	csptr->str = tmp->str;
	csptr->length = tmp->length;
	free(tmp);
	return TRUE;
}

PCString duple(PCString cstr)
{
	PCString ptr = cstring(cstr->str);
	return ptr;
}
PCString makeptr(PCString cstr)
{
	char* ptr = malloc(sizeof(CString));
	if (!ptr)
	{
		free(ptr);
		return NULL;
	}

	char* csptr = (char*)cstr;

	for (int i = 0; i < sizeof(CString); i++)
		ptr[i] = csptr[i];

	return (PCString)ptr;
}

void mergeex(PCString self, PCString cstr)
{
	self->Append(self, cstr->str);
	FREECSTR(cstr)
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

	self->str = realloc(self->str, self->length--);
	//self->str = result;

	return TRUE;
}

int removemulti(PCString self, char ch, int count)
{
	int removed = 0;
	if (count <= 0)
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
	return removemulti(self, ch, 0);
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
	if (count <= 0)
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
	return replacemulti(self, ch, rpl, 0);
}

void insertex(PCString self, char ch, int ind)
{
	if (ind < 0 || ind > self->length) return;
	self->length++;
	char* ptr = malloc(self->length + 2);
	if (!ptr)
	{
		free(ptr);
		return;
	}
	char* ptr1 = ptr;

	for (int i = 0; i < self->length; i++)
	{
		if (i == ind)
			*ptr1++ = ch;
		*ptr1++ = self->str[i];
	}
	*ptr1 = '\0';
	free(self->str);
	self->str = ptr;
}
void appendex(PCString self, const char* str)
{
	int len = length(str);
	char* ptr = realloc(self->str, self->length + len + 1);
	if (!ptr)
	{
		free(ptr);
		return NULL;
	}
	self->str = ptr;
	ptr += self->length;
	for (int i = 0; i < len; i++)
	{
		*ptr++ = str[i];
	}
	*ptr = '\0';
	self->length += len;
}
//REGION END @EDIT

//REGION @TEST
BOOL cmpstr(const char* str1, const char* str2)
{
	//if (*str1 != *str2) return FALSE;
	const unsigned char* p1 = (const unsigned char*)str1;
	const unsigned char* p2 = (const unsigned char*)str2;
	for (; *p1 && *p1 == *p2; ++p1, ++p2);

	return (!*p1) || (*p1 == *p2);
}
BOOL cmpstrex(PCString self, PCString cstr)
{
	return cmpstr(self->str, cstr->str);
}
BOOL contain(PCString self, const char* str)
{
	char* ptr = findchrex(self, *str);
	if (!ptr)
	{
		free(ptr);
		return FALSE;
	}
	while (ptr != NULL)
	{
		if (cmpstr(str, ptr))
		{
			return TRUE;
		}
		ptr = findchr((char*)(ptr+1), *str);
	}
	return FALSE;
}
//REGION END @TEST

//REGION @CAST
int toint(PCString self)
{
	int result = 0;
	char* ptr = self->str;
	if (*ptr == '-') ptr++;
	if (*ptr < '0' || *ptr > '9') return 0;
	for (;;)
	{
		if (*ptr < '0' || *ptr > '9') break;
		result = result * 10 + (*ptr - '0');
		ptr++;
	}
	if (*(self->str) == '-') result = -result;
	return result;
}

int findintex(PCString self)
{
	int result = 0;
	char* ptr = findbetween(self->str, '0', '9');
	if (ptr == NULL) return 0;

	int x = 1;
	if (*(ptr - 1) == '-') x = -x;
	for (;;)
	{
		if (*ptr < '0' || *ptr > '9') break;
		ptr++;
	}
	while (ptr--)
	{
		if (*ptr < '0' || *ptr > '9') break;
		result += (*ptr - '0') * x;
		x *= 10;
	}
	return result;
}

//REGION END @CAST

//REGION @INIT_DESTROY
void csdestroy(PCString self)
{
	free(self);
	self = NULL;
}
PCString cstring(const char* str)
{
	PCString cstr = malloc(sizeof(CString));
	if (cstr && *str)
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
		cstr->Append = appendex;
		cstr->Merge = mergeex;
		cstr->Insert = insertex;
		cstr->Compare = cmpstrex;
		cstr->Contain = contain;
		cstr->ToInt = toint;
		cstr->FindInt = findintex;
		cstr->Start = startex;
		cstr->End = endex;

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
