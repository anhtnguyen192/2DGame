attribute vec4 a_posL;
varying vec2 v_uv;
//uniform mat4 u_mvp;

void main()
{
gl_Position =vec4(a_posL.xy,0.0,1.0);
v_uv=a_posL.zw;
}
//u_mvp*
//hihi