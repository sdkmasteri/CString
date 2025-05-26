#ifndef CSTRING_H
#define CSTRING_H
#include <windows.h>

#ifdef CSTR_DBG
#include <stdio.h>
#endif // CSTR_DBG

typedef struct CString CString, * PCString;
struct CString
{
	char*	str;
	size_t	length;

	void	(*ToUpper)(PCString);
	void	(*ToLower)(PCString);
	void	(*Capitalize)(PCString);
	void	(*Capall)(PCString);
	void	(*Free)(PCString);
	char*	(*Find)(PCString, char);
	int		(*FindInd)(PCString, char);
	BOOL	(*Swap)(PCString, PCString);
	BOOL	(*Remove)(PCString, char);
	int		(*RemoveMulti)(PCString, char, int);
	int		(*RemoveAll)(PCString, char);
	BOOL	(*Replace)(PCString, char, char);
	int		(*ReplaceMulti)(PCString, char, char, int);
	int		(*ReplaceAll)(PCString, char, char);
};

PCString cstring(const char* str);
PCString duple(PCString);
PCString makeptr(PCString);

#define UPTEXT(cstr) cstr->ToUpper(cstr);
#define LOWTEXT(cstr) cstr->ToLower(cstr);
#define CAPTEXT(cstr) cstr->Capitalize(cstr);
#define CAPALLTEXT(cstr) cstr->Capall(cstr);

#endif // CSTRING_H
