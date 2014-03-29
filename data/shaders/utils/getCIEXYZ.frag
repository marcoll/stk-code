// Using numerical value from here
// http://content.gpwiki.org/index.php/D3DBook:High-Dynamic_Range_Rendering

vec3 getCIEYxy(vec3 rgbColor)
{
    mat3 RGB2XYZ = mat3(
        vec3(0.5141364, 0.3238786,  0.16036376),
        vec3(0.265068,  0.67023428, 0.06409157),
        vec3(0.0241188, 0.1228178,  0.84442666));

    vec3 XYZ = RGB2XYZ * rgbColor;
    float sum = dot(vec3(1.), XYZ);
    return vec3(XYZ.y, XYZ.xy / sum);
}