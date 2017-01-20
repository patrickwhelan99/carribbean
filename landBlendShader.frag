uniform sampler2D diffuseTexture;
uniform sampler2D alphaTexture;


void main()
{
    vec4 diffuse = texture2D(diffuseTexture, gl_TexCoord[0].xy);
    vec4 alpha = texture2D(alphaTexture, gl_TexCoord[0].xy);
    vec4 final;
    final.rgb = diffuse.rgb;
    final.a = alpha.a;
    gl_FragColor =  final;
}
