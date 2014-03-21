#if __VERSION__ >= 130
in vec3 nor;
#ifdef _HAS_STENCIL_SUPPORT_
out vec2 EncodedNormal;
#else
out vec3 EncodedNormal;
#endif
#else
varying vec3 nor;
#define EncodedNormal gl_FragColor.xy
#endif



// from Crytek "a bit more deferred CryEngine"
vec2 EncodeNormal(vec3 n)
{
	return normalize(n.xy) * sqrt(n.z * 0.5 + 0.5);
}

void main(void)
{
    EncodedNormal.xy = 0.5 * EncodeNormal(normalize(nor)) + 0.5;
#ifndef _HAS_STENCIL_SUPPORT_
    EncodedNormal.z = gl_FragCoord.z;
#endif
}
