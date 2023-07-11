#include<GL/glut.h>
#include <stdlib.h>
#include<stdio.h>

GLfloat v[4][3]={
                    {0.0,0.0,-1.0},
                    {-1.0,-1.0,1.0},
                    {1.0,-1.0,1.0},
                    {0.0,1.0,-1.0}
                };
int n;


void triangle(GLfloat *a,GLfloat *b,GLfloat *c)
{
glColor3f(1.0,0.0,0.0);
glVertex3fv(a);
glColor3f(0.0,1.0,0.0);
glVertex3fv(b);
glColor3f(0.0,0.0,1.0);
glVertex3fv(c);
}


void tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
glColor3f(1.0,0.0,0.0);
triangle(a,b,c);
glColor3f(0.0,0.5,0.0);
triangle(a,d,c);
glColor3f(0.8,1.0,0.0);
triangle(b,d,c);
glColor3f(1.0,0.0,0.0);
triangle(a,b,d);
}


void divide_tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,int m)
{
GLfloat ab[3],bc[3],cd[3],ad[3],bd[3],ac[3];
int j;
if(m>0){
    for(j=0;j<3;j++)
    {
        ab[j]=(a[j]+b[j])/2;
        bc[j]=(b[j]+c[j])/2;
        cd[j]=(c[j]+d[j])/2;
        ad[j]=(a[j]+d[j])/2;
        bd[j]=(b[j]+d[j])/2;
        ac[j]=(a[j]+c[j])/2;
    }
    divide_tetra(a,ab,ac,ad,m-1);
    divide_tetra(b,bc,bd,ab,m-1);
    divide_tetra(c,ac,bc,cd,m-1);
    divide_tetra(d,bd,ad,cd,m-1);

}
else {
    tetra(a,b,c,d);
}
}


void display()
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glBegin(GL_TRIANGLES);
divide_tetra(v[0],v[1],v[2],v[3],n);
glEnd();
glFlush();

}


void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glOrtho(-3.0,3.0,-3.0,3.0,-2.0,2.0);

}

int main(int argc, char**argv){
glutInit(&argc, argv);
printf("enter the number of subdivisions");
scanf("%d",&n);
glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
glutCreateWindow("3D Gasket");
glutInitWindowSize(500.0, 500.0);
glutDisplayFunc(display);
myinit();
glEnable(GL_DEPTH_TEST);
glutMainLoop();
return 0;
}

