static const char* shader_frag = STRINGIFY(

precision highp float;

varying vec4 v_color;

void main()
{  
	gl_FragColor = v_color;
}

);
