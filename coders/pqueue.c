/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:34:23 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 15:34:23 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pqueue.h"

t_pqueue	*pq_create(int capacity)
{
	t_pqueue		*pqueue;
	t_pqueue_node	*nodes;

	pqueue = malloc(sizeof(t_pqueue));
	nodes = malloc(sizeof(t_pqueue_node) * capacity);
	if (!pqueue || !nodes)
	{
		free(pqueue);
		free(nodes);
		return (NULL);
	}
	pqueue->size = 0;
	pqueue->capacity = capacity;
	pqueue->node = nodes;
	return (pqueue);
}

t_pqueue	*pq_destroy(t_pqueue *pqueue)
{
	if (pqueue)
	{
		free(pqueue->node);
		free(pqueue);
	}
	return (NULL);
}

// Push a coder into the priority queue with the given priority 
// (i - 1)/2 parent index
int	pq_push(t_pqueue *pqueue, t_coder *coder, long priority)
{
	t_pqueue_node	tmp;
	int				i;

	if (pqueue->size >= pqueue->capacity)
		return (1);
	pqueue->node[pqueue->size].coder = coder;
	pqueue->node[pqueue->size].priority = priority;
	pqueue->size++;
	i = pqueue->size - 1;
	while (i > 0 && pqueue->node[i].priority < pqueue->node[
			(i - 1) / 2].priority)
	{
		tmp = pqueue->node[i];
		pqueue->node[i] = pqueue->node[(i - 1) / 2];
		pqueue->node[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
	}
	return (0);
}

void	pq_sift_down(t_pqueue *pqueue, int i)
{
	int				size;
	int				smallest;
	t_pqueue_node	tmp;

	size = pqueue->size;
	while (2 * i + 1 < size)
	{
		smallest = 2 * i + 1;
		if (2 * i + 2 < size && pqueue->node[2 * i + 2].priority
			< pqueue->node[2 * i + 1].priority)
			smallest = 2 * i + 2;
		if (pqueue->node[i].priority < pqueue->node[smallest].priority)
			break ;
		else
		{
			tmp = pqueue->node[i];
			pqueue->node[i] = pqueue->node[smallest];
			pqueue->node[smallest] = tmp;
			i = smallest;
		}
	}
}

t_coder	*pq_pop(t_pqueue *pqueue)
{
	t_coder	*coder;
	int		i;

	if (pqueue->size == 0)
		return (NULL);
	coder = pqueue->node[0].coder;
	pqueue->node[0] = pqueue->node[pqueue->size - 1];
	pqueue->size--;
	i = 0;
	pq_sift_down(pqueue, i);
	return (coder);
}
