/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:25:56 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/21 14:47:12 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"

typedef enum	e_tokentype{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	IO_NUMBER = -2,
	TOKEN = -1,
}				t_token_type;

typedef enum	e_token_state{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
}				t_token_state;

typedef struct s_token	t_token;

struct			s_token
{
	t_token			*next;
	t_token			*prev;
	t_token_type	type;
	char			*data;
};
void			del_token(t_token **token_p);
void			del_token_list(t_token **token_p);
t_token_type	judge_token_type(char c);
t_token			*token_init(size_t len, t_token *prev);

#endif
