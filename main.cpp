#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <GL/glut.h>

#include "atomos.hpp"

GLuint window;
int window_wd = 300;
int window_ht = 300;
uint frameCount = 0;

const int simulation_wd = 100;
const int simulation_ht = 100;
GLubyte pixelData[simulation_ht * simulation_wd * 3];

// void mouseHandler(int, int state, int, int) {
//     if (state == GLUT_DOWN) {
//         printf("mousepressed\n");
//     }
//     // glutPostRedisplay();
// }

void reshapeHandler(int wd, int ht) {
    window_wd = wd;
    window_ht = ht;
    glPixelZoom(
        (float)window_wd / simulation_wd,
        (float)window_ht / simulation_ht
    );

}


// Input
void keyHandler(unsigned char key, int, int) {
    switch (key) {
        case 27: // Escape -> exit
        case 'q':
            glutDestroyWindow(window);
            exit (0);
            break;
    }
}


// the body of the main loop
void tick() {
    frameCount += 1;
    // printf("frame %d\n", frameCount);

    int y = simulation_ht / 2;
    for (int x=0; x<simulation_wd; ++x) {
        pixelData[3 * (y * simulation_wd + x)] = ((frameCount + x) % simulation_wd == 0) ? 0 : 255;
    }

    // we are using old openGL but this is quick, simple and dirty
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(simulation_wd, simulation_ht, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
    glutSwapBuffers();
    glutPostRedisplay();  // active rendering
}

int main(int argc, char** argv) {
    // time_init();

    // Atomos atomos;
    // Volume_ptr vol = atomos.createVolume(6);
    // printf("vol? %d\n", vol->capacity());
    // printf("isnull? %d\n", vol.);

    printf("hello world\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window_wd, window_ht);
    window = glutCreateWindow("atomos");

    glutDisplayFunc(tick);
    glutReshapeFunc(reshapeHandler);
    // glutIdleFunc(AnimateScene);
    glutKeyboardFunc(keyHandler);
    // glutMouseFunc(mouseHandler);


    glutMainLoop();

    return 0;

}


