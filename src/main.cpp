#include "main.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int controlMode = 1;
int viewModel = 1;
bool displayNormals = false;

void drawAxes(void)
{
    // Start and end position for X axis
    point3 xStart = {-5.0, 0.0, 0.0};
    point3 xEnd = {5.0, 0.0, 0.0};

    // Start and end position for Y axis
    point3 yStart = {0.0, -5.0, 0.0};
    point3 yEnd = {0.0, 5.0, 0.0};

    // Start and end position for Z axis
    point3 zStart = {0.0, 0.0, -5.0};
    point3 zEnd = {0.0, 0.0, 5.0};

    // Red drawing color
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);

    glVertex3fv(xStart);
    glVertex3fv(xEnd);

    glEnd();

    // Green drawing color
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);

    glVertex3fv(yStart);
    glVertex3fv(yEnd);

    glEnd();

    // Blue drawing color
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);

    glVertex3fv(zStart);
    glVertex3fv(zEnd);

    glEnd();
}

void renderScene(void)
{
    if (mouseStatus == MouseStatus::leftDown)
    {
        if (controlMode == 2)
        {
            viewer->thetaAdd(mousePosDiff[0] * pix2angle);
            viewer->phiAdd(mousePosDiff[1] * pix2angle);
        }
        else
        {
            redLightPoint->thetaAdd(-mousePosDiff[0] * pix2angle);
            redLightPoint->phiAdd(-mousePosDiff[1] * pix2angle);
        }
    }
    else if (mouseStatus == MouseStatus::rightDown)
    {

        if (controlMode == 2)
        {
            const float zoomSpeed = 0.05;
            viewer->rAdd(zoomSpeed * mousePosDiff[1]);
        }
        else
        {
            // blueLightPoint->thetaAdd(-mousePosDiff[0] * pix2angle);
            // blueLightPoint->phiAdd(-mousePosDiff[1] * pix2angle);
        }
    }

    // blueLightPoint->updatePos();
    redLightPoint->updatePos();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    viewer->updatePos();

    drawAxes();

    mercury->display();
    venus->display();

    glFlush();
    glutSwapBuffers();
}

void init(void)
{

    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // sphere = new Sphere(sectorCount, stackCount, 5.0f);

    mercury = new Planet(1.5, 1, "../textures/mercury.tga");
    venus = new Planet(1.5, 4, "../textures/venus.tga");

    // ->setDrawNormals(displayNormals);
    viewer = new Viewer();

    redLightPoint = new LightPoint(0.5, 0.5, 14.0, GL_LIGHT0);

    redLightPoint->setAmbient(0.1, 0.1, 0.1, 1.0);
    redLightPoint->setDiffuse(1.0, 1.0, 1.0, 1.0);
    redLightPoint->setSpecular(1.0, 1.0, 1.0, 1.0);

    // sphere->setDisplayMode(DisplayMode::filledTriangles);

    // background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    setupMaterial();
}

void changeSize(GLsizei horizontal, GLsizei vertical)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 1.0, 1.0, 30.0);

    if (horizontal <= vertical)
    {
        glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
    }
    else
    {
        glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int btn, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        mousePosOld[0] = x;
        mousePosOld[1] = y;
        if (btn == GLUT_LEFT_BUTTON)
        {
            mouseStatus = MouseStatus::leftDown;
        }
        else if (btn == GLUT_RIGHT_BUTTON)
        {
            mouseStatus = MouseStatus::rightDown;
        }
    }
    else
    {
        mouseStatus = MouseStatus::allUp;
    }
}

void motion(GLsizei x, GLsizei y)
{
    mousePosDiff[0] = x - mousePosOld[0];
    mousePosDiff[1] = y - mousePosOld[1];

    mousePosOld[0] = x;
    mousePosOld[1] = y;

    glutPostRedisplay();
}

void lightControlMode()
{
    controlMode = 1;
    printf("\nSterowanie polezoniem zrodla swiatla\n\n");
    printf("Przy wcisnietym lewym klawiszu myszy, ruch kursora myszy w kierunku poziomym powoduje proporcjonalna zmiane azymutu kata Theta dla zrodla.\n");
    printf("Przy wcisnietym prawym klawiszu myszy, ruch kursora myszy w kierunku poziomym powoduje proporcjonalna zmiane azymutu kata Theta dla zrodla.\n");
}

void viewerControlMode()
{
    controlMode = 2;
    printf("\nSterowanie polozeniem obserwatora\n\n");
    printf("Przy wcisnietym lewym klawiszu myszy, ruch kursora myszy w kierunku poziomym powoduje proporcjonalna zmiane azymutu kata Theta.\n");
    printf("Przy wcisnietym lewym klawiszu myszy, ruch kursora myszy w kierunku pionowym powoduje proporcjonalna zmiane kata elewacji Phi.\n");
    printf("Przy wcisnietym prawym klawiszu myszy, ruchy kursora myszy w kierunku pionowym realizuja zmiane promienia R (odleglosci obserwatora od srodka ukladu wspolrzednych).\n");
}

void keys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        lightControlMode();
        break;
    case '2':
        viewerControlMode();
        break;
    }
    renderScene();
}

int main(int argc, char *argv[])
{
    try
    {
        po::options_description desc{"Options"};

        //@formatter:off
        desc.add_options()("help,h", "Help screen")("sectorCount", po::value<int>()->default_value(40), "Number of sectors")("stackCount", po::value<int>()->default_value(40), "Number of stacks")("dispNorm,d", "Display model normals on screen");
        //@formatter:on

        po::variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << '\n';
            return 1;
        }
        if (vm.count("sectorCount"))
        {
            std::cout << "Number of sectors was set to: " << vm["sectorCount"].as<int>() << '\n';
            sectorCount = vm["sectorCount"].as<int>();
        }
        if (vm.count("stackCount"))
        {
            std::cout << "Number of stacks was set to: " << vm["stackCount"].as<int>() << '\n';
            stackCount = vm["stackCount"].as<int>();
        }
        if (vm.count("dispNorm"))
        {
            std::cout << "Display normals\n";
            displayNormals = true;
        }
    }
    catch (const po::error &ex)
    {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    lightControlMode();

    printf("Sterowanie: \n");
    printf("Klawisz \"1\" - przelaczenie trybu na sterowanie polozeniem swiatla\n");
    printf("Klawisz \"2\" - przelaczenie trybu na sterowanie polozeniem obserwatora\n");

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);

    glutCreateWindow("GKiKCK - laboratorium 7");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keys);
    glutMotionFunc(motion);

    init();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    exit(0);
}

void setupMaterial()
{
    // Definicja materiału z jakiego zrobiony jest czajnik

    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    // współczynniki ka =[kar,kag,kab] dla światła otoczenia

    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    // współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    // współczynniki ks =[ksr,ksg,ksb] dla światła odbitego

    GLfloat mat_shininess = {20.0};
    // współczynnik n opisujący połysk powierzchni

    /*************************************************************************************/
    // Ustawienie parametrów materiału i źródła światła

    redLightPoint->setup();
    // blueLightPoint->setup();

    /*************************************************************************************/
    // Ustawienie patrametrów materiału

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    /*************************************************************************************/
    // Ustawienie opcji systemu oświetlania sceny

    glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
    glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny

    redLightPoint->enable();
    // blueLightPoint->enable();

    glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

    /*************************************************************************************/
}

// void loadTexture(const char *fileName)
// {
//     GLbyte *pBytes;
//     GLint ImWidth, ImHeight, ImComponents;
//     GLenum ImFormat;

//     //  Load texture
//     pBytes = Texture::LoadTGAImage(fileName, &ImWidth, &ImHeight, &ImComponents, &ImFormat);
//     // Define texture
//     glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);
//     // Free memory
//     free(pBytes);
// }
