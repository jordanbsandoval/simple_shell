#include "Shell.h"

/**
 * Counter_Word - Word count program
 * @String: Array of characters to analyze.
 * Return: Returns the number of words.
 */

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

/**
 * _Fork - Function that creates a second process.
 * @argv: Contains the path and arguments passed to the program.
 * Return: Returns the status of the second program.
 */

int _Fork(char **argv)
{
	pid_t child_pid  = 0;
	int status       = 0;

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

	return (status);
}

/**
 * Match_Path - Function to find out whether or not there is a path written in
 *              the passed string.
 * @Command_Or_Path: First argument written in terminal.
 * @list: It contains the data structure, where are the paths to analyze.
 * Return: Return the command complete or null if it finds the path or not.
 */

char *Match_Path(char *Command_Or_Path, List *list)
{
	Element *element = list->Head;

	while (element)
		if (list->Match(element->Path, Command_Or_Path))
			element = element->Next;
		else
			return (Command_Or_Path);

	return (NULL);
}

/**
 * _strcat - String that copies a string passed to me.
 * @element: Node passed to the function, which contains the path to paste.
 * @Command: Command also to paste.
 * Return: I return null or the full Path.
 */

char *_strcat(Element *element, char *Command)
{
	int Length1  = 0;
	char *Path   = NULL;
	int i = 0, j = 0;

	while (Command[Length1])
		Length1++;
	Length1 += 2;
	Length1 += element->Length_Path;

	if (Length1)
		Path = (char *)malloc(sizeof(char) * Length1);
	else
		return (NULL);

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
	return (Path);
}

/**
 * Analizar_String - Function that analyzes the string passed.
 * @String_Character: Past string.
 * @list: Data structure.
 */

void Analizar_String(char *String_Character, List *list)
{
	int Number_Word = Counter_Word(String_Character);
	int Index       = 1;
	char **argv     = NULL;
	char *Temp      = NULL;

	if (!Number_Word)
		return;
	argv = (char **)malloc(sizeof(char *) * (Number_Word + 1));
	if (!argv)
		return;
	*argv = strtok(String_Character, " \n\t");
	while (Index < Number_Word)
		argv[Index++] = strtok(NULL, " \n\t");
	Temp = *argv;
	Temp = Match_Path(*argv, list);
	if (Temp)
		_Fork(argv);
	else
	{
		Element *element  = list->Head;
		char *Temp_String = NULL;
		struct stat st;

		while (element)
		{
			Temp_String = _strcat(element, *argv);
			if (stat(Temp_String, &st) == 0)
			{
				list->Execve(Temp_String, argv);
				free(Temp_String);
				break;
			}
			free(Temp_String);
			element = element->Next;
		}
		if (!element)
			hand_error(Counter_Error, argv);
	}
	free(argv);
}
