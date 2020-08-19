#include "Shell.h"

/**
 * Data_Path - Create a string with a specific path where the s.o
 *             executables are located
 * @Temp_Environ: Pointer to the PATH environment variable.
 * Return: Returns an absolute path.
 */

char *
Data_Path(char **Temp_Environ)
{
	char *temp;
	int counter = 1;   /*
			    * Para incluir el caracter '\0'.
			    */
	int index = 0;

	while ((*Temp_Environ)[index] != ':' && (*Temp_Environ)[index])
		counter++, index++;

	temp = (char *)malloc(sizeof(char) * counter);

	if (!temp)
		return (NULL);

	index = 0;
	while (*(*Temp_Environ) != ':' && **(Temp_Environ))
		temp[index++] = *(*Temp_Environ)++;
	if (**Temp_Environ == ':')
		(*Temp_Environ)++;
	temp[index] = '\0';
	return (temp);
}
