#include "shell.h"

/**
 * ctrl_c - ignore Ctrl-C input and prints prompt again
 * @n: takes in int from signal
 */
void ctrl_c(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * built_in - handles builtins (exit, env, cd)
 * @token: user's typed command
 * @env: environmental variable
 * @num: take in nth user command typed to write error message
 * @command: bring in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int built_in(char **token, list_t *env, int num, char **cmd)
{
	int i = 0;
	if (_strcmp(token[0], "exit") == 0)
	{
		i = __exit(token, env, num, cmd);
	}
	else if (_strcmp(token[0], "env") == 0)
	{
		_env(token, env);
		i = 1;
	}
	else if (_strcmp(token[0], "cd") == 0)
	{
		i = _cd(token, env, num);
	}
	else if (_strcmp(token[0], "setenv") == 0)
	{
		_setenv(&env, token);
		i = 1;
	}
	else if (_strcmp(token[0], "unsetenv") == 0)
	{
		_unsetenv(&env, token);
		i = 1;
	}
	return (i);
}

/**
 * ignore_space - return string without spaces in front
 * @str: string
 * Return: new string
 */
char *ignore_space(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read via get_line
 * @command: user's typed in command
 * @env: environmental variable linked list
 */
void ctrl_D(int i, char *cmd, list_t *env)
{
	if (i == 0) 
	{
		free(cmd);
		free_linked_list(env);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * prompt - repeatedly prompts user and executes user's cmds if applicable
 * @en: envrionmental variables
 * Return: 0 on success
 */
int prompt(char **en)
{
	list_t *env;
	size_t i = 0, n = 0;
	int cmd_line_no = 0, exit_stat = 0;
	char *cmd, *n_cmd, **token;

	env = env_linked_list(en);
	do {
		cmd_line_no++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		else
			n_interactive(env);
		signal(SIGINT, ctrl_c);
		cmd = NULL; i = 0;
		i = get_line(&cmd);
		ctrl_D(i, cmd, env);
		n_cmd = cmd;
		cmd = ignore_space(cmd);
		n = 0;
		while (cmd[n] != '\n')
			n++;
		cmd[n] = '\0';
		if (cmd[0] == '\0')
		{
			free(n_cmd); continue;
		}
		token = NULL; token = _str_tok(cmd, " ");
		if (n_cmd != NULL)
			free(n_cmd);
		exit_stat = built_in(token, env, cmd_line_no, NULL);
		if (exit_stat)
			continue;
		exit_stat = _execve(token, env, cmd_line_no);
	} while (1);
	return (exit_stat);
}
