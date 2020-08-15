#include "Shell.h"

/**
 * _strlen -  function
 * @s: The number to be checked
 *
 * Return: returns the length of a string.
 */
int _strlen(char *s)
{
	int contador = 0;

	while (s && s[contador] != '\0')
	{
		contador++;
	}
	return (contador);
}

int error_print(char c);

/**
 * hand_error - compose the standar error message
 * @argv: double pointer with arguments from input
 * @error_counter: prompt counter
 */
void hand_error(int error_counter, char **argv)
{
	int multi = 1, number = 1, copy = 0;

	write(STDERR_FILENO, "hsh", 3);
	write(STDERR_FILENO, ": ", 2);

	copy = error_counter;

	while (copy >= 10)
	{
		copy = copy / 10;
		multi = multi * 10;
		number++;
	}
	while (number > 1)
	{
		if ((error_counter / multi) < 10)
			error_print((error_counter / multi + '0'));
		else
			error_print((error_counter / multi) % 10 + '0');
		number--;
		multi = multi / 10;
	}
	error_print(error_counter % 10 + '0');
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}
/**
 *error_print - sends char to write
 *@c: char to be printed
 *Return: to print
 */
int error_print(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}
