# include "../../inc/rt.h"

void	rgbthex(t_rgb color, int *hex_color)
{
	*hex_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
}
