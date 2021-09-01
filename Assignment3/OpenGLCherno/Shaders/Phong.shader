#shader vertex
#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

// Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;
out vec4 GourandResult;

//out vec3 Dirambient;
//out vec3 Dirdiffuse;
//out vec3 Dirspecular;
//out vec3 Spotambient;
//out vec3 Spotdiffuse;
//out vec3 Spotspecular;
//
//out float attenuation;
//out float intensity;


uniform vec3 viewPosVert;
uniform DirLight dirLightVert;
uniform SpotLight spotLightVert;
uniform Material materialVert;
uniform int SpotLightOnVert;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int VertCalc;

void main()
{
	FragPos = vec3(model * position);
	Normal = mat3(transpose(inverse(model))) * normal;
	TexCoords = texCoords;

	if (VertCalc == 1)
	{
		//// Properties
		vec3 norm = normalize(Normal);
		vec3 viewDir = normalize(viewPosVert - FragPos);


		//No Tex Calc Gourand
		/*
		////Directional Light
		//vec3 lightDir = normalize(-dirLightVert.direction);

		//// Diffuse shading
		//float diff = max(dot(norm, lightDir), 0.0);

		//// Specular shading
		//vec3 reflectDir = reflect(-lightDir, norm);
		//float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialVert.shininess);

		//// Combine results
		//Dirambient = dirLightVert.ambient;// *vec3(texture(materialVert.diffuse, TexCoords));
		//Dirdiffuse = dirLightVert.diffuse * diff;// *vec3(texture(materialVert.diffuse, TexCoords));
		//Dirspecular = dirLightVert.specular * spec;// *vec3(texture(materialVert.specular, TexCoords));

	 //  //SpotLight

		//lightDir = vec3(0.0f);
		//lightDir = normalize(spotLightVert.position - FragPos);

		//// Diffuse shading
		//diff = 0.0f;
		//diff = max(dot(Normal, lightDir), 0.0);

		//// Specular shading
		//reflectDir = vec3(0.0f);
		//reflectDir = reflect(-lightDir, Normal);
		//spec = 0.0f;
		//spec = pow(max(dot(viewDir, reflectDir), 0.0), materialVert.shininess);

		//// Attenuation
		//float distance = length(spotLightVert.position - FragPos);
		//float attenuation = 1.0f / (spotLightVert.constant + spotLightVert.linear * distance + spotLightVert.quadratic * (distance * distance));

		//// Spotlight intensity
		//float theta = dot(lightDir, normalize(-spotLightVert.direction));
		//float epsilon = spotLightVert.cutOff - spotLightVert.outerCutOff;
		//float intensity = clamp((theta - spotLightVert.outerCutOff) / epsilon, 0.0, 1.0);

		//// Combine results
		//Spotambient = spotLightVert.ambient;// *vec3(texture(materialVert.diffuse, TexCoords));
		//Spotdiffuse = spotLightVert.diffuse * diff;// *vec3(texture(materialVert.diffuse, TexCoords));
		//Spotspecular = spotLightVert.specular * spec;// *vec3(texture(materialVert.specular, TexCoords));

	 //  Spotambient *= attenuation * intensity;
	 //  Spotdiffuse *= attenuation * intensity;
	 //  Spotspecular *= attenuation * intensity;

		//GourandResult = vec4(1.0f);
		*/

		// Directional lighting
		vec3 result = CalcDirLight(dirLightVert, Normal, viewDir);

		// Spot light
		if (SpotLightOnVert == 0)
			result += CalcSpotLight(spotLightVert, Normal, FragPos, viewDir);

		GourandResult = vec4(result, 1.0f);
	}
	else
	{
		GourandResult = vec4(0.0f);
	}

	gl_Position = projection * view * model * position;
}
//Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialVert.shininess);

	// Combine results
	vec3 ambient = light.ambient * vec3(texture(materialVert.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(materialVert.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(materialVert.specular, TexCoords));

	return (ambient + diffuse + specular);
}

// Calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialVert.shininess);

	// Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// Spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// Combine results
	vec3 ambient = light.ambient * vec3(texture(materialVert.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(materialVert.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(materialVert.specular, TexCoords));

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}


#shader fragment
#version 330 core

#define NUMBER_OF_POINT_LIGHTS 4

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 GourandResult;

//in vec3 Dirambient;
//in vec3 Dirdiffuse;
//in vec3 Dirspecular;
//in vec3 Spotambient;
//in vec3 Spotdiffuse;
//in vec3 Spotspecular;
//
//in float attenuation;
//in float intensity;


uniform vec3 viewPos;
uniform DirLight dirLight;
uniform SpotLight spotLight;
uniform Material material;
uniform int SpotLightOn;


layout(location = 0) out vec4 color;

// Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	if (GourandResult.w == 0.0f)
	{
		//// Properties
		vec3 norm = normalize(Normal);
		vec3 viewDir = normalize(viewPos - FragPos);

		// Directional lighting
		vec3 result = CalcDirLight(dirLight, norm, viewDir);

		// Spot light
		if (SpotLightOn == 0)
			result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

		color = vec4(result, 1.0);
	}
	else
	{
		//In Frag Tex Goraund
		/*
		vec3 FragDirambient = Dirambient  *vec3(texture(material.diffuse, TexCoords));
		vec3 FragDirdiffuse = Dirdiffuse  *vec3(texture(material.diffuse, TexCoords));
		vec3 FragDirspecular = Dirspecular* vec3(texture(material.specular, TexCoords));

		vec3 result = FragDirambient + FragDirdiffuse + FragDirspecular;

		vec3 FragSpotambient = Spotambient * vec3(texture(material.diffuse, TexCoords));
		vec3 FragSpotdiffuse = Spotdiffuse * vec3(texture(material.diffuse, TexCoords));
		vec3 FragSpotspecular = Spotspecular*  vec3(texture(material.specular, TexCoords));


		FragSpotambient *= attenuation * intensity;
		FragSpotdiffuse *= attenuation * intensity;
		FragSpotspecular *= attenuation * intensity;

		result += FragSpotambient + FragSpotdiffuse + FragSpotspecular;

		color = vec4(result, 1.0f);
		*/

		color = GourandResult;
	}
}

//Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	return (ambient + diffuse + specular);
}

// Calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// Spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// Combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}
