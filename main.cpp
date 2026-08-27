#include <GL/glut.h>

float carX = -500;
float gateAngle = 0;
int gateOpen = 0;

void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void drawCar() {
    glColor3f(0.9, 0.1, 0.1);
    drawRectangle(carX, -40, carX + 140, 0);

    glColor3f(0.8, 0.2, 0.2);
    drawRectangle(carX + 20, 0, carX + 120, 30);

    glColor3f(0, 0, 0);
    drawRectangle(carX + 25, -55, carX + 50, -40);
    drawRectangle(carX + 90, -55, carX + 115, -40);
}

void drawGate() {
    glPushMatrix();
    glTranslatef(150, 0, 0);
    glRotatef(gateAngle, 0, 0, 1);

    glColor3f(1, 0, 0);
    drawRectangle(0, 0, 120, 8);

    glPopMatrix();
}

void drawBooth() {
    glColor3f(0.7, 0.7, 0.7);
    drawRectangle(100, 0, 250, 150);

    glColor3f(0.2, 0.6, 1.0);
    drawRectangle(130, 60, 220, 130);

    glColor3f(0.4, 0.4, 0.4);
    drawRectangle(160, 0, 200, 60);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(0.2, 0.6, 1.0);
        glVertex2f(-500, 300);
        glVertex2f(500, 300);
        glColor3f(0.6, 0.8, 1.0);
        glVertex2f(500, 0);
        glVertex2f(-500, 0);
    glEnd();

    glColor3f(0.2, 0.2, 0.2);
    drawRectangle(-500, -100, 500, -200);

    glColor3f(1, 1, 0);
    drawRectangle(-500, -145, 500, -155);

    drawBooth();
    drawGate();
    drawCar();

    glutSwapBuffers();
}

void timer(int value) {

    if (!gateOpen && carX < 50) {
        carX += 1;
    }

    if (gateOpen && gateAngle < 70) {
        gateAngle += 2;
    }

    if (gateOpen && gateAngle >= 70) {
        carX += 2;
    }

    if (carX > 600) {
        carX = -500;
        gateOpen = 0;
        gateAngle = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {

    case 'p':
        gateOpen = 1;
        break;

    case 's':
        gateOpen = 0;
        gateAngle = 0;
        break;

    case 'r':
        carX = -500;
        gateOpen = 0;
        gateAngle = 0;
        break;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.4, 0.7, 1.0, 1.0);
    gluOrtho2D(-500, 500, -300, 300);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Toll Booth Project (2D)");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
