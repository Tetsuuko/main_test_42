/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:21:02 by ldoyen--          #+#    #+#             */
/*   Updated: 2023/11/28 10:38:06 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "printf/includes/printf.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	char	*c3 = "Salut les amis de 42!";
	int	myft;
	int	cft;
	
	printf("* TEST CHAR *\n\n");
	myft = ft_printf("%s ok %c%c\n %ssal%%%%ut%%%s%s%s\n", "\0", 'X', 'Y', (char *)NULL, "coucou", "\n", "");
	cft = printf("%s ok %c%c\n %ssal%%%%ut%%%s%s%s\n", "\0", 'X', 'Y', (char *)NULL, "coucou", "\n", "");
	printf("My ft = %d\n", myft);
	printf("Cft = %d\n\n", cft);

	printf("* TEST MIXT id *\n\n");
	myft = ft_printf("%d ok ok %i %d %i %d %i\n", -2147483647, -214783647, 0, 0, 2147483647, 2147483647);
	cft = printf("%d ok ok %i %d %i %d %i\n", -2147483647, -214783647 + 1, 0, 0, 2147483647, 2147483647);
	printf("My ft = %d\n", myft);
	printf("Cft = %d\n\n", cft);

	printf("* TEST MIXT uxX *\n\n");
	myft = ft_printf("%u %u %x %X\n", -1, -1, -1, -1);
	cft = printf("%u %u %x %X\n", -1, -1, -1, -1);
	printf("My ft = %d\n", myft);
	printf("Cft = %d\n\n", cft);

	printf("* TEST p *\n\n");
	myft = ft_printf("%p %p\n", c3, NULL);
	cft = printf("%p %p\n", c3, NULL);
	printf("My ft = %d\n", myft);
	printf("Cft = %d\n\n", cft);

	printf("* TEST null format *\n\n");
	myft = ft_printf(NULL);
	//cft = printf(NULL);
	printf("My ft = %d\n", myft);
	//printf("Cft = %d\n\n", cft);

	printf("* TEST empty *\n\n");
	myft = ft_printf("");
	cft = printf("");
	printf("My ft = %d\n", myft);
	printf("Cft = %d\n\n", cft);

	printf("* TEST min id *\n\n");
	myft = ft_printf("%d\n%i\n", -214783648, -214783648);
	printf("My ft = %d\n", myft);

	return (0);
}

