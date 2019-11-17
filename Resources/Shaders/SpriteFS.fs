precision mediump float;
uniform sampler2D u_texture1;
varying vec2 v_uv;
uniform float u_isHit;

void main()
{

	vec4 _FragColor = texture2D(u_texture1,v_uv);
	if (u_isHit == 1.0) 
	{
	_FragColor.r *= 1.0;
	_FragColor.g *= 0.8;
	_FragColor.b *= 0.8;
	_FragColor.a *= 0.7;
	}
	//_FragColor.rgba *= 0.7;
	gl_FragColor = _FragColor;
//gl_FragColor = vec4(0.0,0.0,1.0,1.0);
}
