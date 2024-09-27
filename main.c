#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}

int main(int argc , char *argv[] ) { 
  glutInit(&argc, argv);
  if ( argc != 2 ){
    printf("comando invalido se necesita el nombre del archivo");
    return 1; 
  }
  char filename[256];
  
  int i = 0;
  
  while(argv[1][i]!='\0' && i < sizeof(filename)-1){
    filename[i]=argv[1][i];
    i++;
  }
  filename[i]='\0';

  image = readBMP(filename);
  if (!image) return 1;
 
  // Establecer el modo de visualización
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(image->width, image->height);
  glutCreateWindow("Visualizador de BMP");

  glLoadIdentity();
  glOrtho(0, image->width, image->height, 0, -1, 1);

  glutDisplayFunc(display);
  glutMainLoop();

  freeBMP(image);
  return 0;
}
