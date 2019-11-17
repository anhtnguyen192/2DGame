precision mediump float;
uniform sampler2D u_texture1;
varying vec2 v_uv;


void main()
{

	gl_FragColor = texture2D(u_texture1,v_uv);
//gl_FragColor = vec4(0.0,1.0,0.0,1.0);
}
