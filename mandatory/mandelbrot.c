/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:37:18 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/31 16:59:15 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	render_mandelbrot(t_data *data)
{
	if (!data->win_ptr)
		return (1);
	data->re_factor = (data->max_re - data->min_re) / (data->win_width);
	data->im_factor = (data->max_im - data->min_im) / (data->win_height);
	mandelbrot(&data->img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, data->win_width,
			data->win_height);
	return (0);
}

void	color_man(t_data *data, t_img *img, t_index in, t_fract *fract)
{
	double	tmp;

	while (++in.i < data->iter && (fract->z_re * fract->z_re
			+ fract->z_im * fract->z_im < 4))
	{
		tmp = fract->z_re * fract->z_re - fract->z_im * fract->z_im;
		fract->z_im = (2 * fract->z_im * fract->z_re) + fract->c_im;
		fract->z_re = tmp + fract->c_re;
	}
	if (in.i == data->iter)
		img_pix_put(img, in.x, in.y, 0x000000);
	else
		img_pix_put(img, in.x, in.y, 0xF0F8FF * in.i);
	fract->z_re = fract->c_re;
	fract->z_im = fract->c_im;
}

int	mandelbrot(t_img *img, t_data *data)
{
	t_fract	man;
	t_index	in;

	man.z_re = 0;
	man.z_im = 0;
	in.y = -1;
	while (++in.y < data->win_height)
	{
		man.c_im = data->min_im + in.y * data->im_factor;
		in.x = -1;
		while (++in.x < data->win_width)
		{
			man.c_re = data->min_re + (in.x * data->re_factor);
			in.i = -1;
			color_man(data, img, in, &man);
		}
	}
	return (0);
}
