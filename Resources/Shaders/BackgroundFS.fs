precision mediump float;
uniform sampler2D u_texture0;
varying vec2 v_uv;
uniform float u_Time;

void main()
{
	vec2 myUV = vec2(v_uv.x,v_uv.y*0.5+u_Time*0.5);
	gl_FragColor = texture2D(u_texture0,myUV);
//gl_FragColor = vec4(1.0,1.0,0.0,1.0);
	
}
