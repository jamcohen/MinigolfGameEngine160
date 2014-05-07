#version 150 


in  vec4 vPosition;
in  vec3 normal;
in  vec3 vColor;
out vec4 color;
out vec3 N;

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;
void main()
{

	mat4 model_view = camera*model;
    // Transform vertex  position into eye coordinates
    vec3 pos = (model_view * vPosition).xyz;
	
    //Transform vertex normal into eye coordinates
    N = normalize( inverse(transpose(model))*vec4(normal, 0.0) ).xyz;
    
    /*vec3 L = normalize( light );
    vec3 E = normalize( (eye.xyz) );
    vec3 H = normalize( L + E );

    //Compute terms in the illumination equation
    vec4 ambient = AmbientProduct*vec4(vColor, 1.0);

    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct*vec4(vColor, 1.0);

    float Ks = pow( max(dot(N, H), 0.0), 50 );
    vec4  specular = Ks * SpecularProduct;
    
	color = ambient + diffuse+specular*vec4(vColor, 1.0);
    if( dot(L, N) < 0.0 ) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
		diffuse = vec4(0.0, 0.0, 0.0, 1.0);
		color = vec4(0.0, 0.0, 0.0, 1.0);
    }*/

    gl_Position = projection * model_view * vPosition;
    
    color = vec4(vColor, 1.0);
    color.a = 1.0;
}