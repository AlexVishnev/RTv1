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
}						t_ray;

typedef	struct			s_light
{
	int					type;
	double				intensity;
	float3				position;
	float3				direction;
}						t_light;

typedef	struct		s_obj
{
	int				type;
	float3			mid;
	float3			direction;
	float4			color;
	float			specular;
	float			radius;
	float			reflect;
	float			angle;
}					t_obj;


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
	float3		O;
	float3		Direct;
	float3		camera_rot;
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

int			RgbToInt(int red, int green, int blue);


float2		discriminant(float3 k);


float3		SetCameraPosititon(t_params par, float x, float y);
float3		matrix_rotate(double a, double b, double c, float3 r);
int 		ClosestIntersection(__constant t_obj *obj, t_trace *tr, t_params *par,
							float3 O, float3 D, float t_min, float t_max);
float3		GlobalNormal(t_trace *tr, float3 P);
float3		normal(float3 a);
float3		ReflectRay(float3 R, float3 N);
float		RayLenght(float3 ray);
float2		Intersect_Cylinder(__constant t_obj *obj, float3 P, float3 V);
double		GetForms(__constant t_obj *obj, double t, float3 P, float3 V, float3 VA);
float2		Intersect_Cone(__constant t_obj *obj, float3 P, float3 V);
float2		Inersect_Sphere(__constant t_obj *obj, float3 O, float3 D);
float2		Intersect_Plane(__constant t_obj *obj, float3 O, float3 D);
double		GenerateLigth(__constant t_obj *obj, __constant t_light *light, t_params *par,	float3 P, float3 N, float3 V, float spec);
float3		ray_multipl(double a, float3 b);
float3		ray_summary(float3 a, float3 b);
float3		divide_ray(float3 a, float b);
float3		ray_subs(float3 a, float3 b);
float		ft_dot(float3 a, float3 b);




float	RayLenght(float3 ray)
{
	return (sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z));
}

float3	ray_summary(float3 a, float3 b)
{
	return ((float3){a.x + b.x, a.y + b.y, a.z + b.z});
}



float3	ray_multipl(double a, float3 b)
{
	return ((float3){a * b.x, a * b.y, a * b.z});
}

int		RgbToInt(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}


float3	divide_ray(float3 a, float b)
{
	if (b == 0)
		return (a);
	return ((float3){a.x / b, a.y / b, a.z / b});
}


float3	ray_subs(float3 a, float3 b)
{
	return ((float3){a.x - b.x, a.y - b.y, a.z - b.z});
}


float3	SetCameraPosititon(t_params par, float x, float y)
{
	return ((float3){x * par.viewport.w / par.screenw, y * par.viewport.h / par.screenh, par.viewport.dist * 2});
}


float3	matrix_rotate(double a, double b, double c, float3 r)
{
	return ((float3){((cos(b) * cos(c)) * r.x) + ((cos(c) * sin(a) * sin(b)
	 - cos(a) * sin(c)) * r.y) + ((cos(a) * cos(c) * sin(b) + sin(a) * sin(c)) * r.z), 
	((cos(b) * sin(c)) * r.x) + ((cos(a) * cos(c) + sin(a) * sin(b) * sin(c)) * r.y)
	 + ((-cos(c) * sin(a) + cos(a) * sin(b) * sin(c)) * r.z),((-sin(b)) * r.x) +
	  ((cos(b) * sin(a)) * r.y) + ((cos(a) * cos(b)) * r.z)});
}

float3	normal(float3 a)
{
	return (divide_ray(a, RayLenght(a)));
}

float	ft_dot(float3 a, float3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}


float3	ReflectRay(float3 R, float3 N)
{
	// return (dot(N, R) * (2.0f * N)) - R;
    return (ray_subs(ray_multipl(ft_dot(N, R), ray_multipl(2.0, N)), R));
}

double		GenerateLigth(__constant t_obj *obj, __constant t_light *light, t_params *par,	float3 P, float3 N, float3 V, float spec)
{
	double		intens;
	int			j;
	float3		L;
	float3		R;
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
			if (ft_dot(V, N) < 0)
				continue ;
			ClosestIntersection(obj, &shadows, par, P, L, 0.001, max);
			if (shadows.closest_intersect != INFINITY)
				continue ;
			nl = ft_dot(N, L);
			if (nl > 0)
				intens += light[j].intensity * nl / (RayLenght(N) * RayLenght(L));
			if (spec >= 0)
			{
				R = ray_subs(ray_multipl(ft_dot(N, L), ray_multipl(2.0, N)), L);
				rv = ft_dot(R, V);
				if (rv > 0)
					intens += light[j].intensity * pow(rv / (RayLenght(R) * RayLenght(V)), spec);
			}
		}
	}
	intens > 1.0 ? intens = 1.0 : 0;
	return (intens);
}

float2	discriminant(float3 k)
{
	float	d;

	d =  k.y * k.y - 4.0f * k.x * k.z;
	if (d < 0)
		return ((float2){INFINITY, INFINITY});
	return ((float2){(-k.y + sqrt(d)) / (2.0f * k.x), (-k.y - sqrt(d)) / (2.0f * k.x)});
}


double		GetForms(__constant t_obj *obj, double t, float3 P, float3 V, float3 VA)
{
	float2 k;

	if (t < 0)
		return (INFINITY);
	k.x = ft_dot(VA, ray_subs(ray_summary(P, ray_multipl(t, V)), obj->mid));
	k.y = ft_dot(VA, ray_subs(ray_summary(P, ray_multipl(t, V)), obj->direction));
	if (k.x < 0.0 && k.y > 0.0)
		return (t);
	return (INFINITY);
}


float2	Inersect_Sphere(__constant t_obj *obj, float3 O, float3 D)
{
	float3 c;

	c.x = ft_dot(D, D);
	c.y = 2.0f * ft_dot(ray_subs(O, obj->mid), D);
	c.z = ft_dot(ray_subs(O, obj->mid), ray_subs(O, obj->mid)) - obj->radius * obj->radius;
	return (discriminant(c));
}


float2	Intersect_Cone(__constant t_obj *obj, float3 P, float3 V)
{
	float	angle;
	float	cospw;
	float	sinpw;
	float3	VA;
	float3	deltaP;
	float3	A;
	float3	B;
	float2	t;
	float3	v;

	angle = (obj->angle * M_PI) / 180;
	VA = normal(ray_subs(obj->mid, obj->direction));
	deltaP = ray_subs(P, obj->mid);
	A = ray_subs(V, ray_multipl(ft_dot(V, VA), VA));
	B = ray_subs(deltaP, ray_multipl(ft_dot(deltaP, VA), VA));
	cospw = cos(angle) * cos(angle);
	sinpw = sin(angle) * sin(angle);

	v.x = cospw * ft_dot(A, A) - sinpw * ft_dot(V, VA) * ft_dot(V, VA);
	v.y = 2.0f * cospw * ft_dot(A, B) - 2.0f * sinpw * ft_dot(V, VA) * ft_dot(deltaP, VA);
	v.z = cospw * ft_dot(B, B) - sinpw * ft_dot(deltaP, VA) * ft_dot(deltaP, VA);

	t = discriminant(v);
	return ((float2){GetForms(obj, t.x, P, V, VA), GetForms(obj, t.y, P, V, VA)});
}


float2	Intersect_Cylinder(__constant t_obj *obj, float3 P, float3 V)
{
	float3	Normal;
	float3	deltaP;
	float3	A;
	float3	B;
	float2	t;
	float3	v;

	Normal = normal(ray_subs(obj->mid, obj->direction));
	deltaP = ray_subs(P, obj->mid);

	A = ray_subs(V, ray_multipl(ft_dot(V, Normal), Normal));
	B = ray_subs(deltaP, ray_multipl(ft_dot(deltaP, Normal), Normal));
		
	v.x = ft_dot(A, A);
	v.y = 2.0f * ft_dot(A, B);
	v.z = ft_dot(B, B) - obj->radius * obj->radius;
	t = discriminant(v);
	return ((float2){GetForms(obj, t.x, P, V, Normal), GetForms(obj, t.y, P, V, Normal)});

}

float2	Intersect_Plane(__constant t_obj *obj, float3 O, float3 D)
{
	float3	X;
	float3	C;
	float3	N;
	float2	t;
	float2	k;

	C = obj->mid;
	N = obj->direction;
	X = ray_subs(O, C);
	k.x = ft_dot(D, N);
	k.y = ft_dot(X, N);
	if (k.x)
	{
		t.x = -k.y / k.x;
		t.y = INFINITY;
		return (t);		
	}
	return ((float2){INFINITY, INFINITY});
 }

int		ClosestIntersection(__constant t_obj *obj, t_trace *tr, t_params *par,
								float3 O, float3 D, float t_min, float t_max)
{
	int			i;
	float2	t;

	tr->closest_intersect = INFINITY;
	i = -1;
	while (++i < par->objects)
	{
		if (obj[i].type == SPHERE)
			t = Inersect_Sphere(&obj[i], O, D);
		else if (obj[i].type == PLANE)
			t = Intersect_Plane(&obj[i], O, D);
		else if (obj[i].type == CYLINDER)
			t = Intersect_Cylinder(&obj[i], O, D);
		else if (obj[i].type == CONE)
			t = Intersect_Cone(&obj[i], O, D);
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


float3	GlobalNormal(t_trace *tr, float3 P)
{
	float3	Normal;
	float3	center;
	float3	projection;

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
		projection = ray_multipl(ft_dot(Normal, center), center);
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
	float3		P;
	float3		N;
	float4		color[RECURS + 1];
	int			recurs;
	double		intensity;
	float3		DD;


	recurs = 0;
	while (recurs <= RECURS)
	{
		color[recurs] = (float4){0, 0, 0, 0};
		recurs++;
	}
	recurs = RECURS;
	while (recurs >= 0)
	{

		ClosestIntersection(obj, &tr, &par, par.O, par.Direct, t_min, t_max);
		if (tr.closest_intersect == INFINITY)
		{
			color[recurs] = (float4){0, 0, 0, 0};
			break ;
		}
		P = ray_summary(par.O, ray_multipl(tr.closest_intersect, par.Direct)); //compute intersection
		N = GlobalNormal(&tr, P);
		DD = (float3){-par.Direct.x, -par.Direct.y, -par.Direct.z};
		intensity = GenerateLigth(obj, light, &par, P, N, DD, tr.closest_object.specular); //NATIVE
		color[recurs] = (float)intensity * tr.closest_object.color;
		color[recurs].w = tr.closest_object.reflect;
		if (tr.closest_object.reflect > 0)
		{
			// par = (t_params){P, ReflectRay(DD, N),  par.camera_rot, par.obj, par.light, par.viewport,  par.t_min, 
			// par.t_max, par.color, par.objects, par.lights, par.screenw, par.screenh}; // peredacha dannuyh structure PO POSITCIAM! // reflect without viewport; 
			
			par.Direct = ReflectRay(DD, N); // reflect with viewport; 
			recurs--;
		}
		else
			break ;
	}
	recurs = -1;
	while (++recurs < RECURS)
	{
		color[recurs + 1] = (color[recurs + 1].w * color[recurs + 1]) +
						(color[recurs + 1].w * color[recurs]);
		
	}
	return (RgbToInt(color[recurs].x, color[recurs].y, color[recurs].z));
}

__kernel
void	render(__global int *img_pxl, t_params params, __constant t_obj *obj, __constant t_light *light)
{
	int x = get_global_id(0);
	int y = get_global_id(1);

	params.Direct = matrix_rotate(params.camera_rot.x, params.camera_rot.y, params.camera_rot.z,
		SetCameraPosititon(params, x - params.screenw / 2, params.screenh / 2 - y));
	img_pxl[x + y * params.screenw] = RayTracer(obj, light, params, 0.001f, INFINITY);
}