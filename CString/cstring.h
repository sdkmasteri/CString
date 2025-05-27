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
	void	(*Append)(PCString, const char*);
	void	(*Merge)(PCString, PCString);
	void	(*Insert)(PCString, char, int);
	BOOL	(*Compare)(PCString, PCString);
	BOOL	(*Contain)(PCString, const char*);
	int		(*ToInt)(PCString);
	int		(*FindInt)(PCString);
	char*	(*Start)(PCString);
	char*	(*End)(PCString);
};

PCString cstring(const char* str);
PCString duple(PCString);
PCString makeptr(PCString);

#define UPCSTR(cstr) cstr->ToUpper(cstr);
#define LOWCSTR(cstr) cstr->ToLower(cstr);
#define CAPCSTR(cstr) cstr->Capitalize(cstr);
#define CAPALLCSTR(cstr) cstr->Capall(cstr);
#define FREECSTR(cstr) cstr->Free(cstr);
#define TOINTCSTR(cstr) cstr->ToInt(cstr);
#endif // CSTRING_H
