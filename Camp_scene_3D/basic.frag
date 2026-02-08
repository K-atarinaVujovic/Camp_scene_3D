#version 330 core
out vec4 FragColor;

in vec3 chNormal;  
in vec3 chFragPos;  
in vec2 chUV;
  
uniform vec3 uLightPos; 
uniform vec3 uViewPos; 
uniform vec3 uLightColor;

uniform sampler2D uDiffMap1;


struct Light {
    //vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;



void main()
{    
    // ambient
//    float ambientStrength = 0.8;
    vec3 ambient = light.ambient * uLightColor;
  	
    // diffuse 
    vec3 norm = normalize(chNormal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * uLightColor;
    
    // specular
    /*
    float specularStrength = 0.5;
    vec3 viewDir = normalize(uViewPos - chFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * uLightColor;*/  

    FragColor = texture(uDiffMap1, chUV) * vec4(ambient + diffuse, 1.0);
}

