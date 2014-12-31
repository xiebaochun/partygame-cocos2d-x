#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform int u_color_red;
uniform int u_color_blue;

void main()
{
	vec4 color = texture2D(u_texture, v_texCoord);
    gl_FragColor = vec4(u_color_red, 0, u_color_blue, color.a);

}