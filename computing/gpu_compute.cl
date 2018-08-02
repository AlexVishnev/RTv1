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
# define SAMPLE 4

# ifndef M_PI
#  define M_PI           3.14159265358979323846  /* pi */
# endif

typedef	struct			s_light
{
	int					type;
	float				intensity;
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
	float			closest_intersect;
	t_obj			closest_object;
	float2			t;
}				t_trace;

typedef	struct	s_params
{
	float3		O;
	float3		Ray;
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
	int 		color_filter;
	int			stop_real_mode;
	int 		ssaa_flag;
}				t_params;


int			convert_color(int color[], int max_arr_size);
float3 		Refract(float3 D,  float3 N,  float ior);
int			RayTracer(__constant t_obj *obj, __constant t_light *light, t_params par, float t_min, float t_max);
int			ColorFilters(int red, int green, int blue, int flag, t_params par);
float2		discriminant(float3 k);

float3		SetCameraPosititon(t_params par, float x, float y);
float3		matrix_rotate(float a, float b, float c, float3 r);
int 		ClosestIntersection(__constant t_obj *obj, t_trace *tr, t_params *par,
							float3 O, float3 D, float t_min, float t_max);
float3		GlobalNormal(t_trace *tr, float3 P);
float3		ReflectRay(float3 R, float3 N);
float2		Intersect_Cylinder(__constant t_obj *obj, float3 P, float3 V);
float		GetForms(__constant t_obj *obj, float t, float3 P, float3 V, float3 VA);
float2		Intersect_Cone(__constant t_obj *obj, float3 P, float3 V);
float2		Inersect_Sphere(__constant t_obj *obj, float3 O, float3 D);
float2		Intersect_Plane(__constant t_obj *obj, float3 O, float3 D);
float		GenerateLigth(__constant t_obj *obj, __constant t_light *light, t_params *par,	float3 P, float3 N, float3 V, float spec);
float		fresnel(float3 D, float3 N, float ior, float kr);

int			set_carton(int red, int green, int blue);
int			set_sepia(int red, int green, int blue);
int			set_bw (int red, int green, int blue);
int			set_negative (int r, int g, int b);

int	set_carton(int r, int g, int b)
{
	r = ((int)(r * 10.0f)) / 10.0f;
	g = ((int)(g * 10.0f)) / 10.0f;
	b = ((int)(b * 10.0f)) / 10.0f;

	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

int	set_sepia(int r, int g, int b)
{
	float		sum;

	sum = (r + g + b) / 3.0f;
	r = sum + 25.2f;
	g = sum + 30.1f;
	b = sum;
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

int	set_bw(int r, int g, int b)
{
	int		sum;

	sum = (r + g + b) / 3.f;
	r = sum;
	g = sum;
	b = sum;
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

int set_negative (int r, int g, int b)
{
	r = 255 - r;
	g = 255 - g;
	b = 255 - b;
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

int	set_stereoskop(int r, int g, int b, int flag)
{
	if (isequal(flag, 5))
		r = 0;
	else if (isequal(flag, 6))
		g = 0;
	else if (isequal(flag,7))
		b = 0;
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

int		ColorFilters(int r, int g, int b, int flag, t_params par)
{
	if (!flag)
		return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
	else if (flag == 1)
		return (set_carton(r,  g, b));
	else if (flag == 2)
		return (set_sepia(r, g, b));
	else if (flag == 3)
		return (set_bw(r, g, b));
	else if (flag == 4)
		return (set_negative(r,g,b));
	else if (flag == 5 || flag == 6 || flag == 7)
		return (set_stereoskop(r,g,b, flag));
	return (r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF);
}

float3	SetCameraPosititon(t_params par, float x, float y)
{
	return ((float3){x * par.viewport.w / par.screenw, y * par.viewport.h / par.screenh, par.viewport.dist});
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

float		GenerateLigth(__constant t_obj *obj, __constant t_light *light, t_params *par,	float3 Point, 
							float3 Normal, float3 V, float spec)
{
	float		intens;
	int			j;
	float3		Light;
	float3		newRay;
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
				Light = light[j].position - Point;
				max = 0.99f;
			}
			else
			{
				Light = light[j].direction;
				max = INFINITY;
			}
			if (isequal(dot(V, Normal), 0))
				continue ;
			ClosestIntersection(obj, &shadows, par, Point, Light, 0.001f, max);
			if (isnotequal(shadows.closest_intersect, INFINITY))
				continue ;
			nl = dot(Normal, Light);
			if (isgreater(nl, 0))
				intens += light[j].intensity * nl / (fast_length(Normal) * fast_length(Light));
			if (isgreater(spec, 0))
			{
				newRay = nl * (2.0f * Normal) - Light;
				rv = dot(newRay, V);
				if (isgreater(rv, 0))
					intens += light[j].intensity * pow(rv / (fast_length(newRay) * fast_length(V)), spec);
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


float		GetForms(__constant t_obj *obj, float t, float3 Point, float3 V, float3 VA)
{
	float2 k;

	if (isless(t, 0))
		return (INFINITY);
	k.x = dot(VA, (Point + t * V) - obj->mid);
	k.y = dot(VA, (Point + t * V) - obj->direction);
	if (isless (k.x, 0.0) && isgreater(k.y, 0.0))
		return (t);
	return (INFINITY);
}


float2	Inersect_Sphere(__constant t_obj *obj, float3 O, float3 Ray)
{
	float3 c;

	c.x = dot(Ray, Ray);
	c.y = 2.0f * dot((O - obj->mid),Ray);
	c.z = dot((O - obj->mid), (O - obj->mid)) - obj->radius * obj->radius;
	return (discriminant(c));
}


float2	Intersect_Cone(__constant t_obj *obj, float3 Point, float3 V)
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
	deltaP = Point - obj->mid;
	A = V - (dot(V, VA) * VA);
	B = deltaP - (dot(deltaP, VA) * VA);
	cospw = native_cos(angle) * native_cos(angle);
	sinpw = native_sin(angle) * native_sin(angle);

	v.x = cospw * dot(A, A) - sinpw * dot(V, VA) * dot(V, VA);
	v.y = 2.0f * cospw * dot(A, B) - 2.0f * sinpw * dot(V, VA) * dot(deltaP, VA);
	v.z = cospw * dot(B, B) - sinpw * dot(deltaP, VA) * dot(deltaP, VA);

	t = discriminant(v);
	return ((float2){GetForms(obj, t.x, Point, V, VA), GetForms(obj, t.y, Point, V, VA)});
}


float2	Intersect_Cylinder(__constant t_obj *obj, float3 Point, float3 V)
{
	float3	Normal;
	float3	deltaP;
	float3	A;
	float3	B;
	float2	t;
	float3	v;

	Normal = fast_normalize(obj->mid - obj->direction);
	deltaP = Point - obj->mid;

	A = V - (dot(V, Normal) * Normal);
	B = deltaP - (dot(deltaP, Normal) * Normal);
		
	v.x = dot(A, A);
	v.y = 2.0f * dot(A, B);
	v.z = dot(B, B) - obj->radius * obj->radius;
	t = discriminant(v);
	return ((float2){GetForms(obj, t.x, Point, V, Normal), GetForms(obj, t.y, Point, V, Normal)});

}

float2	Intersect_Plane(__constant t_obj *obj, float3 O, float3 Ray)
{
	float2	k;
	float3	Normal;

	Normal = fast_normalize(obj->direction);
	k.x = dot(Ray, Normal);
	k.y = (dot(O, Normal) - dot(Normal, obj->mid));
	if (k.x)
		return ((float2){-k.y / k.x, INFINITY});
	return ((float2){INFINITY, INFINITY});


 }

int		ClosestIntersection(__constant t_obj *obj, t_trace *tr, t_params *par,
								float3 O, float3 Ray, float t_min, float t_max)
{
	int			i;
	float2	t;

	tr->closest_intersect = INFINITY;
	i = -1;
	while (isless(++i, par->objects))
	{
		if (isequal(obj[i].type, SPHERE))
			t = Inersect_Sphere(&obj[i], O, Ray);
		else if (isequal(obj[i].type, PLANE))
			t = Intersect_Plane(&obj[i], O, Ray);
		else if (isequal(obj[i].type, CYLINDER))
			t = Intersect_Cylinder(&obj[i], O, Ray);
		else if (isequal(obj[i].type, CONE))
			t = Intersect_Cone(&obj[i], O, Ray);
		if (isgreater(t.x, t_min) && isless(t.x, t_max) && isless(t.x, tr->closest_intersect))
		{
			tr->closest_intersect = t.x;
			tr->closest_object = obj[i];
		}
		if (isgreater(t.y, t_min) && isless(t.y, t_max) && isless(t.y, tr->closest_intersect))
		{
			tr->closest_intersect = t.y;
			tr->closest_object = obj[i];
		}
	}
	return (tr->closest_intersect);
}

float3	GlobalNormal(t_trace *tr, float3 Point)
{
	float3	Normal;
	float3	center;
	float3	projection;

	if (isequal(tr->closest_object.type, SPHERE))
	{
		Normal = Point - tr->closest_object.mid;
		return (fast_normalize(Normal));
	}
	if (isequal(tr->closest_object.type, CYLINDER) || isequal(tr->closest_object.type, CONE))
	{
		center = fast_normalize(tr->closest_object.direction - tr->closest_object.mid);
		Normal = Point - tr->closest_object.mid;
		projection = (dot(Normal, center) * center);
		Normal -= (dot(Normal, center) * center);
		return (fast_normalize(Normal));
	}
	return (fast_normalize(tr->closest_object.direction));
}


float3 Refract(float3 D,  float3 N,  float ior)
{
	float tmp;
	float cosi = clamp(-1.f, 1.f, dot(D, N));
	float etai = 1, etat = ior; 
	float3 n = N;

	if (cosi < 0) 
		cosi = -cosi; 
	else 
	{
		tmp = etai;
		etai = etat;
		etat = tmp;
		n = -N; 
	} 
	float eta = etai / etat; 
	float k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0) 
		return (0);
	return (eta * D + (eta * cosi - sqrtf(k)) * n);
}


float fresnel(float3 D, float3 N, float ior, float kr) 
{
	float tmp;
	float cosi = clamp(-1.f, 1.f, dot(D, N)); 
	float etai = 1, etat = ior; 

	if (cosi > 0) 
	{
		tmp = etai;
		etai = etat;
		etat = tmp;
	} 
	// Compute sini using Snell's law
	float sint = etai / etat * sqrtf(max(0.f, 1 - cosi * cosi)); 
	// Total internal reflection
	if (sint >= 1) 
		kr = 1; 
	else 
	{ 
		float cost = sqrtf(max(0.f, 1 - sint * sint)); 
		cosi = fabsf(cosi); 
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
		kr = (Rs * Rs + Rp * Rp) / 2; 
	} 
	// As a consequence of the conservation of energy, transmittance is given by:
	// kt = 1 - kr;
	return kr;
}


int		RayTracer(__constant t_obj *obj, __constant t_light *light, t_params par, float t_min, float t_max)
{
	t_trace		tr;
	float3		Point;
	float3		Nornal;
	float4		color[RECURS + 1];
	int			recurs;
	float		intensity;

	recurs = 0;
	while (islessequal(recurs, RECURS))
	{
		color[recurs] = 0;
		recurs++;
	}
	recurs = RECURS;
	while (isgreaterequal(recurs, 0))
	{
		ClosestIntersection(obj, &tr, &par, par.O, par.Ray, t_min, t_max);
		if (isinf(tr.closest_intersect))
		{
			color[recurs] = 0;
			break ;
		}
		Point = par.O + tr.closest_intersect * par.Ray;
		Nornal = GlobalNormal(&tr, Point);
		intensity = GenerateLigth(obj, light, &par, Point, Nornal, -par.Ray, tr.closest_object.specular);
		color[recurs] = intensity * tr.closest_object.color;
		color[recurs].w = tr.closest_object.reflect;

		if (isgreater(tr.closest_object.reflect, 0))
		{
			if (isequal(par.stop_real_mode, 1))
			{
				par.Ray = (dot(Nornal, -par.Ray) * 2.0f * Nornal) + par.Ray;
				par.O = Point;
			}
			else 
				par.Ray = (dot(Nornal, -par.Ray) * 2.0f * Nornal) + par.Ray; 
			recurs--;
		}
		else
			break ;
	}
	recurs = -1;
	while (isless(++recurs, RECURS))
	{
		color[recurs + 1] = (1 - color[recurs + 1].w) * color[recurs + 1] +	
		(color[recurs + 1].w * color[recurs]);
	}
	return (ColorFilters(color[recurs].x, color[recurs].y, color[recurs].z, par.color_filter, par));
}

int convert_color(int color[], int array_size)
{
	int		ssaa;
	int 	i;

	i = 0;
	ssaa = 0;
	while (isless(i, array_size))
	{
		ssaa += color[i];
		i++;
	}
	return ssaa / array_size;
}

__kernel
void	render(__global int *img_pxl, t_params params, __constant t_obj *obj, __constant t_light *light)
{
	int x = get_global_id(0);
	int y = get_global_id(1);


	int sample;
	if (isequal(params.ssaa_flag, 42))
		sample = 4;
	sample = 1;
	int color[sample];
    float3 dirs[sample];

	params.Ray = matrix_rotate(params.camera_rot.x, params.camera_rot.y, params.camera_rot.z,
		SetCameraPosititon(params, x - params.screenw / 2, params.screenh / 2 - y));
	barrier(CLK_GLOBAL_MEM_FENCE);
	int i = 0;
    if (isequal(sample, 4))
    {
        dirs[0] = params.Ray + (float3)(0.25, 0.25, 0.);
        dirs[1] = params.Ray + (float3)(0.25, -0.25, 0.);
        dirs[2] = params.Ray + (float3)(-0.25, 0.25, 0.);
        dirs[3] = params.Ray + (float3)(-0.25, -0.25, 0.);
    }
	while (isless( i, sample))
	{
		color[i] = RayTracer(obj, light, params, 0.001f, INFINITY);
		i++;
	}
	img_pxl[x + y * params.screenw] = convert_color(color, sample);
}
