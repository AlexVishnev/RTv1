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

# ifndef M_PI
#  define M_PI           3.14159265358979323846  /* pi */
# endif


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
float3		matrix_rotate(float a, float b, float c, float3 r);
int 		ClosestIntersection(__constant t_obj *obj, t_trace *tr, t_params *par,
							float3 O, float3 D, float t_min, float t_max);
float3		GlobalNormal(t_trace *tr, float3 P);
float3		ReflectRay(float3 R, float3 N);
float2		Intersect_Cylinder(__constant t_obj *obj, float3 P, float3 V);
double		GetForms(__constant t_obj *obj, double t, float3 P, float3 V, float3 VA);
float2		Intersect_Cone(__constant t_obj *obj, float3 P, float3 V);
float2		Inersect_Sphere(__constant t_obj *obj, float3 O, float3 D);
float2		Intersect_Plane(__constant t_obj *obj, float3 O, float3 D);
double		GenerateLigth(__constant t_obj *obj, __constant t_light *light, t_params *par,	float3 P, float3 N, float3 V, float spec);

int		RgbToInt(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}



float3	SetCameraPosititon(t_params par, float x, float y)
{
	return ((float3){x * par.viewport.w / par.screenw, y * par.viewport.h / par.screenh, par.viewport.dist * 2});
}


float3	matrix_rotate(float a, float b, float c, float3 r)
{
	float 	sin_a = native_sin(a);
	float 	sin_b = native_sin(b);
	float 	sin_c = native_sin(c);
	float 	cos_a = native_cos(a);
	float 	cos_b = native_cos(b);
	float 	cos_c = native_cos(c);

	return ((float3){((cos_b * cos_c) * r.x) + ((cos_c * sin_a * sin_b
	 - cos_a * sin_c) * r.y) + ((cos_a * cos_c * sin_b + sin_a * sin_c) * r.z), 
	((cos_b * sin_c) * r.x) + ((cos_a * cos_c + sin_a * sin_b * sin_c) * r.y)
	 + ((-cos_c * sin_a + cos_a * sin_b * sin_c) * r.z),((-sin_b) * r.x) +
	  ((cos_b * sin_a) * r.y) + ((cos_a * cos_b) * r.z)});
}



float3	ReflectRay(float3 R, float3 N)
{
	return (dot(N, R) * (2.0f * N)) - R;
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
	while (isless(++j, par->lights))
	{
		if (isequal(light[j].type, GLOBAL))
			intens += light[j].intensity;
		else
		{
			if (isequal(light[j].type, POINT))
			{
				L = light[j].position - P;
				max = 0.99f;
			}
			else
			{
				L = light[j].direction;
				max = INFINITY;
			}
			if (isequal(dot(V, N), 0))
				continue ;
			ClosestIntersection(obj, &shadows, par, P, L, 0.001, max);
			if (isnotequal(shadows.closest_intersect, INFINITY))
				continue ;
			nl = dot(N, L);
			if (isgreater(nl, 0))
				intens += light[j].intensity * nl / (length(N) * length(L));
			if (isgreaterequal(spec, 0))
			{
				R = nl * (2.0f * N) - L;
				rv = dot(R, V);
				if (isgreater(rv, 0))
					intens += light[j].intensity * pow(rv / (length(R) * length(V)), spec);
			}
		}
	}
	isgreater(intens, 1.0) ? intens = 1.0 : 0;
	return (intens);
}

float2	discriminant(float3 k)
{
	float	d;
	float 	sqrt_d;

	d =  k.y * k.y - 4.0f * k.x * k.z;
	sqrt_d = native_sqrt(d);
	if (isless(d, 0))
		return ((float2){INFINITY, INFINITY});
	return ((float2){(-k.y + sqrt_d) / (2.0f * k.x), (-k.y - sqrt_d) / (2.0f * k.x)});
}


double		GetForms(__constant t_obj *obj, double t, float3 P, float3 V, float3 VA)
{
	float2 k;

	if (isless(t, 0))
		return (INFINITY);
	k.x = dot(VA, (P + (float)t * V) - obj->mid);
	k.y = dot(VA, (P + (float)t * V) - obj->direction);
	if (isless (k.x, 0.0) && isgreater (k.y, 0.0))
		return (t);
	return (INFINITY);
}


float2	Inersect_Sphere(__constant t_obj *obj, float3 O, float3 D)
{
	float3 c;

	c.x = dot(D, D);
	c.y = 2.0f * dot((O - obj->mid), D);
	c.z = dot((O - obj->mid), (O - obj->mid)) - obj->radius * obj->radius;
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
	VA = fast_normalize(obj->mid - obj->direction);
	deltaP = P - obj->mid;
	A = V - (dot(V, VA) * VA);
	B = deltaP - (dot(deltaP, VA) * VA);
	cospw = native_cos(angle) * native_cos(angle);
	sinpw = native_sin(angle) * native_sin(angle);

	v.x = cospw * dot(A, A) - sinpw * dot(V, VA) * dot(V, VA);
	v.y = 2.0f * cospw * dot(A, B) - 2.0f * sinpw * dot(V, VA) * dot(deltaP, VA);
	v.z = cospw * dot(B, B) - sinpw * dot(deltaP, VA) * dot(deltaP, VA);

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

	Normal = fast_normalize(obj->mid - obj->direction);
	deltaP = P - obj->mid;

	A = V - (dot(V, Normal) * Normal);
	B = deltaP - (dot(deltaP, Normal) * Normal);
		
	v.x = dot(A, A);
	v.y = 2.0f * dot(A, B);
	v.z = dot(B, B) - obj->radius * obj->radius;
	t = discriminant(v);
	return ((float2){GetForms(obj, t.x, P, V, Normal), GetForms(obj, t.y, P, V, Normal)});

}

float2	Intersect_Plane(__constant t_obj *obj, float3 O, float3 D)
{
	float2	k;

	k.x = dot(D, obj->direction);
	k.y = dot(O - obj->mid, obj->direction);
	if (k.x)
		return ((float2){-k.y / k.x, INFINITY});
	return ((float2){INFINITY, INFINITY});
 }

int		ClosestIntersection(__constant t_obj *obj, t_trace *tr, t_params *par,
								float3 O, float3 D, float t_min, float t_max)
{
	int			i;
	float2	t;

	tr->closest_intersect = INFINITY;
	i = -1;
	while (isless(++i, par->objects))
	{
		if (isequal(obj[i].type, SPHERE))
			t = Inersect_Sphere(&obj[i], O, D);
		else if (isequal(obj[i].type, PLANE))
			t = Intersect_Plane(&obj[i], O, D);
		else if (isequal(obj[i].type, CYLINDER))
			t = Intersect_Cylinder(&obj[i], O, D);
		else if (isequal(obj[i].type, CONE))
			t = Intersect_Cone(&obj[i], O, D);
		if (isgreater(t.x, t_min) && isless(t.x, t_max) && isless(t.x, tr->closest_intersect))
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

	if (isequal(tr->closest_object.type, SPHERE))
	{
		Normal = P - tr->closest_object.mid;
		return (fast_normalize(Normal));
	}
	if (isequal(tr->closest_object.type, CYLINDER) || isequal(tr->closest_object.type, CONE))
	{
		center = fast_normalize(tr->closest_object.direction - tr->closest_object.mid);
		Normal = P - tr->closest_object.mid;
		projection = (dot(Normal, center) * center);
		Normal -= (dot(Normal, center) * center);
		return (fast_normalize(Normal));
	}
	return (tr->closest_object.direction);
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
	while (islessequal(recurs, RECURS))
	{
		color[recurs] = 0;
		recurs++;
	}
	recurs = RECURS;
	while (isgreaterequal(recurs, 0))
	{

		ClosestIntersection(obj, &tr, &par, par.O, par.Direct, t_min, t_max);
		if (isinf(tr.closest_intersect))
		{
			color[recurs] = 0;
			break ;
		}
		P = par.O + (float)tr.closest_intersect * par.Direct;  //compute intersection
		N = GlobalNormal(&tr, P);
		DD = (float3){-par.Direct.x, -par.Direct.y, -par.Direct.z};
		intensity = GenerateLigth(obj, light, &par, P, N, DD, tr.closest_object.specular); //NATIVE
		color[recurs] = (float)intensity * tr.closest_object.color;
		color[recurs].w = tr.closest_object.reflect;
		if (isgreater(tr.closest_object.reflect, 0))
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
	while (isless(++recurs, RECURS))
	{
		color[recurs + 1] = (1 - color[recurs + 1].w) * color[recurs + 1] +
						(color[recurs + 1].w * color[recurs]); // compute reflection
		
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
	barrier(CLK_GLOBAL_MEM_FENCE);
	img_pxl[x + y * params.screenw] = RayTracer(obj, light, params, 0.001f, INFINITY);
}
