varying highp vec4 outColor;

void main(void)
{
    gl_FragColor = outColor;
    gl_FragColor.rgb*=(1.0f-gl_FragCoord.z);
}

