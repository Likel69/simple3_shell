#include "shell.h"

/**
 * add_node - should add a node to beginning of the list
 * @head: address of pointer to head node, top
 * @str: the string of the node in question
 * @num: node idx
 *
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
	{
		return (NULL);
	}
	
	new_header = malloc(sizeof(list_t));

	if (!new_header)
	{
		return (NULL);
	}
	
	_memset((void *)new_header, 0, sizeof(list_t));
	new_header->num = num;

	if (str)
	{
		new_header->str = _strdup(str);

		if (!new_header->str)
		{
			free(new_header);

			return (NULL);
		}
	}

	new_header->next = *head;
	*head = new_header;

	return (new_header);
}

/**
 * add_node_end - will add a node to the back end of list
 * @head: address of point to head (front) node
 * @str: the string of the nod
 * @num: node index used by history
 *
 * Return: should return size of list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *mynode;

	if (!head)
	{
		return (NULL);
	}
	
	mynode = *head;
	new_node = malloc(sizeof(list_t));

	if (!new_node)
	{
		return (NULL);
	}
	
	_memset((void *)new_node, 0, sizeof(list_t));
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

	if (mynode)
	{
		while (mynode->next)
		{
			mynode = mynode->next;
		}
		
		mynode->next = new_node;
	}

	else
	{
		*head = new_node;
	}
	
	return (new_node);
}

/**
 * print_list_str - should spit out just the str element of a list_t linked list
 * @h: will point to the first node
 *
 * Return: size of list
 */

size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");

		h = h->next;
		i++;
	}

	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **head, unsigned int index)
{

	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
	{
		return (0);
	}
	
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
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: should give us a void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;
	
	if (!head_ptr || !*head_ptr)
	{
		return;
	}
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

