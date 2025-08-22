#version 460

#define RECIPROCAL_PI 0.3183098861837907
#define RECIPROCAL_2PI 0.15915494309189535


vec3 modifiedPhongBRDF( vec3 lightDir,
						vec3 viewDir,
						vec3 normal,
						vec3 phongDiffuseColor,
						vec3 phongSpecularColor,
						float phongShininess)
{
	vec3 color = phongDiffuseColor * RECIPROCAL_PI;
	vec3 reflectDir = reflect(-lightDir, normal);
	float specDot = max(dot(reflectDir, viewDir), 0.001);
	float normalization = (phongShininess + 2.0) * RECIPROCAL_2PI;
	color += pow(specDot, phongShininess) * normalization * phongSpecularColor;
	return color;
}
float roughnessToShininess( const in float roughness ) {
	return pow(1000.0, 1.0-roughness);
}
// from http://www.thetenthplanet.de/archives/1180
mat3 cotangentFrame(in vec3 N, in vec3 p, in vec2 uv){//yeah i have no fucking clue what this does
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
 
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    // construct a scale-invariant frame 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}
vec3 applyNormalMap(in vec3 n, in vec3 v, in vec2 texcoord, sampler2D normalTexture){ //normalTexture is a uniform
	vec3 highResNormal = texture(normalTexture, texcoord).xyz;
	highResNormal = normalize(highResNormal * 2.0 - 1);
	mat3 TBN = cotangentFrame(n, -v, texcoord);
	return normalize(TBN * highResNormal);
}

vec3 rgb2lin(vec3 rgb) { // sRGB to linear approximation
  return pow(rgb, vec3(2.2));
}

vec3 lin2rgb(vec3 lin) { // linear to sRGB approximation
  return pow(lin, vec3(1.0 / 2.2));
}
vec3 fresnelShlick(float cosTheta, vec3 F0){
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
float D_GGX(float NoH, float roughness) {
  float alpha = roughness * roughness;
  float alpha2 = alpha * alpha;
  float NoH2 = NoH * NoH;
  float b = (NoH2 * (alpha2 - 1.0) + 1.0);
  return alpha2 * RECIPROCAL_PI / (b * b);
}
float G1_GGX_Schlick(float NoV, float roughness) {
  float alpha = roughness * roughness;
  float k = alpha / 2.0;
  return max(NoV, 0.001) / (NoV * (1.0 - k) + k);
}
float G_Smith(float NoV, float NoL, float roughness) {
  return G1_GGX_Schlick(NoL, roughness) * G1_GGX_Schlick(NoV, roughness);
}

float fresnelSchlick90(float cosTheta, float F0, float F90) {
  return F0 + (F90 - F0) * pow(1.0 - cosTheta, 5.0);
} 

float disneyDiffuseFactor(float NoV, float NoL, float VoH, float roughness) {
  float alpha = roughness * roughness;
  float F90 = 0.5 + 2.0 * alpha * VoH * VoH;
  float F_in = fresnelSchlick90(NoL, 1.0, F90);
  float F_out = fresnelSchlick90(NoV, 1.0, F90);
  return F_in * F_out;
}

vec3 microfacetBRDF(in vec3 l,
					in vec3 v,
					in vec3 n,
					in float metallic,
					in float roughness,
					in vec3 baseColor,
					in float reflectance)
{
	vec3 h = normalize(v + l);

	float nov = clamp(dot(n, v), 0.0, 1.0);
	float nol = clamp(dot(n, l), 0.0, 1.0);
	float noh = clamp(dot(n, h), 0.0, 1.0);
	float voh = clamp(dot(v, h), 0.0, 1.0);

	vec3 f0 = vec3(0.16 * (reflectance * reflectance));
	f0 = mix(f0, baseColor, metallic);

	//can chage these guys ill add options later
	vec3 f = fresnelShlick(voh, f0);
	float d = D_GGX(noh, roughness);
	float g = G_Smith(nov, nol, roughness);

	vec3 specular  = (f * d * g) / (4.0 * max(nov, 0.001) * max(nol, 0.001));
	vec3 rhoD = baseColor; //albedo

	rhoD *= vec3(1.0) - f;
	//	OR
	//rhoD *= disneyDiffuseFactor(nov, nol, voh, roughness);

	rhoD *= (1.0 - metallic);
	vec3 diffuse = rhoD * RECIPROCAL_PI;
	return specular + diffuse;
}

