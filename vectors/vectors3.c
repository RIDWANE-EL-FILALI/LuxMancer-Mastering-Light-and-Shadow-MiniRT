#include "vectors.h"

double  distance(t_point p1, t_point p2)
{
    double d;

	d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
	return (d);
}

t_point		x_axis_rotation(t_point vec, double angle)
{
	t_point	row1;
	t_point	row2;
	t_point	row3;
	t_point	rotated;
	double	rad_angle;

	rad_angle = angle * M_PI / 180;
	row1 = (t_point){1, 0, 0};
	row2 = (t_point){0, cos(rad_angle), -sin(rad_angle)};
	row3 = (t_point){0, sin(rad_angle), cos(rad_angle)};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}

t_point		y_axis_rotation(t_point vec, double angle)
{
	t_point	row1;
	t_point	row2;
	t_point	row3;
	t_point	rotated;
	double	rad_angle;

	rad_angle = angle * M_PI / 180;
	row1 = (t_point){cos(rad_angle), 0, sin(rad_angle)};
	row2 = (t_point){0, 1, 0};
	row3 = (t_point){-sin(rad_angle), 0, cos(rad_angle)};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}

t_point		z_axis_rotation(t_point vec, double angle)
{
	t_point	row1;
	t_point	row2;
	t_point	row3;
	t_point	rotated;
	double	rad_angle;

	rad_angle = angle * M_PI / 180;
	row1 = (t_point){cos(rad_angle), -sin(rad_angle), 0};
	row2 = (t_point){sin(rad_angle), cos(rad_angle), 0};
	row3 = (t_point){0, 0, 1};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}
