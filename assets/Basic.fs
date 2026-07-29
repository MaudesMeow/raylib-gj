#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec2 resolution;

out vec4 finalColor;

void main()
{
    vec3 color = texture(texture0, fragTexCoord).rgb;

    float scanlines = 0.9 + 0.1 *
        sin(fragTexCoord.y * resolution.y * 3.14159);

    color *= scanlines;

    finalColor = vec4(color, 1.0);
}
