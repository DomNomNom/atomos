#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>  // min

#include "atomos.hpp"
#include "volumes/environment.hpp"
#include "pipe.hpp"
#include "time.hpp"

GLuint window;
int window_wd = 300;
int window_ht = 300;
uint frameCount = 0;

const int simulation_wd = 100;
const int simulation_ht = 100;
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
    float scale = std::min(
        (float)window_wd / simulation_wd,
        (float)window_ht / simulation_ht
    );
    glPixelZoom(scale, scale);
}

// prints something identifyable and the time in miliseconds since the last call of this function
void doTiming(const char *description) {
    printf("[ %s: %5.1fms ]        ", description, time_dt()*1000.0);
}

void cleanUp() {

    printf("starting clean up\n");

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
    printf("finished clean up\n");
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

std::vector<Molecule_ptr> &getMolecules(unsigned x, unsigned y) {
    return volumes.at(y * simulation_wd + x)->molecules;
}

void printVolume(unsigned x, unsigned y) {
    for (const Molecule_ptr &mol : getMolecules(x,y)) {
        printf((mol)? "1" : "0");
    }
    printf("\n");
}

// the body of the main loop
void tick() {
    doTiming("outside of tick()");

    frameCount += 1;
    // printf("frame %d\n", frameCount);

    // for (int i=0; i<5; ++i) {
        Atomos::getInstance().tick();  // where the magic happens
    // }

    doTiming("repeated atomos::tick()");


    // interpret the volumes as a pixel grid
    for (int y=0; y<simulation_ht; ++y){
        for (int x=0; x<simulation_wd; ++x) {
            int index = y * simulation_wd + x;
            std::vector<Molecule_ptr> &mols = getMolecules(x, y);
            unsigned molCount = 0;
            for (const Molecule_ptr &mol : mols) {
                if (mol) {
                    molCount += 1;
                }
            }

            // red if completely full
            // black if completely empty
            pixelData[4 * index] = (molCount * 255) / mols.size();
        }
    }

    doTiming("pixelData filling");


    // do a debug print of the one volume
    // printVolume(simulation_wd*0.5, simulation_ht*0.5);


    // draw the pixel data
    // we are using old openGL but this is quick, simple and dirty
    glClearColor(0.1, 0.1, 0.1, 1.0);  // have a dark grey background
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(simulation_wd, simulation_ht, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
    glutSwapBuffers();
    glutPostRedisplay();  // active rendering

    doTiming("draw");
    printf("\n");
}

int main(int argc, char** argv) {
    printf("hello world\n");

    time_init();

    // create the atmos grid
    for (int y=0; y<simulation_ht; ++y) {
        for (int x=0; x<simulation_wd; ++x) {
            Environment *newEnv = new Environment(11);
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

    doTiming("graph creation");

    // fill a region of the grid to its capacity
    for (unsigned y=simulation_ht*0.25; y<=simulation_ht*0.5; ++y) {
        for (unsigned x=simulation_wd*0.25; x<=simulation_wd*0.5; ++x) {
            std::vector<Molecule_ptr> &mols = getMolecules(x, y);

            for (unsigned i=0; i < mols.size(); ++i) {
                mols.at(i).reset(new Molecule(1337));
            }
        }
    }

    doTiming("molecule creation");

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

    doTiming("window setup");
    printf("\n");

    glutMainLoop();

    return 0;

}


