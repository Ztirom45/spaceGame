#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

//macros:
#define GET_DISTANCE(x1,y1,x2,y2) pow(pow((x2 - x1),2) + pow((y2 - y1),2),0.5)
#define IN_CIRCLE(x1,y1,rad1,x2,y2) (GET_DISTANCE(x1,y1,x2,y2) < rad1)
#define TOUCH_CIRCLE(x1,y1,rad1,x2,y2,rad2) (GET_DISTANCE(x1,y1,x2,y2) < rad1+rad2)


#define RECT1(x,y) (x1<x && w1>x  &&  y1<y && h1>y) 
#define RECT2(x,y) (x2<x && w2>x  &&  y2<y && h2>y)

// w & h = cords != x+w,y+h
#define INRECT(x,y,rx,ry,rw,rh)(rx<x && rw>x  &&  ry<y && rh>y)
#define TOUCH_RECT(x1,y1,w1,h1,  x2,y2,w2,h2)(INRECT(x2,y2,x1,y1,w1,h1)||INRECT(w2,y2,x1,y1,w1,h1)||INRECT(w2,h2,x1,y1,w1,h1)||INRECT(x2,h2,x1,y1,w1,h1)||INRECT(x1,y1,x2,y2,w2,h2)||INRECT(w1,y1,x2,y2,w2,h2)||INRECT(w1,h1,x2,y2,w2,h2)||INRECT(x1,h1,x2,y2,w2,h2))





//function:
//petformance & test (please delet main() function to use this liberry correct)
/*
float get_distance(float x1,float y1, float x2,float y2)								{return GET_DISTANCE(x1,y1,x2,y2);}
bool in_circle(float x1,float y1,float rad1,float x2,float y2)							{return IN_CIRCLE(x1,y1,rad1,x2,y2);}
bool touch_circle(float x1,float y1,float rad1,float x2,float y2,float rad2)			{return TOUCH_CIRCLE(x1,y1,rad1,x2,y2,rad2);}
bool in_rect(float x,float y,float rx,float ry,float rw,float rh)						{return INRECT(x,y,rx,ry,rw,rh);}
bool touch_rect(float x1,float y1,float w1,float h1,float x2,float y2,float w2,float h2){return TOUCH_RECT(x1,y1,w1,h1,x2,y2,w2,h2);}
*/

int get_distance(int x1,int y1, int x2,int y2)								{return GET_DISTANCE(x1,y1,x2,y2);}
bool in_circle(int x1,int y1,int rad1,int x2,int y2)							{return IN_CIRCLE(x1,y1,rad1,x2,y2);}
bool touch_circle(int x1,int y1,int rad1,int x2,int y2,int rad2)			{return TOUCH_CIRCLE(x1,y1,rad1,x2,y2,rad2);}
bool in_rect(int x,int y,int rx,int ry,int rw,int rh)						{return INRECT(x,y,rx,ry,rw,rh);}
bool touch_rect(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2){return TOUCH_RECT(x1,y1,w1,h1,x2,y2,w2,h2);}

