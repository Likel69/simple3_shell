#include "shell.h"

/**
 * input_buf - input buffers the chained commands
 * @info: the structure of the parameter
 * @buf: location of buffer
 * @len: location of len var
 *
 * Return: should return the bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t j = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		j = getline(buf, &len_p, stdin);
#else
		j = _getline(info, buf, &len_p);
#endif
		if (j > 0)
		{
			if ((*buf)[j - 1] == '\n')
			{
				(*buf)[j - 1] = '\0';
				j--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = j;
				info->cmd_buf = buf;
			}
		}
	}
	return (j);
}

/**
 * get_input - gets a line minus the newline
 * @info: the parameter structure
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, u, len;
	ssize_t j = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	j = input_buf(info, &buf, &len);
	if (j == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		u = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &u, i, len);
		while (u < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &u))
				break;
			u++;
		}

		i = u + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* otherwise if  not a chain, pass back buffer from _getline() */
	return (j); /* give us back the len of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: will return us j
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t j = 0;

	if (*i)
		return (0);
	j = read(info->readfd, buf, READ_BUF_SIZE);
	if (j >= 0)
		*i = j;
	return (j);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: the parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t j = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	j = read_buf(info, buf, &len);
	if (j == -1 || (j == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* THE MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: should return us the void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

