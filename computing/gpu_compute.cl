/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_compute.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:38:07 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/17 14:38:10 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define TRUE 1
# define AMBIENT 1
# define POINT 2
# define DIRECTIONAL 3
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define DEEP 1

typedef	struct	s_vector
{
	float		x;
	float		y;
}				t_vector;

typedef	struct	s_ray
{
	float		x;
	float		y;
	float		z;
	float		w;
	float		reflect;
}				t_ray;

typedef	struct	s_light
{
	int			type;
	double		intensity;
	t_ray		position;
	t_ray		direction;
}				t_light;

typedef	struct	s_obj
{
	int			name;
	t_ray		center;
	t_ray		direction;
	t_ray		color;
	float		specular;
	float		radius;
	float		reflect;
	float		angle;
}				t_obj;

typedef struct	s_cam
{
	float		w;
	float		h;
	float		dist;
}				t_cam;

typedef	struct	s_traceray
{
	double		closest_t;
	t_obj		closest_obj;
	t_vector		t;
}				t_trace;

typedef	struct	s_params
{
	t_ray		O;
	t_ray		D;
	t_ray		camera_rot;
	int			color;
	float		t_min;
	float		t_max;
	int			objects;
	int			lights;
	long		obj;
	long		light;
	t_cam		vp;
	int			screenw;
	int			screenh;
}				t_params;


t_ray	global_normal(t_ray P, t_trace *tr);
t_ray	rot_matrix(double a, double b, double c, t_ray r);
t_ray	vec_f_mult(double a, t_ray b);
t_ray	vec_mult(t_ray a, t_ray b);
t_ray	vec_add(t_ray a, t_ray b);
t_ray	vec_div(t_ray a, float b);
t_ray	vec_sub(t_ray a, t_ray b);
t_ray	normal(t_ray a);
t_ray	ReflectRay(t_ray R, t_ray N);
t_ray	CanvasToViewport(t_params *par, float x, float y);
t_vector	find_discriminant(float k[3]);
t_vector	IntersectRayCylinder(t_ray P, t_ray V, __constant t_obj *obj);
t_vector	IntersectRayCone(t_ray P, t_ray V, __constant t_obj *obj);
t_vector	IntersectRaySphere(t_ray O, t_ray D, __constant t_obj *obj);
t_vector	IntersectRayPlane(t_ray O, t_ray D, __constant t_obj *obj);
float	vec_lenght(t_ray struc);
float	conv_degr_rad(float degree);
float	ft_dot(t_ray a, t_ray b);
int		rgb_to_int(int red, int green, int blue);
double	ComputeLighting(t_params *par, __constant t_obj *obj, __constant t_light *light, t_ray P, t_ray N, t_ray V, float specular);
double	get_lim_solution(double t, t_ray P, t_ray V, t_ray VA, __constant t_obj *obj);
int		RayTracer(t_params par, __constant t_obj *obj, __constant t_light *light, float t_min, float t_max);
void	ClosestIntersection(t_trace *tr, t_params *par, __constant t_obj *obj,
							t_ray O, t_ray D, float t_min, float t_max);

t_ray	vec_f_mult(double a, t_ray b)
{
	t_ray c;

	c.x = a * b.x;
	c.y = a * b.y;
	c.z = a * b.z;
	return (c);
}

int		rgb_to_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

t_ray	rot_matrix(double a, double b, double c, t_ray r)
{
	double		mat[3][3];
	t_ray		ray;

	
	mat[0][0] = cos(b) * cos(c);
	mat[1][0] = cos(c) * sin(a) * sin(b) - cos(a) * sin(c);
	mat[2][0] = cos(a) * cos(c) * sin(b) + sin(a) * sin(c);
	mat[0][1] = cos(b) * sin(c);
	mat[1][1] = cos(a) * cos(c) + sin(a) * sin(b) * sin(c);
	mat[2][1] = -cos(c) * sin(a) + cos(a) * sin(b) * sin(c);
	mat[0][2] = -sin(b);
	mat[1][2] = cos(b) * sin(a);
	mat[2][2] = cos(a) * cos(b);
	ray.x = (mat[0][0] * r.x) + (mat[1][0] * r.y) + (mat[2][0] * r.z);
	ray.y = (mat[0][1] * r.x) + (mat[1][1] * r.y) + (mat[2][1] * r.z);
	ray.z = (mat[0][2] * r.x) + (mat[1][2] * r.y) + (mat[2][2] * r.z);
	return (ray);
}

float	vec_lenght(t_ray vc)
{
	float rez;

	rez = sqrt(vc.x * vc.x + vc.y * vc.y + vc.z * vc.z);
	return (rez);
}

t_ray	vec_mult(t_ray a, t_ray b)
{
	t_ray rez;

	rez.x = a.x * b.x;
	rez.y = a.y * b.y;
	rez.z = a.z * b.z;
	return (rez);
}

t_ray	vec_add(t_ray a, t_ray b)
{
	t_ray c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_ray	vec_div(t_ray a, float b)
{
	t_ray c;

	if (b == 0)
		return (c);
	c.x = a.x / b;
	c.y = a.y / b;
	c.z = a.z / b;
	return (c);
}

t_ray	vec_sub(t_ray a, t_ray b)
{
	t_ray c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_ray	normal(t_ray a)
{
	t_ray c;

	c = vec_div(a, vec_lenght(a));
	return (c);
}

t_ray	CanvasToViewport(t_params *par, float x, float y)
{
	t_ray D;

	D.x = x * par->vp.w / par->screenw;
	D.y = y * par->vp.h / par->screenh;
	D.z = par->vp.dist;
	return (D);
}

float	conv_degr_rad(float degree)
{
	float	radians;

	radians = (degree * M_PI) / 180;
	return (radians);
}

float	ft_dot(t_ray a, t_ray b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_ray	ReflectRay(t_ray R, t_ray N)
{
	t_ray res;

	res = vec_sub(vec_f_mult(ft_dot(N, R), vec_f_mult(2.0, N)), R);
    return (res);
}

double		ComputeLighting(t_params *par, __constant t_obj *obj, __constant t_light *light,
									t_ray P, t_ray N, t_ray V, float spec)
{
	double		i;
	int			j;
	t_ray		L;
	t_ray		R;
	float		nl;
	float		rv;
	float		max;
	t_trace		shadow;

	i = 0.0;
	j = -1;
	while (++j < par->lights)
	{
		if (light[j].type == AMBIENT)
			i += light[j].intensity;
		else
		{
			if (light[j].type == POINT)
			{
				L = vec_sub(light[j].position, P);
				max = 0.99f;
			}
			else
			{
				L = light[j].direction;
				max = INFINITY;
			}

			// Проверка нормали для света
			if (ft_dot(V, N) < 0)
				continue ;
			
			// Проверка тени
			ClosestIntersection(&shadow, par, obj, P, L, 0.001, max);
			if (shadow.closest_t != INFINITY)
				continue ;

			// Диффузность
			nl = ft_dot(N, L);
			if (nl > 0)
				i += light[j].intensity * nl / (vec_lenght(N) * vec_lenght(L));

			// Зеркальность
			if (spec >= 0)
			{
				R = vec_sub(vec_f_mult(ft_dot(N, L), vec_f_mult(2.0, N)), L); //vec_sub(vec_f_mult((ft_dot(N, L) * 2), N), L);
				rv = ft_dot(R, V);
				if (rv > 0)
					i += light[j].intensity * pow(rv / (vec_lenght(R) * vec_lenght(V)), specular);
			}
		}
	}
	i > 1.0 ? i = 1.0 : 0;
	return (i);
}

t_vector	find_discriminant(float k[3])
{
	t_vector	t;
	float	disc;

	disc = k[1] * k[1] - 4.0f * k[0] * k[2];
	if (disc < 0)
		return ((t_vector){INFINITY, INFINITY});
	t.x = (-k[1] + sqrt(disc)) / (2.0f * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2.0f * k[0]);
	return (t);
}

double		get_lim_solution(double t, t_ray P, t_ray V, t_ray VA, __constant t_obj *obj)
{
	t_ray	Q;
	float	k[2];

	if (t < 0)
		return (INFINITY);
	Q = vec_add(P, vec_f_mult(t, V));
	k[0] = ft_dot(VA, vec_sub(Q, obj->center));
	k[1] = ft_dot(VA, vec_sub(Q, obj->direction));
	if (k[0] < 0.0 && k[1] > 0.0)
		return (t);
	return (INFINITY);
}

t_vector	IntersectRayCone(t_ray P, t_ray V, __constant t_obj *obj)
{
	t_ray	PA;
	t_ray	VA;
	t_ray	deltaP;
	t_ray	A;
	t_ray	B;
	t_vector	t;
	float	k[3];
	float	angle;
	float	cospw;
	float	sinpw;

	angle = conv_degr_rad(obj->angle);
	PA = obj->center;
	VA = normal(vec_sub(PA, obj->direction));
	deltaP = vec_sub(P, PA);

	A = vec_sub(V, vec_f_mult(ft_dot(V, VA), VA));
	B = vec_sub(deltaP, vec_f_mult(ft_dot(deltaP, VA), VA));
	cospw = cos(angle) * cos(angle);
	sinpw = sin(angle) * sin(angle);

	k[0] = cospw * ft_dot(A, A) - sinpw * ft_dot(V, VA) * ft_dot(V, VA);
	k[1] = 2.0f * cospw * ft_dot(A, B) - 2.0f * sinpw * ft_dot(V, VA) * ft_dot(deltaP, VA);
	k[2] = cospw * ft_dot(B, B) - sinpw * ft_dot(deltaP, VA) * ft_dot(deltaP, VA);
	t = find_discriminant(k);
	t.x = get_lim_solution(t.x, P, V, VA, obj);
	t.y = get_lim_solution(t.y, P, V, VA, obj);
	return (t);
}

t_vector	IntersectRayCylinder(t_ray P, t_ray V, __constant t_obj *obj)
{
	t_ray	PA;
	t_ray	VA;
	t_ray	deltaP;
	t_ray	A;
	t_ray	B;
	t_vector	t;
	float	k[3];

	PA = obj->center;
	VA = normal(vec_sub(PA, obj->direction));
	deltaP = vec_sub(P, PA);

	A = vec_sub(V, vec_f_mult(ft_dot(V, VA), VA));
	B = vec_sub(deltaP, vec_f_mult(ft_dot(deltaP, VA), VA));

	k[0] = ft_dot(A, A);
	k[1] = 2.0f * ft_dot(A, B);
	k[2] = ft_dot(B, B) - obj->radius * obj->radius;
	t = find_discriminant(k);
	t.x = get_lim_solution(t.x, P, V, VA, obj);
	t.y = get_lim_solution(t.y, P, V, VA, obj);
	return (t);
}

t_vector	IntersectRaySphere(t_ray O, t_ray D, __constant t_obj *obj)
{
	t_ray	C;
	t_ray	OC;
	double	r;
	float	k[3];

	C = obj->center;
	r = obj->radius;
	OC = vec_sub(O, C);

	k[0] = ft_dot(D, D);
	k[1] = 2.0f * ft_dot(OC, D);
	k[2] = ft_dot(OC, OC) - r * r;
	return (find_discriminant(k));
}

t_vector	IntersectRayPlane(t_ray O, t_ray D, __constant t_obj *obj)
{
	t_ray	X;
	t_ray	C;
	t_ray	N;
	t_vector	t;
	float	k[2];

	C = obj->center;
	N = obj->direction;
	X = vec_sub(O, C);
	k[0] = ft_dot(D, N);
	k[1] = ft_dot(X, N);
	if (k[0])
	{
		t.x = -k[1] / k[0];
		t.y = INFINITY;
		return (t);		
	}
	return ((t_vector){INFINITY, INFINITY});
}

void	ClosestIntersection(t_trace *tr, t_params *par, __constant t_obj *obj,
								t_ray O, t_ray D, float t_min, float t_max)
{
	int			i;
	t_vector		t;

	tr->closest_t = INFINITY;
	i = -1;
	while (++i < par->objects)
	{
		if (obj[i].name == SPHERE)
			t = IntersectRaySphere(O, D, &obj[i]);
		else if (obj[i].name == PLANE)
			t = IntersectRayPlane(O, D, &obj[i]);
		else if (obj[i].name == CYLINDER)
			t = IntersectRayCylinder(O, D, &obj[i]);
		else if (obj[i].name == CONE)
			t = IntersectRayCone(O, D, &obj[i]);
		if (t.x > t_min && t.x < t_max && t.x < tr->closest_t)
		{
			tr->closest_t = t.x;
			tr->closest_obj = obj[i];
		}
		if (t.y > t_min && t.y < t_max && t.y < tr->closest_t)
		{
			tr->closest_t = t.y;
			tr->closest_obj = obj[i];
		}
	}
}

t_ray	global_normal(t_ray P, t_trace *tr)
{
	t_ray	N;
	t_ray	os;
	t_ray	proj;

	if (tr->closest_obj.name == SPHERE)
	{
		N = vec_sub(P, tr->closest_obj.center);
		N = normal(N);
		return (N);
	}
	if (tr->closest_obj.name == CYLINDER || tr->closest_obj.name == CONE)
	{
		os = normal(vec_sub(tr->closest_obj.direction, tr->closest_obj.center));
		N = vec_sub(P, tr->closest_obj.center);
		proj = vec_f_mult(ft_dot(N, os), os);
		N = vec_sub(N, proj);
		N = normal(N);
		return (N);
	}
	N = tr->closest_obj.direction; // PLANE
	return (N);
}

int		RayTracer(t_params par, __constant t_obj *obj, __constant t_light *light, float t_min, float t_max)
{
	t_trace		tr;
	t_ray		P;
	t_ray		N;
	t_ray		R;
	t_ray		local_color[DEEP + 1];
	int			deep;
	double		intensity;

	deep = DEEP;
	while (deep >= 0)
	{
		local_color[deep].x = 0;
		local_color[deep].y = 0;
		local_color[deep].z = 0;
		local_color[deep].reflect = 0;
		deep--;
	}
	deep = DEEP;
	while (deep >= 0)
	{
		ClosestIntersection(&tr, &par, obj, par.O, par.D, t_min, t_max);
		if (tr.closest_t == INFINITY)
		{
			local_color[deep] = (t_ray){0,0,0};
			break ;
		}
		P = vec_add(par.O, vec_f_mult(tr.closest_t, par.D)); //compute intersection
		N = global_normal(P, &tr);
		t_ray DD = (t_ray){-par.D.x, -par.D.y, -par.D.z, 0};
		intensity = ComputeLighting(&par, obj, light, P, N, DD, tr.closest_obj.specular); // -D
		local_color[deep] = vec_f_mult(intensity, tr.closest_obj.color);


		local_color[deep].reflect = tr.closest_obj.reflect;
		if (tr.closest_obj.reflect > 0)
		{
			R = ReflectRay(DD, N);
			par = (t_params){P, R, par.camera_rot, par.color, par.t_min,
				par.t_max, par.objects, par.lights, par.obj, par.light, par.vp, par.screenw, par.screenh};
			deep--;
		}
		else
			break ;
	}
	deep = 0;
	while (deep < DEEP)
	{
		local_color[deep + 1] = vec_add(vec_f_mult(1 - local_color[deep + 1].reflect, local_color[deep + 1]),
						vec_f_mult(local_color[deep + 1].reflect, local_color[deep]));
		deep++;
	}
	return (rgb_to_int(local_color[deep].x, local_color[deep].y, local_color[deep].z));
}

__kernel
void	render(__global int *img_pxl, t_params par, __constant t_obj *obj, __constant t_light *light)
{
	int x;
	int y; 

	x = get_global_id(0);
	y = get_global_id(1);

	par.D = rot_matrix(par.camera_rot.x, par.camera_rot.y, par.camera_rot.z,
		CanvasToViewport(&par, x - par.screenw / 2, par.screenh / 2 - y));
	par.color = RayTracer(par, obj, light, 0.001f, INFINITY);
	img_pxl[x + y * par.screenw] = par.color;
}
