#include <stdio.h>
#include <math.h>
#include "glut.h"

GLuint texture[4];
GLuint bitTex;
//first image
GLubyte *pic;  
GLint width; 
GLint height;

//second image
GLubyte *pic1;
GLint width1;
GLint height1;

void init()
{
	FILE *f;
	int picSize;
	int rd;
	GLubyte header[54],colorTable[1024];
	
	glEnable(GL_TEXTURE_2D);

	glOrtho(-1.0, 1.0, -1.0 ,1.0,2.0,-2.0);
	//gluPerspective(20,1,0.5,8);
	//glTranslatef(0,0,-4);
	
	glClearColor(0,0,0,0);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
//	glDisable(GL_BLEND);
	f=fopen("lena.bmp","rb");
	
	/*************************/
	//image header reading
	fread(header,54,1,f);
	if(header[0]!='B' || header[1]!='M')
		exit(1);  //not a BMP file
	for(int i=0;i<54;i++)
		printf("%x  ",header[i]);
	
	
	picSize=(*(int*)(header+2)-54);
	width=*(int*)(header+18);
	height=*(int*)(header+22);
	printf("\n%d %d %d %d \n",picSize,width,height,width*height*3);
	
	/**********************************/
	
	pic=new GLubyte[picSize];
	rd=fread(pic,1,picSize,f); //read image
	fclose(f);
	/*
	for(int i = 0; i < height*width; i += 3)
    {
            unsigned char tmp = pic[i];
            pic[i] = pic[i+2];
            pic[i+2] = tmp;
    }
	*/
	printf("*****  %d *******\n",rd);
		
	// printf("texture\n");
	

	//************ image **************************
	//glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1, &texture[0]);  //generate place for new texture
	glBindTexture(GL_TEXTURE_2D, texture[0]); // initialize first texure 
	
	//texture properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	//build texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_BGR_EXT, GL_UNSIGNED_BYTE, pic);
	
	/*for (int i = 0; i < height * 3 ; i++) {
		for (int j = 0; j < width * 3; j+=3) {
			pic[0][i * width + j] = 0; 
		}
	}*/

}

void mydisplay(void){
	
	glClear(GL_COLOR_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, texture[0]); //using first texture
	glViewport(0,0,512,512); 
	
	
	//glColor3f(.2f, 0.5f , 0.3f);
	
	//glShadeModel(GL_FLAT);
	glBegin(GL_QUADS);
		glTexCoord2f(-1.0, 1); //adapt texture to shape
		glVertex2f(-1.0f, 1.0f);
		
		glTexCoord2f(0, 1);  //adapt texture to shape
		glVertex2f(0.0f, 1.0f);
		
		glTexCoord2f(0, 0);//adapt texture to shape
		glVertex2f(0.0f,0.0f);
		
		glTexCoord2f(-1, 0);//adapt texture to shape
		glVertex2f(-1.0f,0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glFlush(); 
}

int main(int  argc,  char** argv) 
{

   glutInit (& argc, argv) ;
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB) ;
   glutInitWindowSize ( 512,512);
   glutCreateWindow("Simple") ;
   init();
  // glutReshapeFunc(myReshape);
   glutDisplayFunc(mydisplay) ;
   //glutIdleFunc(mydisplay);
  // printf("pi = %f",3.14);
   //glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	 glutMainLoop () ; 
	
   delete(pic);
 
}  