#ifndef VECTORS_H
#define VECTORS_H

#include "./../main.h"


typedef struct s_point
{
    double x;
    double y;
    double z;
}   t_point;



t_point		z_axis_rotation(t_point vec, double angle);
t_point		y_axis_rotation(t_point vec, double angle);
t_point		x_axis_rotation(t_point vec, double angle);
double  distance(t_point p1, t_point p2);
t_point		scal_x_vec(double n, t_point p);
double		vcos(t_point a, t_point b);
double		vsin(t_point a, t_point b);
t_point normalize(t_point vector);
double mod(t_point vector);
t_point cross(t_point a, t_point b);
t_point cross(t_point a, t_point b);
t_point vadd(t_point a, t_point b);
t_point vsubstr(t_point a, t_point b);
t_point vector(double x, double y, double z);
double dot(t_point a, t_point b);


#endif