/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:01:12 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/03 02:03:07 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_whitespace_and_sign(const char **str, int *sign)
{
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign *= -1;
		(*str)++;
	}
}

static int	get_base(const char **str, int base)
{
	if (base == 0)
	{
		if (**str == '0')
		{
			(*str)++;
			if (ft_tolower(**str) == 'x')
				base = 16;
			else
				base = 8;
		}
		else
			base = 10;
	}
	else if (base == 16 && (**str == '0' && ft_tolower(*(*str + 1)) == 'x'))
		(*str) += 2;
	return (base);
}

static int	get_digit_value(char c, int base)
{
	int	value;

	if (ft_isdigit(c))
		value = c - '0';
	else if (ft_isalpha(c))
		value = ft_tolower(c) - 'a' + 10;
	else
		return (-1);
	if (value >= base)
		return (-1);
	return (value);
}

static int	check_overflow(long res, int digit, int base, int sign)
{
	if (res > (LONG_MAX - digit) / base)
	{
		if (sign == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	res;
	int		sign;
	int		digit;
	int		overflow;

	res = 0;
	sign = 1;
	skip_whitespace_and_sign(&str, &sign);
	base = get_base(&str, base);
	while (1)
	{
		digit = get_digit_value(*str, base);
		if (digit == -1)
			break ;
		overflow = check_overflow(res, digit, base, sign);
		if (overflow == 1)
			return (LONG_MAX);
		else if (overflow == -1)
			return (LONG_MIN);
		res = res * base + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (res * sign);
}
