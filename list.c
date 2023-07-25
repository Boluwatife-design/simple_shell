#include "shell.h"

/**
 * _lentlist-calculate length of linked list
 * @p: pointer to first node
 * Return: size of list
 */
size_t _lentlist(const list_t *p)
{
	size_t i = 0;

	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}
/**
 * lst_tostr-returns array of strings of the list
 * @head: pointer to first node
 * Return: array of strings
 */
char **lst_tostr(list_t *head)
{
	list_t *node = head;
	size_t i = _lentlist(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * pull_list-pull all elements of a list_t linked list
 * @p: pointer to first node
 * Return: size of list
 */
size_t pull_list(const list_t *p)
{
	size_t i = 0;

	while (p)
	{
		_puts(convert_number(p->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		i++;
	}
	return (i);
}

/**
 * begin_node-prints node whose string begin with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *begin_node(list_t *node, char *prefix, char c)
{
	char *h = NULL;

	while (node)
	{
		h = begin_with(node->str, prefix);
		if (h && ((c == -1) || (*h == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * _node_index-gets index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t _node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
