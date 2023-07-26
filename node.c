#include "shell.h"

/**
 * _putnode-puts a node at the beginning of list
 * @head: address of pointer to head node
 * @str: rep string
 * @num: node index
 * Return: size of list
 */
list_t *_putnode(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_fill((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * _putnodeend-puts a node at the end of the list
 * @head: address of pointer to head node
 * @str: string
 * @num: node index
 * Return: size of list
 */
list_t *_putnodeend(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_fill((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * _printstr-prints only the str element of a linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t _printstr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_sets(h->str ? h->str : "(nil)");
		_sets("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _delnode-deletes node at a given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success,else 0
 */
int _delnode(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * _freelist-frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void _freelist(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
