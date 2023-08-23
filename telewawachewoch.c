#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @p: address of current position in buf
 * @mereja: the parameter struct
 * @buf: the char buffer
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(mereja_t *mereja, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		mereja->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		mereja->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		mereja->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * meyayaze - checks we should continue chaining based on last status
 * @buf: the char buffer
 * @i: starting position in buf
 * @len: length of buf
 * @mereja: the parameter struct
 * @p: address of current position in buf
 * Return: Void
 */
void meyayaze(mereja_t *mereja, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (mereja->cmd_buf_type == CMD_AND)
	{
		if (mereja->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (mereja->cmd_buf_type == CMD_OR)
	{
		if (!mereja->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @mereja: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(mereja_t *mereja)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(mereja->alias, mereja->argv[0], '=');
		if (!node)
			return (0);
		free(mereja->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		mereja->argv[0] = p;
	}
	return (1);
}

/**
 * replace_telewawachewoch - replaces telewawachewoch in the tokenized string
 * @mereja: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_telewawachewoch(mereja_t *mereja)
{
	int i = 0;
	list_t *node;

	for (i = 0; mereja->argv[i]; i++)
	{
		if (mereja->argv[i][0] != '$' || !mereja->argv[i][1])
			continue;

		if (!_strcmp(mereja->argv[i], "$?"))
		{
			replace_string(&(mereja->argv[i]),
					_strdup(wede_quter(mereja->status, 10, 0)));
			continue;
		}
		if (!_strcmp(mereja->argv[i], "$$"))
		{
			replace_string(&(mereja->argv[i]),
					_strdup(wede_quter(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(mereja->env, &mereja->argv[i][1], '=');
		if (node)
		{
			replace_string(&(mereja->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&mereja->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
