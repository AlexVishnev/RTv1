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
# define GLOBAL 1
# define POINT 2
# define DIRECTIONAL 3
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define DEEP 1

typedef struct 			s_vector
{
	float				x;
	float				y;
}						t_vector;

typedef struct			s_ray
{
	float				x;
	float				y;
	float				z;
	float				w;
	float				reflect;
}						t_ray;

typedef	struct			s_light
{
	int					type;
	double				intensity;
	t_ray				position;
	t_ray				direction;
}						t_light;

typedef	struct			s_obj
{
	int					type;
	t_ray				mid;
	t_ray				direction;
	t_ray				color;
	float				specular;
	float				radius;
	float				reflect;
	float				angle;
}						t_obj;

typedef struct			s_cam
{
	float				w;
	float				h;
	float				dist;
}						t_cam;

typedef	struct	s_trace
{
	double			closest_inters;
	t_obj			closest_obj;
	t_vector		t;
}				t_trace;

typedef	struct	s_params
{
	t_ray		O;
	t_ray		D;
	t_ray		camera_rot;
	long		obj;
	long		light;
	t_cam		vp;
	float		t_min;
	float		t_max;
	int			color;
	int			objects;
	int			lights;
	int			screenw;
	int			screenh;
}				t_params;


t_ray	global_normal(t_ray P, t_trace *tr);
t_ray	rot_matrix(double a, double b, double c, t_ray r);
t_ray	ray_multipl(double a, t_ray b);
//t_ray	vec_mult(t_ray a, t_ray b);
t_ray	ray_summary(t_ray a, t_ray b);
t_ray	divide_ray(t_ray a, float b);
t_ray	ray_subs(t_ray a, t_ray b);
t_ray	normal(t_ray a);
t_ray	ReflectRay(t_ray R, t_ray N);
t_ray	CanvasToViewport(t_params *par, float x, float y);
t_vector	find_discriminant(float k[3]);
t_vector	IntersectRayCylinder(t_ray P, t_ray V, __constant t_obj *obj);
t_vector	IntersectRayCone(t_ray P, t_ray V, __constant t_obj *obj);
t_vector	IntersectRaySphere(t_ray O, t_ray D, __constant t_obj *obj);
t_vector	IntersectRayPlane(t_ray O, t_ray D, __constant t_obj *obj);
float	ft_raylen(t_ray struc);
float	conv_degr_rad(float degree);
float	itersect_dot(t_ray a, t_ray b);
int		rgb_to_int(int red, int green, int blue);
double	GenerateLigth(t_params *par, __constant t_obj *obj, __constant t_light *light, t_ray P, t_ray N, t_ray V, float specular);
double	get_lim_solution(double t, t_ray P, t_ray V, t_ray VA, __constant t_obj *obj);
int		RayTracer(t_params par, __constant t_obj *obj, __constant t_light *light, float t_min, float t_max);
int		ClosestIntersection(t_trace *tr, t_params *par, __constant t_obj *obj,
							t_ray O, t_ray D, float t_min, float t_max);

t_ray	ray_multipl(double a, t_ray b)
{
	return ((t_ray){a * b.x, a * b.y, a * b.z});
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
	ray.x = (cos(b) * cos(c) * r.x) + (cos(c) * sin(a) * sin(b)
	 - cos(a) * sin(c) * r.y) + (cos(a) * cos(c) * sin(b) + sin(a) * sin(c) * r.z);
	ray.y = (cos(b) * sin(c) * r.x) + (mat[1][1] * r.y) + (mat[2][1] * r.z);
	ray.z = (mat[0][2] * r.x) + (mat[1][2] * r.y) + (mat[2][2] * r.z);
	return (ray);
}

float	ft_raylen(t_ray ray)
{
	return (sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z));
}

// t_ray	vec_mult(t_ray a, t_ray b)
// {
// 	return ((t_ray){a.x * b.x, a.y * b.y, a.z * b.z});
// }

t_ray	ray_summary(t_ray a, t_ray b)
{
	return ((t_ray){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_ray	divide_ray(t_ray a, float b)
{
	if (b == 0)
		return (a);
	return ((t_ray){a.x / b, a.y / b, a.z / b});
}

t_ray	ray_subs(t_ray a, t_ray b)
{
	return ((t_ray){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_ray	normal(t_ray a)
{
	return (divide_ray(a, ft_raylen(a)));
}

t_ray	CanvasToViewport(t_params *par, float x, float y)
{
	return ((t_ray){x * par->vp.w / par->screenw, y * par->vp.h / par->screenh, par->vp.dist});
}

float	conv_degr_rad(float degree)
{
	return ((degree * M_PI) / 180);
}

float	itersect_dot(t_ray a, t_ray b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_ray	ReflectRay(t_ray R, t_ray N)
{
    return (ray_subs(ray_multipl(itersect_dot(N, R), ray_multipl(2.0, N)), R));
}

double		GenerateLigth(t_params *par, __constant t_obj *obj, __constant t_light *light,
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
		if (light[j].type == GLOBAL)
			i += light[j].intensity;
		else
		{
			if (light[j].type == POINT)
			{
				L = ray_subs(light[j].position, P);
				max = 0.99f;
			}
			else
			{
				L = light[j].direction;
				max = INFINITY;
			}

			// Проверка нормали для света
			if (itersect_dot(V, N) < 0)
				continue ;
			
			// Проверка тени
			ClosestIntersection(&shadow, par, obj, P, L, 0.001, max);
			if (shadow.closest_inters != INFINITY)
				continue ;

			// Диффузность
			nl = itersect_dot(N, L);
			if (nl > 0)
				i += light[j].intensity * nl / (ft_raylen(N) * ft_raylen(L));

			// Зеркальность
			if (spec >= 0)
			{
//				R = ray_subs(ray_multipl((itersect_dot(N, L) * 2), N), L);
				R = ray_subs(ray_multipl(itersect_dot(N, L), ray_multipl(2.0, N)), L);
				rv = itersect_dot(R, V);
				if (rv > 0)
					i += light[j].intensity * pow(rv / (ft_raylen(R) * ft_raylen(V)), spec);
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
	Q = ray_summary(P, ray_multipl(t, V));
	k[0] = itersect_dot(VA, ray_subs(Q, obj->mid));
	k[1] = itersect_dot(VA, ray_subs(Q, obj->direction));
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
	PA = obj->mid;
	VA = normal(ray_subs(PA, obj->direction));
	deltaP = ray_subs(P, PA);

	A = ray_subs(V, ray_multipl(itersect_dot(V, VA), VA));
	B = ray_subs(deltaP, ray_multipl(itersect_dot(deltaP, VA), VA));
	cospw = cos(angle) * cos(angle);
	sinpw = sin(angle) * sin(angle);

	k[0] = cospw * itersect_dot(A, A) - sinpw * itersect_dot(V, VA) * itersect_dot(V, VA);
	k[1] = 2.0f * cospw * itersect_dot(A, B) - 2.0f * sinpw * itersect_dot(V, VA) * itersect_dot(deltaP, VA);
	k[2] = cospw * itersect_dot(B, B) - sinpw * itersect_dot(deltaP, VA) * itersect_dot(deltaP, VA);
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

	PA = obj->mid;
	VA = normal(ray_subs(PA, obj->direction));
	deltaP = ray_subs(P, PA);

	A = ray_subs(V, ray_multipl(itersect_dot(V, VA), VA));
	B = ray_subs(deltaP, ray_multipl(itersect_dot(deltaP, VA), VA));

	k[0] = itersect_dot(A, A);
	k[1] = 2.0f * itersect_dot(A, B);
	k[2] = itersect_dot(B, B) - obj->radius * obj->radius;
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

	C = obj->mid;
	r = obj->radius;
	OC = ray_subs(O, C);

	k[0] = itersect_dot(D, D);
	k[1] = 2.0f * itersect_dot(OC, D);
	k[2] = itersect_dot(OC, OC) - r * r;
	return (find_discriminant(k));
}

t_vector	IntersectRayPlane(t_ray O, t_ray D, __constant t_obj *obj)
{
	t_ray	X;
	t_ray	C;
	t_ray	N;
	t_vector	t;
	float	k[2];

	C = obj->mid;
	N = obj->direction;
	X = ray_subs(O, C);
	k[0] = itersect_dot(D, N);
	k[1] = itersect_dot(X, N);
	if (k[0])
	{
		t.x = -k[1] / k[0];
		t.y = INFINITY;
		return (t);		
	}
	return ((t_vector){INFINITY, INFINITY});
}

int		ClosestIntersection(t_trace *tr, t_params *par, __constant t_obj *obj,
								t_ray O, t_ray D, float t_min, float t_max)
{
	int			i;
	t_vector		t;

	tr->closest_inters = INFINITY;
	i = -1;
	while (++i < par->objects)
	{
		if (obj[i].type == SPHERE)
			t = IntersectRaySphere(O, D, &obj[i]);
		else if (obj[i].type == PLANE)
			t = IntersectRayPlane(O, D, &obj[i]);
		else if (obj[i].type == CYLINDER)
			t = IntersectRayCylinder(O, D, &obj[i]);
		else if (obj[i].type == CONE)
			t = IntersectRayCone(O, D, &obj[i]);
		if (t.x > t_min && t.x < t_max && t.x < tr->closest_inters)
		{
			tr->closest_inters = t.x;
			tr->closest_obj = obj[i];
		}
		if (t.y > t_min && t.y < t_max && t.y < tr->closest_inters)
		{
			tr->closest_inters = t.y;
			tr->closest_obj = obj[i];
		}
	}
	return (tr->closest_inters);
}

t_ray	global_normal(t_ray P, t_trace *tr)
{
	t_ray	N;
	t_ray	os;
	t_ray	proj;

	if (tr->closest_obj.type == SPHERE)
	{
		N = ray_subs(P, tr->closest_obj.mid);
		N = normal(N);
		return (N);
	}
	if (tr->closest_obj.type == CYLINDER || tr->closest_obj.type == CONE)
	{
		os = normal(ray_subs(tr->closest_obj.direction, tr->closest_obj.mid));
		N = ray_subs(P, tr->closest_obj.mid);
		proj = ray_multipl(itersect_dot(N, os), os);
		N = ray_subs(N, proj);
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
		local_color[deep] = (t_ray){0,0,0,0};
		deep--;
	}
	deep = DEEP;
	while (deep >= 0)
	{
		ClosestIntersection(&tr, &par, obj, par.O, par.D, t_min, t_max);
		if (tr.closest_inters == INFINITY)
		{
			local_color[deep] = (t_ray){0,0,0};
			break ;
		}
		P = ray_summary(par.O, ray_multipl(tr.closest_inters, par.D)); //compute intersection
		N = global_normal(P, &tr);
		t_ray DD = (t_ray){-par.D.x, -par.D.y, -par.D.z, 0};
		intensity = GenerateLigth(&par, obj, light, P, N, DD, tr.closest_obj.specular); // -D
		local_color[deep] = ray_multipl(intensity, tr.closest_obj.color);


		local_color[deep].reflect = tr.closest_obj.reflect;
		if (tr.closest_obj.reflect > 0)
		{
			R = ReflectRay(DD, N);
			par = (t_params){P, R, par.camera_rot, par.obj, par.light, par.vp,  par.t_min,
				par.t_max, par.color, par.objects, par.lights, par.screenw, par.screenh};
			deep--;
		}
		else
			break ;
	}
	deep = 0;
	while (deep < DEEP)
	{
		local_color[deep + 1] = ray_summary(ray_multipl(1 - local_color[deep + 1].reflect, local_color[deep + 1]),
						ray_multipl(local_color[deep + 1].reflect, local_color[deep]));
		deep++;
	}
	return (rgb_to_int(local_color[deep].x, local_color[deep].y, local_color[deep].z));
}

__kernel
void	render(__global int *img_pxl, t_params params, __constant t_obj *obj, __constant t_light *light)
{
	int x = get_global_id(0);
	int y = get_global_id(1);

	params.D = rot_matrix(params.camera_rot.x, params.camera_rot.y, params.camera_rot.z,
		CanvasToViewport(&params, x - params.screenw / 2, params.screenh / 2 - y));
	params.color = RayTracer(params, obj, light, 0.001f, INFINITY);
	img_pxl[x + y * params.screenw] = params.color;
}
