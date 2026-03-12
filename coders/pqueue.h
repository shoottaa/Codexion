/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:12:07 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 14:12:07 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PQUEUE_H
# define PQUEUE_H

# include "types.h"
# include <stdlib.h>

typedef struct s_coder	t_coder;

typedef struct s_pqueue_node
{
	t_coder	*coder;
	long	priority;
}	t_pqueue_node;

typedef struct s_pqueue
{
	t_pqueue_node	*node;
	int				size;
	int				capacity;
}	t_pqueue;

t_pqueue	*pq_create(int capacity);
t_pqueue	*pq_destroy(t_pqueue *pqueue);

int		pq_push(t_pqueue *pqueue, t_coder *coder, long priority);
t_coder	*pq_pop(t_pqueue *pqueue);

#endif