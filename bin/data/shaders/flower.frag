#version 150

#define CONE_SIDES 10

out vec4 outputColor;
uniform float scale;
uniform float iTime;
uniform vec2 coneACenter;
uniform vec4 coneAVerts[CONE_SIDES];
uniform vec2 coneBCenter;
uniform vec4 coneBVerts[CONE_SIDES];
  
void main()
{

    vec2 iResolution = vec2(1024.0,768.0);

   // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy/iResolution.xy;
    uv -= 0.5;
    uv.x *= iResolution.x/iResolution.y;

    vec3 col;

    // compute distance from center
    float dist = distance(uv, vec2(0.0));
    // pixel angle
    float angle = atan(uv.x/uv.y);
    //float segments = 4.0;
    //angle = floor(segments*angle)/segments;
    
    // Cause occasional twisting
    dist += max(6.0*sin(0.29*iTime)-5.0,0.0)*angle;
    
    // Wiggle with distance
    dist += (0.2*pow(sin(0.09*iTime),15.0))*sin((12.0)*angle);
    
    // scale up distance value, and oscilate slowly over time
    float d = dist*80.0+170.0*sin(iTime*0.18);//160.0;
    //d = floor(d*0.2);
    float rd = d;//+1.0*sin(2.0*d);
    float gd = d+10.1*sin(0.2*d);
    float bd = d+12.0*cos(0.12*d);
    float red   = 0.23*rd + 10.0*(0.28*sin(0.11*iTime)+0.511)*cos(0.19*iTime);
    float green = 0.21*gd + 65.0*(0.21*sin(0.13*iTime)+0.420)*sin(0.12*iTime);
    float blue  = 0.27*bd + 91.0*(0.24*sin(0.14*iTime)+0.617)*cos(0.09*iTime);
   
    col = vec3( 0.5*sin(red)+0.5, 0.5*cos(green)+0.5, 0.5*sin(blue)+0.5 );
    
    // Fade out with many radial sections
    //angle = 1.0*mod(angle,2.0+0.5*sin(0.1*iTime));
    float s = 1.0;
    // radial wipe
    s *= min(pow(angle - 3.0*sin(1.0*iTime), 8.0),1.0);
    // circular wipe
    s *= min(pow(dist-2.0*sin(iTime), 8.0),1.5);
    col *= s;
    
    
    //col = vec3( sin(40.0*uv.x*uv.y + iTime*uv.y) );
    
    outputColor = vec4(col,1.0);

}
