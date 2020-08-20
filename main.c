#include "Shell.h"

/**
 * Match - Function to check if the Path variable matches the second argument.
 *         of the function.
 * @Path: Variable to check if it matches the viable Key1.
 * @Key1: Data that is analyzed if it matches or not with path.
 * Return: Returns 0 on success, 1 otherwise.
 */

int
Match(char *Path, char *Key1)
{
	while (*Path)
		if (*Path == *Key1)
			Path++, Key1++;
		else
			break;
	if (*Path)
		return (1);
	else
		return (0);
}

/**
 * Destroy - Function to destroy the data inserted in the Path variable
 *           found in.
 *           the structure, structure Element_
 * @PATH: Function that destroys dynamically allocated memory in Path.
 */

void
Destroy(char *PATH)
{
	free(PATH);
}

/**
 * Execve - Function that creates a child by calling fork to be able to execute
 *          the command (written without the path in the terminal).
 * @Path: Non-relative path passed as the first argument, in order to correctly
 *        execute the execve function.
 * @argv: A double pointer that points to an array of pointers,
 *        containing the command and arguments passed from the termianl.
 * Return: Returns 0 on success, 1 otherwise.
 */

int
Execve(char *Path, char **argv)
{
	pid_t child_pid = 0;
	int status      = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid)
		wait(&status);
	else
		return (execve(Path, argv, NULL));
	return (status);
}

/**
 * Handle_Sigint - ctrl + c implementacion
 * @Status: status.
 */

void Handle_Sigint(int Status)
{
	Status = Status;
	write(STDOUT_FILENO, "\n$ ", 3);
	fflush(stdout);
}

/**
 * main - shell program.
 * @argc: Number of parameters passed to the shell.
 * @argv: parameters passed to shell
 * Return: 0.
 */

int main(void)
{
	List list;
	size_t Counter_Character = 0;
	char *String_Character = NULL;
	int Status = 0;

	List_Init(&list, Destroy, Execve, Match);
	Get_Path(&list);

	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "$ ", 2);
	signal(SIGINT, Handle_Sigint);
	while (getline(&String_Character, &Counter_Character, stdin) != EOF)
	{
		Counter_Error++;
		Status = Analizar_String(String_Character, &list);
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "$ ", 2);
		free(String_Character), String_Character  = NULL;
		Counter_Character = 0;
	}
	free(String_Character), List_Destroy(&list);
	if (isatty(STDIN_FILENO) == 1)
		write(1, "\n", 1);
	if (Status == 512)
		Status = 2;
	_exit(Status);
}
