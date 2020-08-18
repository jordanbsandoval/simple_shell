#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 *  Macros.
 */

int
Match(char *Path, char *Key1);

#define Posicionar_Path(environ)		\
	while ((*environ))			\
		if (!(Match("PATH", *environ)))	\
			break;			\
		else				\
			(environ)++;

#define Posicionar_Environ(environ)		\
	while (*(*environ)++ != '=');

#define Length_PATH(element, Length)			\
	while (((element)->Path)[Length])		\
		(Length)++;

#define print_variable_Envarioment(Temp)	\
	while (*Temp)				\
		printf("%s\n", *Temp++);

#define Verificador_String(String)					\
	((String) == '\n' || (String) == '\t' || (String) == ' ')

/*
 *  Variable environ.
 */

extern char **environ;
int Counter_Error;

/**
 * struct Element_ - This structure in the data structure represents
 *                   the nodes or elements of the linked list that will be
 *                   created.
 *
 * @Path: Contains the string of one of the paths found in the Path
 *        environment variable.
 * @Length_Path: Corresponds to the number of visible characters found in Path.
 * @Next: Points to the next node in the data structure.
 */

struct Element_
{
	char *Path;
	int  Length_Path;
	struct Element_ *Next;
};

/**
 * struct List_ - Structure that points to the created nodes that are linked.
 *
 * @Size_List: Corresponds to the number of nodes created in the
 *             data structure.
 * @Tail: Pointer to the last node.
 * @Head: Pointer pointing to the first node.
 * @Destroy: Pointer to a Destroy function.
 * @Execve: Pointer to a Execve function.
 * @Match:  Pointer to a Match function.
 */

struct List_
{
	int Size_List;
	struct Element_ *Head;
	struct Element_ *Tail;
	void (*Destroy)(char *Path);
	int (*Execve)(char *Path, char **argv);
	int (*Match)(char *key1, char *key2);
};

typedef struct Element_ Element;
typedef struct List_    List;

/*
 *  Funciones.
 */

void
hand_error(int error_counter, char **argv);

void
Analizar_String(char *String_Character, List *list);

char *
Data_Path(char **Temp_Environ);

void
Get_Path(List *list);

int
Ins_Next_Element(List *list, Element *element, char *Path);

void
List_Init(List *list, void (*Destroy)(char *Path), int (*Execve)(char *Path, char **argv), int (*Match)(char *Key1, char *Key2));

int
Rem_Nex_Element(List *list, Element *element, char **Path);

void
List_Destroy(List *list);

void
Analizar_String_Character(char *String, List *list);

#endif
