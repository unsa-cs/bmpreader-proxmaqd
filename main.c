#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}

void convertirabn(BMPImage *image) {
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  if (argc < 2 || argc > 3) {
    printf("comando invalido\n");
    return 1;
  }

  char filename[256];
  int i = 0;

  while (argv[1][i] != '\0' && i < sizeof(filename) - 1) {
    filename[i] = argv[1][i];
    i++;
  }
  filename[i] = '\0';

  image = readBMP(filename);
  if (!image) return 1;

  if (argc == 3) {
    int is_bw = 1;
    char *bw_id = argv[2];

    char bw_text[] = "bw";
    for (i = 0; bw_text[i] != '\0' && bw_id[i] != '\0'; i++) {
      if (bw_text[i] != bw_id[i]) {
        is_bw = 0; 
        break;
      }
    }
    if (bw_text[i] != '\0' || bw_id[i] != '\0') {
      is_bw = 0;
    }

    if (is_bw) {
      convertirabn(image);
    }
  }

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

