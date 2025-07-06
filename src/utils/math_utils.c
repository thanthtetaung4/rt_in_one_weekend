#include "../../inc/rt.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.0));
}

double	ft_fabs(double x)
{
	return (x < 0) ? -x : x;
}
