#include "shell.h"

/**
 * _which - fleshes out command by appending it to a matching PATH directory
 * @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
 * @env: environmental variable
 * Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
 */
char *_which(char *str, list_t *env)
{
	char *pah, *cat = NULL, **tok;
	int j = 0;

	
	pah = get_env("PATH", env);
	tok = c_str_tok(pah, ":");
	free(pah);

	
	j = 0;
	while (tok[j] != NULL)
	{
		if (tok[j][0] == '\0')
			cat = getcwd(cat, 0);
		else
			cat = _strdup(tok[j]);
		cat = _strcat(cat, "/");
		cat = _strcat(cat, str);
		if (access(cat, F_OK) == 0)
		{
			free_double_ptr(tok);
			return (cat);
		}
		free(cat); 
		j++;
	}
	free_double_ptr(tok);
	return (str);
}
