#version 330 core


in vec2 fragCoord;
uniform vec2 resolution;
uniform vec2 center;
uniform float zoom;
uniform int max_iter;


//Taken from Inigo Quilez
vec3 palette( in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    return a + b*cos( 6.283185*(c*t+d) );
}


void main() {
	vec4 color;
	vec2 uv = gl_FragCoord.xy / resolution;
	vec2 c = center + (uv * 4.0 - vec2(2.0)) * (zoom / 4.0);

	vec2 z = vec2(0.0);
	bool escaped = false;
	int i;
	while(i < max_iter) {
		z = vec2((z.x * z.x - z.y * z.y) + c.x, (2.0 * z.x * z.y) + c.y);
		if(length(z) > 2.0) {
			escaped = true;
			break;
		}
		i++;
	}
	if(escaped) {
		color = vec4(palette(float(i)/float(max_iter), vec3(0.155,0.160,0.149),vec3(0.710,0.520,0.401),vec3(0.433,0.990,0.943),vec3(0.995,0.822,0.9)),1.0); 
	} else {
		color = vec4(vec3(0.0),1.0);
	}
	gl_FragColor = color;
}
