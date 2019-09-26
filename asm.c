/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:01:44 by nwispmot          #+#    #+#             */
/*   Updated: 2019/09/24 14:01:48 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
void	int_to_hex(int32_t dec, int dir_size, unsigned place);

void    add_token(t_parser *par, t_type type, char *content)
{
	t_token	*new;
	//t_token	*head;

	if (!par->tokens)
	{
		par->tokens = (t_token*)malloc(sizeof(t_token));
		ft_bzero(par->tokens, sizeof(t_token));
		par->tokens->type = type;
		if (content)
			par->tokens->content = ft_strdup(content);
		par->tokens->next = NULL;
		par->head = par->tokens;
	}
	else
	{
//		head = par->tokens;
		while (par->tokens->next)
		{
			par->tokens = par->tokens->next;
		}
		new = (t_token*)malloc(sizeof(t_token));
		ft_bzero(new, sizeof(t_token));
		new->type = type;
		if (content)
			new->content = ft_strdup(content);
		new->next = NULL;
		par->tokens->next = new;
        par->tokens = par->tokens->next;
	}
}

void    add_label(t_parser *par, t_token *token)
{
    t_label *new;
    t_label *head;

    if (!par->labels)
    {
        par->labels = (t_label*)malloc(sizeof(t_label));
        ft_bzero(par->labels, sizeof(t_label));
        par->labels->point = token;
        par->labels->prev = NULL;
        par->labels->next = NULL;
    }
    else
    {
        head = par->labels;
        while (head->next)
        {
//            if (ft_strcmp(head->point->content, token->content) == 0)
//            {
//                head->point = token;
//                return ;
//            }
            head = head->next;
        }
        new = (t_label*)malloc(sizeof(t_label));
        ft_bzero(new, sizeof(t_label));
        new->point = token;
        new->next = NULL;
        head->next = new;
        new->prev = head;
    }
}

void    add_label_token(t_parser *par, char *content)
{
	t_token	*new;
	//t_token	*head;

	if (!par->tokens)
	{
		par->tokens = (t_token*)malloc(sizeof(t_token));
		ft_bzero(par->tokens, sizeof(t_token));
		par->tokens->type = LABEL;
		//par->tokens->row = par->y;
		if (content)
			par->tokens->content = ft_strsub(content, 0, ft_strlen(content) - 1);
		par->tokens->next = NULL;
		par->head = par->tokens;
	}
	else
	{
//		head = par->tokens;
		while (par->tokens->next)
		{
			par->tokens = par->tokens->next;
		}
		new = (t_token*)malloc(sizeof(t_token));
		ft_bzero(new, sizeof(t_token));
		new->type = LABEL;
		if (content)
			new->content = ft_strsub(content, 0, ft_strlen(content) - 1);
		new->next = NULL;
		par->tokens->next = new;
        par->tokens = par->tokens->next;
	}
	add_label(par, par->tokens);
}

int		is_label(char *str, t_parser *par)
{
	int i;
	int len;

	i = -1;

	if (str[len = (ft_strlen(str) - 1)] == LABEL_CHAR)
	{
		while(++i < len)
			if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
				error_lexical(par->y, i);
		return (1);
	}
	else
		return (0);
}

void    is_operation(char *str, t_parser *par)
{
    int oper;

    oper = 0;
    if(!str)
        error_lexical(par->y, par->x);
    while (op[oper].name != NULL)
    {
        if (ft_strcmp(op[oper].name, str) == 0)
        {
        	add_token(par, OPERATOR, str);
        	par->tokens->data = oper; /////////////////////////////////////////////////
        	par->oper = oper;
        	par->arg = 0;
            par->tokens->bytes = g_bytes;
            g_bytes += 1 + (op[par->oper].args_types_code ? 1 : 0);
			ft_printf("%s\n", op[oper].name);
			return ;
        }
        oper++;
    }
    error_lexical(par->y, par->x);
}

int    label_or_comand(char *str, t_parser *par)
{
    if (is_label(str, par))
    {
		add_label_token(par, str);
		return (1);
	}
    else
	{
		is_operation(str, par);
		return (0);
	}
}

void	parse_args(t_parser *par)
{
	char	*string;
	int		i;
	int     args;

	args = 0;
	i = par->x;
	while(par->file[par->y][par->x] != '\0')
	{
	    if (par->file[par->y][par->x] == '#')
            return ;
	    if (args >= op[par->oper].args_num)
	        break ;
	        //error_lexical(par->y, par->x);
		while (par->file[par->y][i] != SEPARATOR_CHAR  && par->file[par->y][i] != ' '
		&& par->file[par->y][i] != '\t' && par->file[par->y][i])
			i++;
		string = ft_strsub(par->file[par->y], par->x, i - par->x);
		check_args(string, par);
		args++;
		i++;
		while (par->file[par->y][i] && (par->file[par->y][i] == ' ' || par->file[par->y][i] == '\t')) {
			i++;
		}
		par->x = i;
		ft_strdel(&string);
	}
	i--;
    while (par->file[par->y][i] && (par->file[par->y][i] == ' ' || par->file[par->y][i] == '\t'))
        i++;
    if (par->file[par->y][i] != '\0')
        error_lexical(par->y, par->x);
	par->x = 0;
	par->y++;
	add_token(par, NEW_LINE, NULL);
}

void	new_token(t_parser *par)
{
	char	*string;
	int		i;
	int		flag;
	int     label;

	label = 0;
	flag = 1;
	while ((par->file[par->y][par->x] == '\t' || par->file[par->y][par->x] == ' ') && par->file[par->y][par->x] != '\0')
		par->x++;
	i = par->x;
	if (par->file[par->y][par->x] == '\0')
        return ;
	while(flag)
	{
	    while (par->file[par->y + 1] && !par->file[par->y][par->x])
        {
	        par->y++;
	        par->x = 0;
            while ((par->file[par->y][par->x] == '\t' || par->file[par->y][par->x] == ' ') && par->file[par->y][par->x] != '\0')
                par->x++;
            i = par->x;
            label = 0;
        }
	    if (!par->file[par->y][par->x])
	        return ;
		while (par->file[par->y][i] != ' ' && par->file[par->y][i] != '\t' && par->file[par->y][i])
			i++;
		string = ft_strsub(par->file[par->y], par->x, i - par->x);
        (flag = label_or_comand(string, par)) == 1 ? label++ : 0;
        label > 1 ? flag = 0 : flag;
		while ((par->file[par->y][i] == ' ' || par->file[par->y][i] == '\t') && par->file[par->y][i])
			i++;
		par->x = i;
		ft_strdel(&string);
	}
	parse_args(par);
}

void parse_token(t_parser *par)
{
	while (par->file[par->y] != NULL)
	{
		while (par->file[par->y] && (par->file[par->y][par->x] == '\0' || par->file[par->y][par->x]
		== COMMENT_CHAR || par->file[par->y][par->x] == ALT_COMMENT_CHAR))
        {
            par->y++;
            par->x = 0;
        }
		if(par->file[par->y])
		    new_token(par);
	}
}

///////////////////////////////////////////////////////////////////////////

void	code_of_args_type(t_token *op, unsigned dest, u_int8_t n_arg)
{
    int8_t	res;
    int		arg;

    res = 0;
    arg = 0;
    while (arg < n_arg)
    {
        if (op->type == REGISTER)
            res |= 1 << 2 * (3 - arg++);
        else if (op->type == DIRECT || op->type == DIRECT_LABEL)
            res |= 2 << 2 * (3 - arg++);
        else if (op->type == INDIRECT || op->type == INDIRECT_LABEL)
            res |= 3 << 2 * (3 - arg++);
        op = op->next;
    }
    int_to_hex(res, 1, dest);
}

void    fill_args_data(t_parser *par, unsigned *dest)
{
    int     len;

    len = 0;
    if (par->head->type == REGISTER)
        len = T_REG;
    else if(par->head->type == DIRECT || par->head->type == DIRECT_LABEL)
        len = op[par->oper].t_dir_size;
    else if(par->head->type == INDIRECT || par->head->type == INDIRECT_LABEL)
        len = 2;

    int_to_hex(par->head->data, len, *dest);
    *dest += len;
    par->head = par->head->next;
}

void    filler_char_array(t_parser *par, unsigned dest)
{
    while(par->head)
    {
        if(par->head->type == OPERATOR)
        {
            par->oper = par->head->data;
            int_to_hex(op[par->head->data].code, 1, dest);
            dest++;
            if(op[par->head->data].args_types_code)
            {
                 code_of_args_type(par->head, dest, op[par->oper].args_num);
                 dest++;
            }
            par->head = par->head->next;
        }
        else if(par->head->type == REGISTER || par->head->type == DIRECT ||
        par->head->type == INDIRECT || par->head->type == DIRECT_LABEL ||
        par->head->type == INDIRECT_LABEL)
            fill_args_data(par, &dest);
        else
            par->head = par->head->next;
    }
}

void	int_to_hex(int32_t dec, int dir_size, unsigned place)
{
    int			move;

    move = 0;
    while (dir_size)
    {
        g_buf[place + dir_size - 1] = (u_int8_t)((dec >> move) & 0xFF);
        move += 8;
        dir_size--;
    }
}

void file_cor(t_parser *par)
{
    int fd;

    if((fd = open(par->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
        error_endline();
    if(write(fd, g_buf, EXEC_START + g_bytes) == -1)
    {
        close(fd);
        error_endline();
    }
    close(fd);
}

void fill_and_create(t_parser *parser)
{
    ft_printf("Writing output program to %s\n", parser->file_name);
    g_buf = (char *)malloc(sizeof(char) * (EXEC_START + g_bytes));
    ft_bzero(g_buf, (EXEC_START + g_bytes));
    int_to_hex(COREWAR_EXEC_MAGIC, 4, 0);
    ft_memcpy(&g_buf[4], parser->name, ft_strlen(parser->name));
    ft_memcpy(&g_buf[4 + PROG_NAME_LENGTH + 4 + 4], parser->comment, ft_strlen(parser->comment));
    int_to_hex(g_bytes, 4, (unsigned)(4 + PROG_NAME_LENGTH + 4));
    filler_char_array(parser, EXEC_START);
    file_cor(parser);
}

/////////////////////////////////////////////////////////////////////////////


unsigned    add_bytes(t_token *operator, char *label, t_parser *par)
{
    unsigned cur_byte;
    unsigned label_byte;
    t_label *head;

    head = par->labels;
    cur_byte = operator->bytes;

    while (head->next)
    {
        if (ft_strcmp(label, head->point->content) == 0)
            break;
        head = head->next;
    }
    label_byte = head->point->next->bytes;
//    if (cur_byte < label_byte)
    return (label_byte - cur_byte);
//    else ()
//    return (cur_byte + label_byte);
}

void    bytes_in_labels(t_parser *par)
{
    t_token *operator;

    operator = NULL;
    while (par->tokens)
    {
        if (par->tokens->type == OPERATOR)
            operator = par->tokens;
        if (par->tokens->type == INDIRECT_LABEL || par->tokens->type == DIRECT_LABEL)
        {
            par->tokens->data = add_bytes(operator, par->tokens->content, par);
        }
        par->tokens = par->tokens->next;
    }
}


int		main(int ac, char **av)
{
	t_parser parser;

	ft_bzero(&parser, sizeof(t_parser));
	g_bytes = 0;
	check_file_name(av[1], &parser);
	if (ac == 2)
	{
		parser.fd = open(av[1], O_RDONLY);
		read_file(&parser);
		parse_name_and_comment(&parser);
		parse_token(&parser);
        parser.tokens = parser.head;
		bytes_in_labels(&parser);
	}
	ft_printf("\n");
	parser.tokens = parser.head;
	fill_and_create(&parser);
//	for (int i = 6;parser.tokens;i++)
//	{
//		if(parser.tokens->type == LABEL)
//			ft_printf("%s\n", parser.tokens->content);
//		parser.tokens = parser.tokens->next;
//	}
	ft_printf("%d", op[1].args_types[0]);
	exit(0);
}
