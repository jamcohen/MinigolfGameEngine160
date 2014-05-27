#version 150

in vec3 N;
in vec4 color;
out vec3 fColor;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform vec3 light;
uniform vec3 eye;
uniform float Shininess;
void main()
{
    
    vec3 L = normalize( light );
    vec3 E = normalize( eye );
    vec3 H = normalize( L + E );
    
    //Compute terms in the illumination equation
    vec4 ambient = AmbientProduct*color;
    
    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct*color;
    
    float Ks = pow( max(dot(N, H), 0.0), 50 );
    vec4  specular = Ks * SpecularProduct*color;
    
	vec4 finalColor = ambient + diffuse + specular;
    if( dot(L, N) < 0.0 ) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
		diffuse = vec4(0.0, 0.0, 0.0, 1.0);
		finalColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
	fColor = finalColor.xyz;
}

