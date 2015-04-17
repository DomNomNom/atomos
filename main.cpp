#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <GL/glut.h>
#include <vector>

#include "atomos.hpp"
#include "volumes/environment.hpp"
#include "pipe.hpp"

GLuint window;
int window_wd = 300;
int window_ht = 300;
uint frameCount = 0;

const int simulation_wd = 5;
const int simulation_ht = 5;
GLubyte pixelData[simulation_ht * simulation_wd * 4];

std::vector<Environment*> volumes;
std::vector<Pipe*> pipes;


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


void cleanUp() {

    printf("starting to clean up\n");

    glutDestroyWindow(window);

    // note: delete pipes before volumes
    for (Pipe* p : pipes) {
        delete p;
    }
    pipes.clear();
    for (Environment* e : volumes) {
        delete e;
    }
    volumes.clear();
    printf("cleaned up before exiting\n");
}


// Input
void keyHandler(unsigned char key, int, int) {
    switch (key) {
        case 27: // Escape -> exit
        case 'q':
            cleanUp();
            exit (0);
            break; // lol
    }
}


// the body of the main loop
void tick() {
    frameCount += 1;
    // printf("frame %d\n", frameCount);


    Atomos::getInstance().tick();  // where the magic happens


    // TODO: interpret the volumes as a pixel grid
    int y = simulation_ht / 2;
    for (int x=0; x<simulation_wd; ++x) {
        pixelData[4 * (y * simulation_wd + x)] = ((frameCount + x) % simulation_wd == 0) ? 0 : 255;
    }


    // draw the pixel data
    // we are using old openGL but this is quick, simple and dirty
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(simulation_wd, simulation_ht, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
    glutSwapBuffers();
    glutPostRedisplay();  // active rendering
}

int main(int argc, char** argv) {
    printf("hello world\n");

    // create the atmos grid
    for (int y=0; y<simulation_ht; ++y) {
        for (int x=0; x<simulation_wd; ++x) {
            Environment *newEnv = new Environment(255);
            volumes.push_back(newEnv);

            // add connections to existing volumes in a grid
            if (x > 0) { // horizontal
                pipes.push_back(new Pipe(
                    newEnv->getNewFitting(),
                    volumes.at(y*simulation_wd + x-1)->getNewFitting()
                ));
            }
            if (y > 0) {  // vertical
                pipes.push_back(new Pipe(
                    newEnv->getNewFitting(),
                    volumes.at((y-1)*simulation_wd + x)->getNewFitting()
                ));
            }

        }
    }

    // fill a cell with atoms
    // TODO


    // set up the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window_wd, window_ht);
    window = glutCreateWindow("atomos");
    glutDisplayFunc(tick);
    glutReshapeFunc(reshapeHandler);
    // glutIdleFunc(AnimateScene);
    glutKeyboardFunc(keyHandler);
    // glutMouseFunc(mouseHandler);

    //
    glutMainLoop();

    return 0;

}


