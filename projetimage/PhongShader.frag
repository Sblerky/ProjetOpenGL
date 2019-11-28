#version 450

in vec3 fragPosition;

out vec4 finalColor;

void main() {

// affichage en couleur uniforme  
    finalColor = vec4(.5,.5,.5,1.);
    
 // affichage de la position comme donnée de couleur peut être utilisé pour le debugage
  // finalColor = vec4(fragPosition,1.);


}
