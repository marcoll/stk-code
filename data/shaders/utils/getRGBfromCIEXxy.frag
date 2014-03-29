// Using numerical value from here
// http://content.gpwiki.org/index.php/D3DBook:High-Dynamic_Range_Rendering

vec3 getRGBFromCIEXxy(vec3 YxyColor)
{
    float Yovery = YxyColor.x / YxyColor.z;
    vec3 XYZ = vec3(YxyColor.y * Yovery, YxyColor.x, (1. - YxyColor.y - YxyColor.z) * Yovery);

    mat3 XYZ2sRGB = mat3(
        vec3(2.5651,-1.1665,-0.3986),
        vec3(-1.0217, 1.9777, 0.0439),
        vec3(0.0753, -0.2543, 1.1892));

    return max(XYZ2sRGB * XYZ, vec3(0.));
}

