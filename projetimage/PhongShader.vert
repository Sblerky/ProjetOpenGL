#version 450
#define M_PI 3.1415926535897932384626433832795

uniform mat4 MVP;
uniform int choice;

out float theta;
out float alpha;
out float quasirot;

out mat3 rot;
out vec3 tmp;

layout(location = 0) in vec3 position; // le location permet de dire de quel flux/canal on récupère les données (doit être en accord avec le location du code opengl)

out vec3 fragPosition;
out vec3 newPosition;


void compressionx(vec3 vecteur,float borneinf, float bornesup)
{
    float Rayon=bornesup-borneinf;
     if (vecteur.x>borneinf){
        if(vecteur.x<bornesup){
           newPosition.x=1.-(vecteur.x-borneinf)/(2.*Rayon);
         }
         else{
              newPosition.x= 1./2.*vecteur.x;
         }
         newPosition.y=vecteur.y;
        newPosition.z=vecteur.z;
     }
     else{
         newPosition=vecteur;
     }

}

void compressionx_yz(vec3 vecteur,float borneinf, float bornesup)
{
    float Rayon=bornesup-borneinf;
     if (vecteur.x>borneinf){
        if(vecteur.x<bornesup){
           newPosition.y=1.-(vecteur.y-borneinf)/(2.*Rayon);
            newPosition.z=1.-(vecteur.z-borneinf)/(2.*Rayon);
         }
         else{
              newPosition.y= 1./2.*vecteur.y;
              newPosition.z= 1./2.*vecteur.z;
         }
         newPosition.x=vecteur.x;
     }
     else{
         newPosition=vecteur;
     }

}


void compressiony(vec3 vecteur,float borneinf, float bornesup)
{
    float Rayon=bornesup-borneinf;
     if (vecteur.y>borneinf){
        if(vecteur.y<bornesup){
           newPosition.y=1.-(vecteur.y-borneinf)/(2.*Rayon);
         }
         else{
              newPosition.y= 1./2.*vecteur.y;
         }
        newPosition.x=vecteur.x;
        newPosition.z=vecteur.z;
        }
     else{
         newPosition=vecteur;
     }
}

void compressiony_xz(vec3 vecteur,float borneinf, float bornesup)
{
    float Rayon=bornesup-borneinf;
     if (vecteur.y>borneinf){
        if(vecteur.y<bornesup){
           newPosition.z=1.-(vecteur.z-borneinf)/(2.*Rayon);
           newPosition.x=1.-(vecteur.x-borneinf)/(2.*Rayon);
         }
         else{
              newPosition.z= 1./2.*vecteur.z;
              newPosition.x= 1./2.*vecteur.x;
         }
        newPosition.y=vecteur.y;
        }
     else{
         newPosition=vecteur;
     }
}


void compressionz(vec3 vecteur,float borneinf, float bornesup)
{
    float Rayon=bornesup-borneinf;
     if (vecteur.z>borneinf){
        if(vecteur.z<bornesup){
           newPosition.z=1.-(vecteur.z-borneinf)/(2.*Rayon);
         }
         else{
              newPosition.z= 1./2.*vecteur.z;
         }
        newPosition.x=vecteur.x;
        newPosition.y=vecteur.y;
     }
     else{
         newPosition=vecteur;
     }

}

void compressionz_xy(vec3 vecteur,float borneinf, float bornesup)
{
    float Rayon=bornesup-borneinf;
     if (vecteur.z>borneinf){
        if(vecteur.z<bornesup){
           newPosition.x=1.-(vecteur.x-borneinf)/(2.*Rayon);
           newPosition.y=1.-(vecteur.y-borneinf)/(2.*Rayon);
         }
         else{
              newPosition.x= 1./2.*vecteur.x;
              newPosition.y= 1./2.*vecteur.y;
         }
        newPosition.z=vecteur.z;
     }
     else{
         newPosition=vecteur;
     }

}

void compressionxtremx (vec3 vecteur,float Max)
{
    newPosition.x=1./Max*vecteur.x;
    newPosition.y=vecteur.y;
    newPosition.z=vecteur.z;
}

void compressionxtremy (vec3 vecteur,float Max)
{
    newPosition.y=1./Max*vecteur.y;
    newPosition.x=vecteur.x;
    newPosition.z=vecteur.z;
}

void compressionxtremz (vec3 vecteur,float Max)
{
    newPosition.z=1./Max*vecteur.z;
    newPosition.y=vecteur.y;
    newPosition.x=vecteur.x;
}

void compressionxtrem(vec3 vecteur, float Maxi)
{
    compressionxtremx(vecteur,Maxi);
    compressionxtremy(newPosition,Maxi);
    compressionxtremz(newPosition,Maxi);
}

void decompressionxtremx (vec3 vecteur,float Max)
{
    newPosition.x=Max*vecteur.x;
    newPosition.y=vecteur.y;
    newPosition.z=vecteur.z;
}

void decompressionxtremy (vec3 vecteur,float Max)
{
    newPosition.y=Max*vecteur.y;
    newPosition.x=vecteur.x;
    newPosition.z=vecteur.z;
}

void decompressionxtremz (vec3 vecteur,float Max)
{
    newPosition.z=Max*vecteur.z;
    newPosition.y=vecteur.y;
    newPosition.x=vecteur.x;
}

void decompressionxtrem(vec3 vecteur, float Maxi)
{
    decompressionxtremx(vecteur,Maxi);
    decompressionxtremy(newPosition,Maxi);
    decompressionxtremz(newPosition,Maxi);
}



void rotationdiffy2(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.y/8;
    rot=mat3(cos(theta),0.0,sin(theta),
                    0.0,1.0,0.0,
                    -sin(theta),0.0,cos(theta)
                    );
    newPosition= rot*vecteur;

}

vec3 rotationdiffy3(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.y/8;
    rot=mat3(cos(theta),0.0,sin(theta),
                    0.0,1.0,0.0,
                    -sin(theta),0.0,cos(theta)
                    );
    return rot*vecteur;

}

void rotationdiffy(vec3 vecteur, int borneinf,int bornesup,float anglerot){

    float Rayon=bornesup-borneinf;
    if (vecteur.y>borneinf){
        if(vecteur.y<bornesup){
            quasirot=((vecteur.y-borneinf)/Rayon)*anglerot;
            newPosition=rotationdiffy3(vecteur,quasirot);
        }
        else{
            newPosition=rotationdiffy3(vecteur,anglerot);
        }
    }
    else{newPosition=vecteur;}
}

void rotationdiffx2(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.x/8;
    rot=mat3(1.0,0.0,0.0,
              0.0,cos(theta),-sin (theta),
              0.0,sin(theta),cos(theta)
             );
    newPosition= rot*vecteur;

}

vec3 rotationdiffx3(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.x/8;
    rot=mat3(1.0,0.0,0.0,
              0.0,cos(theta),-sin (theta),
              0.0,sin(theta),cos(theta)
             );
    return rot*vecteur;

}

void rotationdiffx(vec3 vecteur, int borneinf,int bornesup,float anglerot){

    float Rayon=bornesup-borneinf;
    if (vecteur.x>borneinf){
        if(vecteur.x<bornesup){
            quasirot=((vecteur.x-borneinf)/Rayon)*anglerot;
            newPosition=rotationdiffx3(vecteur,quasirot);
        }
        else{
            newPosition=rotationdiffx3(vecteur,anglerot);
        }
    }
    else{newPosition=vecteur;}
}

void rotationdiffz2(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.z/8;
    rot=mat3(cos(theta),-sin(theta),0.0,
                    sin(theta),cos(theta),0.0,
                    0.0,0.0,1.0
                    );
    newPosition= rot*vecteur;

}

vec3 rotationdiffz3(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.z/8;
    rot=mat3(cos(theta),-sin(theta),0.0,
                    sin(theta),cos(theta),0.0,
                    0.0,0.0,1.0
                    );
    return rot*vecteur;

}

void rotationdiffz(vec3 vecteur, int borneinf,int bornesup,float anglerot){

    float Rayon=bornesup-borneinf;
    if (vecteur.z>borneinf){
        if(vecteur.z<bornesup){
            quasirot=((vecteur.z-borneinf)/Rayon)*anglerot;
            newPosition=rotationdiffz3(vecteur,quasirot);
        }
        else{
            newPosition=rotationdiffz3(vecteur,anglerot);
        }
    }
    else{newPosition=vecteur;}
}


void vortexz(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.z/8;
    alpha=theta*exp(-1.*(vecteur.x*vecteur.x+vecteur.y*vecteur.y));
    rot=mat3(cos(alpha),-sin(alpha),0.0,
                    sin(alpha),cos(alpha),0.0,
                    0.0,0.0,1.0
                    );
    newPosition= (rot*vecteur);

}

void vortexx(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.z/8;
    alpha=theta*exp(-1.*(vecteur.x*vecteur.x+vecteur.y*vecteur.y));
    rot=mat3(1.0,0.0,0.0,
              0.0,cos(alpha),-sin (alpha),
              0.0,sin(alpha),cos(alpha)
             );
    newPosition= (rot*vecteur);

}

void vortexy(vec3 vecteur,float anglerot)
{
    alpha=anglerot*vecteur.y/8;
    theta=alpha*exp(-1.*(vecteur.x*vecteur.x+vecteur.z*vecteur.z));
    rot=mat3(cos(theta),0.0,sin(theta),
                    0.0,1.0,0.0,
                    -sin(theta),0.0,cos(theta)
                    );
    newPosition= rot*vecteur;
}


void torvexz(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.z/8;
    alpha=theta*exp(-1./(vecteur.x*vecteur.x+vecteur.y*vecteur.y));
    rot=mat3(cos(alpha),-sin(alpha),0.0,
                    sin(alpha),cos(alpha),0.0,
                    0.0,0.0,1.0
                    );
    newPosition= (rot*vecteur);

}

void torvexx(vec3 vecteur,float anglerot)
{
    theta=anglerot*vecteur.z/8;
    alpha=theta*exp(-1./(vecteur.x*vecteur.x+vecteur.y*vecteur.y));
    rot=mat3(1.0,0.0,0.0,
              0.0,cos(alpha),-sin (alpha),
              0.0,sin(alpha),cos(alpha)
             );
    newPosition= (rot*vecteur);

}

void torvexy(vec3 vecteur,float anglerot)
{
    alpha=anglerot*vecteur.y/8;
    theta=alpha*exp(-1./(vecteur.x*vecteur.x+vecteur.z*vecteur.z));
    rot=mat3(cos(theta),0.0,sin(theta),
                    0.0,1.0,0.0,
                    -sin(theta),0.0,cos(theta)
                    );
    newPosition= rot*vecteur;
}

void pliagex(vec3 vecteur,int borneinf,int bornesup,float anglerot)
{

    float Rayon=(bornesup-borneinf);
    float trueRayon = (bornesup-borneinf)/anglerot;
    tmp=vec3(0,Rayon,Rayon);
    if (vecteur.z>borneinf){
        if(vecteur.z<bornesup){

            quasirot=vecteur.z-borneinf; // ( z - z0)

            alpha=( (quasirot*anglerot) /Rayon ); // theta * (z-z0)/(z1-z0)

            rot=mat3(1.0,0.0,0.0,
              0.0,cos(alpha),-sin (alpha),
              0.0,sin(alpha),cos(alpha)
             );

            newPosition=vecteur;

            //translation
            newPosition.z=newPosition.z-borneinf;
			newPosition.y=newPosition.y-borneinf-trueRayon;

            //rotation
			newPosition=rot*newPosition;

            newPosition.z = newPosition.z+borneinf;
			newPosition.y = newPosition.y+borneinf+trueRayon;
         }
        else{

            rot=mat3(1.0,0.0,0.0,
              0.0,cos(anglerot),-sin(anglerot),
              0.0,sin(anglerot),cos(anglerot)
             );

            newPosition=vecteur;

            //translation
            newPosition.z=newPosition.z-borneinf;
            newPosition.y=newPosition.y-borneinf-trueRayon;

            //rotation
			newPosition=rot*newPosition;

            newPosition.z = newPosition.z+borneinf;
			newPosition.y = newPosition.y+borneinf+trueRayon;
        }
    }
    else{
        newPosition=vecteur;
    }
}







// ***************************************************************** //



void pliagey(vec3 vecteur,int borneinf,int bornesup,float anglerot)
{

    float Rayon=(bornesup-borneinf);
    float trueRayon = (bornesup-borneinf)/anglerot;
    tmp=vec3(0,Rayon,Rayon);
    if (vecteur.x>borneinf){
        if(vecteur.x<bornesup){

            quasirot=vecteur.x-borneinf; // ( x - z0)

            alpha=( (quasirot*anglerot) /Rayon ); // theta * (z-z0)/(z1-z0)

            rot=mat3(cos(alpha),0.0,sin(alpha),
                    0.0,1.0,0.0,
                    -sin(alpha),0.0,cos(alpha)
                    );

            newPosition=vecteur;

            //translation
            newPosition.x=newPosition.x-borneinf;
			newPosition.z=newPosition.z-borneinf-trueRayon;

            //rotation
			newPosition=rot*newPosition;

            newPosition.x = newPosition.x+borneinf;
			newPosition.z = newPosition.z+borneinf+trueRayon;
         }
        else{

            rot=mat3(cos(anglerot),0.0,sin(anglerot),
                    0.0,1.0,0.0,
                    -sin(anglerot),0.0,cos(anglerot)
                    );

            newPosition=vecteur;

            //translation
            newPosition.x=newPosition.x-borneinf;
            newPosition.z=newPosition.z-borneinf-trueRayon;

            //rotation
			newPosition=rot*newPosition;

            newPosition.x = newPosition.x+borneinf;
			newPosition.z = newPosition.z+borneinf+trueRayon;
        }
    }
    else{
        newPosition=vecteur;
    }
}



// ***************************************************************** //



void pliagez(vec3 vecteur,int borneinf,int bornesup,float anglerot)
{

    float Rayon=(bornesup-borneinf);
    float trueRayon = (bornesup-borneinf)/anglerot;
    tmp=vec3(0,Rayon,Rayon);
    if (vecteur.x>borneinf){
        if(vecteur.x<bornesup){

            quasirot=vecteur.x-borneinf; // ( x - z0)

            alpha=( (quasirot*anglerot) /Rayon ); // theta * (z-z0)/(z1-z0)

            rot=mat3(cos(alpha),-sin(alpha),0.0,
                    sin(alpha),cos(alpha),0.0,
                    0.0,0.0,1.0
            );

            newPosition=vecteur;

            //translation
            newPosition.x=newPosition.x-borneinf;
			newPosition.y=newPosition.y-borneinf-trueRayon;

            //rotation
			newPosition=rot*newPosition;

            newPosition.x = newPosition.x+borneinf;
			newPosition.y = newPosition.y+borneinf+trueRayon;
         }
        else{

            rot=mat3(cos(anglerot),-sin(anglerot),0.0,
                    sin(anglerot),cos(anglerot),0.0,
                    0.0,0.0,1.0
            );

            newPosition=vecteur;

            //translation
            newPosition.x=newPosition.x-borneinf;
            newPosition.y=newPosition.y-borneinf-trueRayon;

            //rotation
			newPosition=rot*newPosition;

            newPosition.x = newPosition.x+borneinf;
			newPosition.y = newPosition.y+borneinf+trueRayon;
        }
    }
    else{
        newPosition=vecteur;
    }
}




void main(){
    //compressionx(position,0,5);
    //compressionx_yz(position,0,4);
    //compressiony_xz(position,0,4);
    //compressionz_xy(position,0,4);
    //compressiony(position,-3,4);
    //compressionz(newPosition,0,4);
    //rotationdiffy(position,-1,3,M_PI);
    //rotationdiffx(newPosition,-1,3,M_PI);
    //rotationdiffy2(position,M_PI/2);
    //rotationdiffz2(position,M_PI/2);
    //rotationdiffx2(position,M_PI/2);
    //compressionxtrem(position,4);
    //vortexy(newPosition,2*M_PI);
    //vortexz(newPosition,2*M_PI);
    //torvexy(newPosition,M_PI);
    //decompressionxtrem(newPosition,4);

    //pliagex(position,-1,2,M_PI/4);
    if(choice==0){pliagey(position,-1,2,M_PI/4);}
    //pliagey(position,-1,2,M_PI/4);
    if(choice>0){pliagez(position,-1,2,M_PI/4);}
    //pliagez(position,-1,2,M_PI/4);

    //rotationdiffx(position,0,4,M_PI/3);
    //compressionx(newPosition,-1,3);

	gl_Position = MVP*vec4(newPosition, 1.0);



	fragPosition = newPosition;


}
