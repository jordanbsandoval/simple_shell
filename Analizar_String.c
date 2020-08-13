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
void Analizar_String(char *String_Character, List *list)
{
	int Number_Word = Counter_Word(String_Character);
	int Index       = 1;
	char **argv     = (char **)malloc(sizeof(char *) * (Number_Word + 1));

	if (!argv)
		return ;
	*argv = strtok(String_Character, " \n\t");
	while (Index < Number_Word)
		argv[Index++] = strtok(NULL, " \n\t");

	_Fork(argv);
	free (argv);
}
