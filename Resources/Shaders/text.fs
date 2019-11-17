precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texture;
uniform vec4 textColor;
void main()
{
    //vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(u_texture, v_uv).a);
	//gl_FragColor = vec4(textColor, 1.0) * sampled;
	gl_FragColor = vec4(textColor.r, textColor.g, textColor.b,texture2D(u_texture, v_uv).a * textColor.a);
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//gl_FragColor = texture2D(u_texture, v_uv);
}