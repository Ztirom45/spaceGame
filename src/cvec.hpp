#include <stdio.h>
#include <math.h>

#define pi 3.14159265358979323846

//define vecs
typedef struct _vec4i{
	int w;
	int x;
	int y;
	int z;
}vec4i;

typedef struct _vec4f{
	float w;
	float x;
	float y;
	float z;
}vec4f;

typedef struct _vec3i{
	int x;
	int y;
	int z;
}vec3i;

typedef struct _vec3f{
	float x;
	float y;
	float z;
}vec3f;

typedef struct _vec2i{
	int x;
	int y;
	int z;
}vec2i;

typedef struct _vec2f{
	float x;
	float y;
	float z;
}vec2f;

//3drotate functions
vec3f rotateX(vec3f pos,float angle){
        //determines radians
        float rad = angle * pi / 180;
        
        //cos,sin of radians
        float cosa = cos(rad);
        float sina = sin(rad);
        
        //determine new y,z value
        float y = pos.y * cosa - pos.z * sina;
        float z = pos.y * sina + pos.z * cosa;
        
        //write y,z to pos 
        pos.y = y;
        pos.z = z;
        return pos;
}

vec3f rotateY(vec3f pos,float angle){
        //detemines radians
        float rad = angle * pi / 180;
        
        //cos, sin of radians
        float cosa = cos(rad);
        float sina = sin(rad);
        
        //calculate new x,z value
        float z = pos.z * cosa - pos.x * sina;
        float x = pos.z * sina + pos.x * cosa;
        
        //write x,z to pos
        pos.x = x;
        pos.z = z;
        return pos;
}

vec3f rotateZ(vec3f pos, float angle){
        
        //determines radians
        float rad = angle * pi / 180;
        
        //cos,sin of radians
        float cosa = cos(rad);
        float sina = sin(rad);
        
        //calculate new x,y value
        float x = pos.x * cosa - pos.y * sina;
        float y = pos.x * sina + pos.y * cosa;
        
        //write x,y to pos
        pos.x = x;
        pos.y = y;
        return pos;
}

vec3f rotate(vec3f pos, vec3f angle){
	pos = rotateX(pos,angle.x);
	pos = rotateY(pos,angle.y);
	pos = rotateZ(pos,angle.z);
	return pos;
}

vec3f RotateInPlayerPerspective(vec3f pos, vec3f angle){//no z fix
	return rotate(pos,{90+angle.x,-angle.y+180,0});
}

vec3f RotatePlayerDistance(float distance, vec3f angle){
	return RotateInPlayerPerspective({0,distance,0},angle);
}
