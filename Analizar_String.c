#include "Shell.h"

int Counter_Word(char *String)
{
	int Number_Word = 0;
	int State       = 1;

	while (*String)
	{
		if (*String == '\n' || *String == '\t' || *String == ' ')
			State = 1;
		else
			if (State == 1)
				Number_Word++, State = 0;
		String++;
	}
	return (Number_Word);
}

int _Fork(char **argv)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
		execve(*argv, argv, NULL);
	else
		wait(&status);
	return (0);
}

char *Match_Path(char *Command_Or_Path, List *list)
{
	Element *element = list->Head;

	while (element)
	{
		if (!(list->Match(element->Path, Command_Or_Path)))
			return (Command_Or_Path);
		element = element->Next;
	}
	return (NULL);
}

char *_strcat(Element *element, char *Command)
{
	int Length1 = 0;
	char *Path;
	int i = 0, j = 0;

	while (Command[Length1])
		Length1++;
	Length1 += 2;
	Length1 += element->Length_Path;

	Path = (char *)malloc(sizeof(char) * Length1);

	while (i < Length1)
	{
		if (i < element->Length_Path)
			Path[i] = (element->Path)[i];
		else if (i == element->Length_Path)
			Path[i] = '/';
		else
			Path[i] = Command[j++];
		i++;
	}
	Path[i] = '\0';
	return (Path);
}

void Analizar_String(char *String_Character, List *list)
{
	int Number_Word = Counter_Word(String_Character);
	int Index       = 1;
	char **argv     = (char **)malloc(sizeof(char *) * (Number_Word + 1));
	char *Temp;

	if (!argv)
		return ;
	*argv = strtok(String_Character, " \n\t");
	while (Index < Number_Word)
		argv[Index++] = strtok(NULL, " \n\t");

	Temp = *argv;
	if (Temp = Match_Path(*argv, list))
		_Fork(argv);
	else
	{
		Element *element = list->Head;
		char *Temp_String;
		struct stat st;

		while (element)
		{
			Temp_String = _strcat(element, *argv);
			list->Execve(Temp_String, argv);
			free(Temp_String);
			element = element->Next;
		}
	}
	free (argv);
}
