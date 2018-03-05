#version 150

#define CONE_SIDES 10

out vec4 outputColor;
uniform float scale;
uniform float iTime;
uniform vec2 coneACenter;
uniform vec4 coneAVerts[CONE_SIDES];
uniform vec2 coneBCenter;
uniform vec4 coneBVerts[CONE_SIDES];
  
#define MOD3 vec3(.1031,.11369,.13787)
//#define MOD3 vec3(443.8975,397.2973, 491.1871)
float hash31(vec3 p3)
{
	p3  = fract(p3 * MOD3);
    p3 += dot(p3, p3.yzx + 19.19);
    return -1.0 + 2.0 * fract((p3.x + p3.y) * p3.z);
}

vec3 hash33(vec3 p3)
{
	p3 = fract(p3 * MOD3);
    p3 += dot(p3, p3.yxz+19.19);
    return -1.0 + 2.0 * fract(vec3((p3.x + p3.y)*p3.z, (p3.x+p3.z)*p3.y, (p3.y+p3.z)*p3.x));
}

float simplex_noise(vec3 p)
{
    const float K1 = 0.333333333;
    const float K2 = 0.166666667;
    
    vec3 i = floor(p + (p.x + p.y + p.z) * K1);
    vec3 d0 = p - (i - (i.x + i.y + i.z) * K2);
    
    // thx nikita: https://www.shadertoy.com/view/XsX3zB
    vec3 e = step(vec3(0.0), d0 - d0.yzx);
	vec3 i1 = e * (1.0 - e.zxy);
	vec3 i2 = 1.0 - e.zxy * (1.0 - e);
    
    vec3 d1 = d0 - (i1 - 1.0 * K2);
    vec3 d2 = d0 - (i2 - 2.0 * K2);
    vec3 d3 = d0 - (1.0 - 3.0 * K2);
    
    vec4 h = max(0.6 - vec4(dot(d0, d0), dot(d1, d1), dot(d2, d2), dot(d3, d3)), 0.0);
    vec4 n = h * h * h * h * vec4(dot(d0, hash33(i)), dot(d1, hash33(i + i1)), dot(d2, hash33(i + i2)), dot(d3, hash33(i + 1.0)));
    
    return dot(vec4(31.316), n);
}

void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.

    float windowWidth = 1024.0;
    float windowHeight = 768.0;
    vec2 iResolution = vec2(1024.0,768.0);

        // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy/iResolution.xy;

    // Time varying pixel color
    //vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    
    vec3 col = vec3(0.0);
    float amp = 0.5;
    //uv += 0.1*iTime;
    /*
    float treb = texture(iChannel0, vec2(0.4,0.0)).x;
    treb += texture(iChannel0, vec2(0.45,0.0)).x;
    treb += texture(iChannel0, vec2(0.5,0.0)).x;
    treb += texture(iChannel0, vec2(0.55,0.0)).x;
    treb += texture(iChannel0, vec2(0.6,0.0)).x;
    treb += texture(iChannel0, vec2(0.65,0.0)).x;
    
    float bass = texture(iChannel0, vec2(0.01,0.0)).x;
    bass += texture(iChannel0, vec2(0.02,0.0)).x;
    bass += texture(iChannel0, vec2(0.4,0.0)).x;
	bass = pow(0.5*bass,15.0)*0.03+0.9;
    
    treb *= 0.01;
    */

    uv = 0.0005*scale*uv + 0.1;
    for (int i=0; i<6; i++) {
        float k = 1.0;//0.6*texelFetch(iChannel0, ivec2(int(float(i)*0.2+0.1),0),0).x;
        col += amp*abs(simplex_noise(vec3(uv+0.05*float(i*i)*iTime,2.0))+0.1*sin(iTime));
        amp *= 0.5+0.1*sin(0.2*iTime);
        uv  *= 2.0;
    }
    
    col = 0.5*sin(col*(25.0+130.*sin(0.07*iTime)))+0.5;

    // Output to screen
    outputColor = vec4(col,1.0);
    
    /*
    if (fragCoord.y < 20.0) {
    	fragColor = vec4(texelFetch(iChannel0, ivec2(int(fragCoord.x),0),0));   
    }
    
    float r = sin(gl_FragCoord.x * scale / windowWidth);
    float g = gl_FragCoord.y / windowHeight;
    float b = 1.0;
    float a = 1.0;
    outputColor = vec4(r, g, b, a);
    */
}
