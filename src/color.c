#include "../inc/color.h"

void	write_color(FILE *out, color pixel_color)
{
	double	r;
	double	g;
	double	b;
	int		rbyte;
	int		gbyte;
	int		bbyte;

	r = pixel_color.x;
	g = pixel_color.y;
	b = pixel_color.z;
	// Convert to [0,255] range
	rbyte = (int)(255.999 * r);
	gbyte = (int)(255.999 * g);
	bbyte = (int)(255.999 * b);
	// Write to file
	fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
