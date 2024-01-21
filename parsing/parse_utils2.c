#include "parse.h"

void		ft_addnewlst_back(t_obj **alst)
{
	t_obj	*begin;
	t_obj	*elem;
	t_obj	*list;

	begin = *alst;
	list = *alst;
	elem = malloc(sizeof(t_obj));
    if (!elem)
        error_message("Error malloc failure in new list\n");
	elem->next = NULL;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = elem;
	}
	else
		begin = elem;
	*alst = begin;
}

int			stoi(char **str)
{
	int i;
	int	neg;

	i = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
		i = i * 10 + (*((*str)++) - '0');
	next(str);
	return (i * neg);
}

void		in_range(double nb, double min, double max, char *function)
{
	char	message[100];

	if (nb < min || nb > max)
	{
		ft_strncpy(message, function, 76);
		ft_strcat(message, " parameter out of range\n");
		error_message(message);
	}
}

int			parse_color(char **str)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	r |= stoi(str);
	in_range(r, 0, 255, "colors must be in range [0, 255],");
	r <<= 16;
	comma(str);
	g |= stoi(str);
	in_range(g, 0, 255, "colors must be in range [0, 255],");
	g <<= 8;
	comma(str);
	b |= stoi(str);
	in_range(b, 0, 255, "colors must be in range [0, 255],");
	return (r | g | b);
}