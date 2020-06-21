uniform sampler2D texture;
uniform vec2 resolution;
uniform float time;
uniform float random;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec2 pos = gl_FragCoord.xy / resolution.xy;
    vec2 centre = pos - vec2(0.5);

    float len = length(centre);
    float rad = 1.1*time;
    vec4 vignette = vec4(vec3(smoothstep(rad, rad-.45, len)), 1.0);

    pixel = vignette;

    pixel.r *= abs(sin(pos.x * time/time + random));
    pixel.g *= abs(tan(pos.y / time*time - random));
    pixel.b *= 1-time*random;
    pixel.a *= vignette.a;

    gl_FragColor =  pixel;
}
