/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_incurses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluton <hluton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:06:59 by hluton            #+#    #+#             */
/*   Updated: 2019/10/07 18:07:00 by hluton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"
#define CORE_WAR 12

char	g_core_war[CORE_WAR][100] =
{
	" ####  ###  ####  #####     \n",
	"#     #   # #   # #         \n",
	"#     #   # ####  #####     \n",
	"#     #   # #  #  #         \n",
	" ####  ###  #   # #####     \n",
	"                            \n",
	"            #           #  #   #### \n",
	"             #         #  # #  #   #\n",
	"              #   #   #  ##### #### \n",
	"               # # # #   #   # #  # \n",
	"                #   #    #   # #   #\n"
};

void	ft_print_frame(WINDOW *frame)
{
	int i;
	int j;
	int colour;

	colour = MAX_PLAYERS + 1;
	i = 0;
	while (i < FRAME_H)
	{
		j = 0;
		while (j < FRAME_L)
		{
			if ((j < 1 && i < 1) || (i == FRAME_H - 1 && j == FRAME_L - 1) ||
			(i == FRAME_H - 1 && j < 1) || (i < 1 && j == FRAME_L - 1))
				mvwaddch(frame, i, j, 'O' | COLOR_PAIR(colour) | A_BOLD);
			else if (i < 1 || i == FRAME_H - 1)
				mvwaddch(frame, i, j, '#' | COLOR_PAIR(colour) | A_BOLD);
			else if (j < 1 || j >= FRAME_L - 1 || j == INFO_X - 4)
				mvwaddch(frame, i, j, '#' | COLOR_PAIR(colour) | A_BOLD);
			j++;
		}
		i++;
	}
}

void	ft_print_picture(WINDOW *win, char *picture, int str_count)
{
	char	*str;
	int		i;

	i = 0;
	wprintw(win, "\n");
	while (i < str_count)
	{
		str = picture + i * 100;
		wprintw(win, "%s", str);
		i++;
	}
	wprintw(win, "\n");
}

void	ft_print_info(t_all *all)
{
	WINDOW	*win;
	int		i;
	t_play	*player;

	win = all->wins->info;
	wmove(win, 0, 0);
	wattron(win, COLOR_PAIR(MAX_PLAYERS + 4));
	ft_print_picture(win, g_core_war[0], CORE_WAR);
	wprintw(win, "Total cycle: %d\n", all->total_cycle);
	wprintw(win, "Cycle: %d\n", all->cycle);
	wprintw(win, "Cycle to die: %d\n", all->cycle_to_die);
	wprintw(win, "Count of process: %d\nWinner: ", all->cars_count);
	wattron(win, COLOR_PAIR(all->last_live_player));
	wprintw(win, "%s\n", (all->player[all->last_live_player])->prog_name);
	wattroff(win, COLOR_PAIR(all->last_live_player));
	wprintw(win, "\nChampions:\n");
	i = 1;
	while (i <= MAX_PLAYERS)
	{
		wattron(win, COLOR_PAIR(i));
		if ((player = all->player[i]))
			wprintw(win, "%d - %s\n", player->number, player->prog_name);
		wattroff(win, COLOR_PAIR(i));
		i++;
	}
}

void	ft_print_battlefield(t_all *all)
{
	WINDOW	*win;
	attr_t	attrs;
	int		i;

	win = all->wins->battlefield;
	wmove(win, 0, 0);
	i = 0;
	while (i < MEM_SIZE)
	{
		attrs = ft_get_colour(all, i);
		wattron(win, attrs);
		wprintw(win, "%02hhx", all->memory[i]);
		wattroff(win, attrs);
		wprintw(win, " ");
		i++;
	}
}
