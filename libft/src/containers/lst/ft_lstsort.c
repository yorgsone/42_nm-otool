#include "../../../include/libft.h"

static void lst_swap(t_list *lst1, t_list *lst2)
{
	void *content_tmp;
	size_t content_size_tmp;

	content_tmp = lst1->content;
	content_size_tmp = lst1->content_size;
	lst1->content = lst2->content;
	lst1->content_size = lst2->content_size;
	lst2->content = content_tmp;
	lst2->content_size = content_size_tmp;
}

void ft_lstsort(t_list *lst, u_int8_t reverse, int (*f)(t_list *lst1, t_list *lst2, u_int8_t))
{
	t_list *to_replace;
	t_list *el;
	t_list *min;

	to_replace = lst;
	while (to_replace && to_replace->next)
	{
		min = NULL;
		el = to_replace;
		while (el)
		{
			if (!min || (*f)(min, el, reverse))
				min = el;
			el = el->next;
		}
		if (min && to_replace != min)
			lst_swap(to_replace, min);
		to_replace = to_replace->next;
	}
}