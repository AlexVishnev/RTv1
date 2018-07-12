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

# define GLOBAL 1
# define POINT 2
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define RECURS 1


typedef struct			s_ray
{
	float				x;
	float				y;
	float				z;
	float				w;
	float				reflect;
	float				k[3];
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
	double			closest_intersect;
	t_obj			closest_object;
	float2			t;
}				t_trace;

typedef	struct	s_params
{
	t_ray		O;
	t_ray		Dimention;
	t_ray		camera_rot;
	long		obj;
	long		light;
	t_cam		viewport;
	float		t_min;
	float		t_max;
	int			color;
	int			objects;
	int			lights;
	int			screenw;
	int			screenh;
}				t_params;


int			RayTracer(__constant t_obj *obj, __constant t_light *light, t_params par, float t_min, float t_max);
int			ClosestIntersection(__constant t_obj *obj, t_trace *tr, t_params *par,
							t_ray O, t_ray D, float t_min, float t_max);
int			RgbToInt(int red, int green, int blue);
double		GetForms(__constant t_obj *obj, double t, t_ray P, t_ray V, t_ray VA);
double		GenerateLigth(__constant t_obj *obj, __constant t_light *light,t_params *par, t_ray P, t_ray N, t_ray V, float specular);
float		RayLenght(t_ray r);
float		__OVERLOAD__ dot(t_ray a, t_ray b);

t_ray		global_normal(t_trace *tr, t_ray P);
t_ray		matrix_rotate(double a, double b, double c, t_ray r);
t_ray		ray_multipl(double a, t_ray b);
t_ray		ray_summary(t_ray a, t_ray b);
t_ray		divide_ray(t_ray a, float b);
t_ray		ray_subs(t_ray a, t_ray b);
t_ray		normal(t_ray a);
t_ray		ReflectRay(t_ray R, t_ray N);
t_ray		SetCameraPosititon(t_params par, float x, float y);
float2	discriminant(float k[3]);
float2	NewCylinder(__constant t_obj *obj, t_ray P, t_ray V);
float2	NewCone(__constant t_obj *obj, t_ray P, t_ray V);
float2	NewSphere(__constant t_obj *obj, t_ray O, t_ray D);
float2	NewPlane(__constant t_obj *obj, t_ray O, t_ray D);

float	RayLenght(t_ray ray)
{
	return (sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z));
}

t_ray	ray_summary(t_ray a, t_ray b)
{
	return ((t_ray){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_ray	ray_multipl(double a, t_ray b)
{
	return ((t_ray){a * b.x, a * b.y, a * b.z});
}

int		RgbToInt(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
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

t_ray	SetCameraPosititon(t_params par, float x, float y)
{
	return ((t_ray){x * par.viewport.w / par.screenw, y * par.viewport.h / par.screenh, par.viewport.dist * 2});
}

t_ray	matrix_rotate(double a, double b, double c, t_ray r)
{
	return ((t_ray){((cos(b) * cos(c)) * r.x) + ((cos(c) * sin(a) * sin(b)
	 - cos(a) * sin(c)) * r.y) + ((cos(a) * cos(c) * sin(b) + sin(a) * sin(c)) * r.z), 
	((cos(b) * sin(c)) * r.x) + ((cos(a) * cos(c) + sin(a) * sin(b) * sin(c)) * r.y)
	 + ((-cos(c) * sin(a) + cos(a) * sin(b) * sin(c)) * r.z),((-sin(b)) * r.x) +
	  ((cos(b) * sin(a)) * r.y) + ((cos(a) * cos(b)) * r.z)});
}

t_ray	normal(t_ray a)
{
	return (divide_ray(a, RayLenght(a)));
}


float	__OVERLOAD__ dot(t_ray a, t_ray b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_ray	ReflectRay(t_ray R, t_ray N)
{
    return (ray_subs(ray_multipl(dot(N, R), ray_multipl(2.0, N)), R));
}

double		GenerateLigth(__constant t_obj *obj, __constant t_light *light, t_params *par,	t_ray P, t_ray N, t_ray V, float spec)
{
	double		intens;
	int			j;
	t_ray		L;
	t_ray		R;
	float		nl;
	float		rv;
	float		max;
	t_trace		shadows;

	intens = 0.0;
	j = -1;
	while (++j < par->lights)
	{
		if (light[j].type == GLOBAL)
			intens += light[j].intensity;
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
			if (dot(V, N) < 0)
				continue ;
			ClosestIntersection(obj, &shadows, par, P, L, 0.001, max);
			if (shadows.closest_intersect != INFINITY)
				continue ;
			nl = dot(N, L);
			if (nl > 0)
				intens += light[j].intensity * nl / (RayLenght(N) * RayLenght(L));
			if (spec >= 0)
			{
				R = ray_subs(ray_multipl(dot(N, L), ray_multipl(2.0, N)), L);
				rv = dot(R, V);
				if (rv > 0)
					intens += light[j].intensity * pow(rv / (RayLenght(R) * RayLenght(V)), spec);
			}
		}
	}
	intens > 1.0 ? intens = 1.0 : 0;
	return (intens);
}

float2	discriminant(float k[3])
{
	float	d;

	d =  k[1] * k[1] - 4.0f * k[0] * k[2];
	if (d < 0)
		return ((float2){INFINITY, INFINITY});
	return ((float2){(-k[1] + sqrt(d)) / (2.0f * k[0]), (-k[1] - sqrt(d)) / (2.0f * k[0])});
}

double		GetForms(__constant t_obj *obj, double t, t_ray P, t_ray V, t_ray VA)
{
	if (t < 0)
		return (INFINITY);
	P.k[0] = dot(VA, ray_subs(ray_summary(P, ray_multipl(t, V)), obj->mid));
	P.k[1] = dot(VA, ray_subs(ray_summary(P, ray_multipl(t, V)), obj->direction));
	if (P.k[0] < 0.0 && P.k[1] > 0.0)
		return (t);
	return (INFINITY);
}

float2	NewSphere(__constant t_obj *obj, t_ray O, t_ray D)
{
	float k[3];
	float3 c;

	D.k[0] = dot(D, D);
	c.x = D.k[0];
	D.k[1] = 2.0f * dot(ray_subs(O, obj->mid), D);
	c.y = D.k[1];
	D.k[2] = dot(ray_subs(O, obj->mid), ray_subs(O, obj->mid)) - obj->radius * obj->radius;
	c.z = D.k[2];
	return (discriminant(D.k));
}


float2	NewCone(__constant t_obj *obj, t_ray P, t_ray V)
{
	float	angle;
	float	cospw;
	float	sinpw;
	t_ray	VA;
	t_ray	deltaP;
	t_ray	A;
	t_ray	B;
	float2	t;

	angle = (obj->angle * M_PI) / 180;
	VA = normal(ray_subs(obj->mid, obj->direction));
	deltaP = ray_subs(P, obj->mid);
	A = ray_subs(V, ray_multipl(dot(V, VA), VA));
	B = ray_subs(deltaP, ray_multipl(dot(deltaP, VA), VA));
	cospw = cos(angle) * cos(angle);
	sinpw = sin(angle) * sin(angle);

	P.k[0] = cospw * dot(A, A) - sinpw * dot(V, VA) * dot(V, VA);
	P.k[1] = 2.0f * cospw * dot(A, B) - 2.0f * sinpw * dot(V, VA) * dot(deltaP, VA);
	P.k[2] = cospw * dot(B, B) - sinpw * dot(deltaP, VA) * dot(deltaP, VA);
	t = discriminant(P.k);
	return ((float2){GetForms(obj, t.x, P, V, VA), GetForms(obj, t.y, P, V, VA)});
}

float2	NewCylinder(__constant t_obj *obj, t_ray P, t_ray V)
{
	t_ray	Normal;
	t_ray	deltaP;
	t_ray	A;
	t_ray	B;
	float2	t;

	Normal = normal(ray_subs(obj->mid, obj->direction));
	deltaP = ray_subs(P, obj->mid);

	A = ray_subs(V, ray_multipl(dot(V, Normal), Normal));
	B = ray_subs(deltaP, ray_multipl(dot(deltaP, Normal), Normal));
	P.k[0] = dot(A, A);
	P.k[1] = 2.0f * dot(A, B);
	P.k[2] = dot(B, B) - obj->radius * obj->radius;
	t = discriminant(P.k);
	return ((float2){GetForms(obj, t.x, P, V, Normal), GetForms(obj, t.y, P, V, Normal)});
}


float2	NewPlane(__constant t_obj *obj, t_ray O, t_ray D)
{
	t_ray	X;
	t_ray	C;
	t_ray	N;
	float2	t;
	float	k[2];

	C = obj->mid;
	N = obj->direction;
	X = ray_subs(O, C);
	k[0] = dot(D, N);
	k[1] = dot(X, N);
	if (k[0])
	{
		t.x = -k[1] / k[0];
		t.y = INFINITY;
		return (t);		
	}
	return ((float2){INFINITY, INFINITY});
}

int		ClosestIntersection(__constant t_obj *obj, t_trace *tr, t_params *par,
								t_ray O, t_ray D, float t_min, float t_max)
{
	int			i;
	float2	t;

	tr->closest_intersect = INFINITY;
	i = -1;
	while (++i < par->objects)
	{
		if (obj[i].type == SPHERE)
			t = NewSphere(&obj[i], O, D);
		else if (obj[i].type == PLANE)
			t = NewPlane(&obj[i], O, D);
		else if (obj[i].type == CYLINDER)
			t = NewCylinder(&obj[i], O, D);
		else if (obj[i].type == CONE)
			t = NewCone(&obj[i], O, D);
		if (t.x > t_min && t.x < t_max && t.x < tr->closest_intersect)
		{
			tr->closest_intersect = t.x;
			tr->closest_object = obj[i];
		}
		if (t.y > t_min && t.y < t_max && t.y < tr->closest_intersect)
		{
			tr->closest_intersect = t.y;
			tr->closest_object = obj[i];
		}
	}
	return (tr->closest_intersect);
}

t_ray	global_normal(t_trace *tr, t_ray P)
{
	t_ray	Normal;
	t_ray	center;
	t_ray	projection;

	if (tr->closest_object.type == SPHERE)
	{
		Normal = ray_subs(P, tr->closest_object.mid);
		Normal = normal(Normal);
		return (Normal);
	}
	if (tr->closest_object.type == CYLINDER || tr->closest_object.type == CONE)
	{
		center = normal(ray_subs(tr->closest_object.direction, tr->closest_object.mid));
		Normal = ray_subs(P, tr->closest_object.mid);
		projection = ray_multipl(dot(Normal, center), center);
		Normal = ray_subs(Normal, projection);
		Normal = normal(Normal);
		return (Normal);
	}
	Normal = tr->closest_object.direction;
	return (Normal);
}

int		RayTracer(__constant t_obj *obj, __constant t_light *light, t_params par, float t_min, float t_max)
{
	t_trace		tr;
	t_ray		P;
	t_ray		N;
	t_ray		color[RECURS + 1];
	int			recurs;
	double		intensity;
	t_ray		DD;

	recurs = 0;
	while (recurs <= RECURS)
	{
		color[recurs] = (t_ray){0, 0, 0, 0};
		recurs++;
	}
	recurs = RECURS;
	while (recurs >= 0)
	{
		ClosestIntersection(obj, &tr, &par, par.O, par.Dimention, t_min, t_max);
		if (tr.closest_intersect == INFINITY)
		{
			color[recurs] = (t_ray){0, 0 ,0};
			break ;
		}
		P = ray_summary(par.O, ray_multipl(tr.closest_intersect, par.Dimention)); //compute intersection
		N = global_normal(&tr, P);
		DD = (t_ray){-par.Dimention.x, -par.Dimention.y, -par.Dimention.z, 0};
		intensity = GenerateLigth(obj, light, &par, P, N, DD, tr.closest_object.specular);
		color[recurs] = ray_multipl(intensity, tr.closest_object.color);
		color[recurs].reflect = tr.closest_object.reflect;
		if (tr.closest_object.reflect > 0)
		{
			par = (t_params){P, ReflectRay(DD, N), par.camera_rot, par.obj, par.light, par.viewport,  par.t_min,
				par.t_max, par.color, par.objects, par.lights, par.screenw, par.screenh}; // peredacha dannuyh structure PO POSITCIAM!
			recurs--;
		}
		else
			break ;
	}
	recurs = -1;
	while (++recurs < RECURS)
	{
		color[recurs + 1] = ray_summary(ray_multipl(1 - color[recurs + 1].reflect, color[recurs + 1]),
						ray_multipl(color[recurs + 1].reflect, color[recurs]));
	}
	return (RgbToInt(color[recurs].x, color[recurs].y, color[recurs].z));
}

__kernel
void	render(__global int *img_pxl, t_params params, __constant t_obj *obj, __constant t_light *light)
{
	int x = get_global_id(0);
	int y = get_global_id(1);

	params.Dimention = matrix_rotate(params.camera_rot.x, params.camera_rot.y, params.camera_rot.z,
		SetCameraPosititon(params, x - params.screenw / 2, params.screenh / 2 - y));
	img_pxl[x + y * params.screenw] = RayTracer(obj, light, params, 0.001f, INFINITY);
}
