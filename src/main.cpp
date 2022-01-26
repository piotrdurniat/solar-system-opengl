#include "main.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

bool displayNormals = false;

// Time in ms between each update
int updateInterval = 15;

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
    lightPoint->updatePos();

    if (mouseStatus == MouseStatus::leftDown)
    {

        viewer->thetaAdd(mousePosDiff[0] * pix2angle);
        viewer->phiAdd(mousePosDiff[1] * pix2angle);
    }
    else if (mouseStatus == MouseStatus::rightDown)
    {

        const float zoomSpeed = 0.05;
        viewer->rAdd(zoomSpeed * mousePosDiff[1]);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    viewer->updatePos();
    drawAxes();

    sun->display();

    mercury->display();
    venus->display();
    earth->display();
    mars->display();
    jupiter->display();
    saturn->display();
    uranus->display();
    neptune->display();

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

    float scale = 10000;

    float sunR = 26000.0 / scale;

    float mercuryR = 2439.7 / scale;
    float venusR = 6051.8 / scale;
    float earthR = 6371.0 / scale;
    float marsR = 3389.5 / scale;
    float jupiterR = 16000.0 / scale;
    float saturnR = 12000.0 / scale;
    float uranusR = 9000.0 / scale;
    float neptuneR = 8500.0 / scale;

    float spacing = 4000.0 / scale;

    float mercuryDist = sunR + mercuryR + spacing;
    float venusDist = mercuryDist + mercuryR + venusR + spacing;
    float earthDist = venusDist + venusR + earthR + spacing;
    float marsDist = earthDist + earthR + marsR + spacing;
    float jupiterDist = marsDist + marsR + jupiterR + spacing;
    float saturnDist = jupiterDist + jupiterR + saturnR + spacing;
    float uranusDist = saturnDist + saturnR + uranusR + spacing;
    float neptuneDist = uranusDist + uranusR + neptuneR + spacing;

    sun = new Planet(sunR, 0.0, "../textures/sun.tga");
    sun->invertNormals();

    mercury = new Planet(mercuryR, mercuryDist, "../textures/mercury.tga");
    venus = new Planet(venusR, venusDist, "../textures/venus.tga");
    earth = new Planet(earthR, earthDist, "../textures/earth.tga");
    mars = new Planet(marsR, marsDist, "../textures/mars.tga");
    jupiter = new Planet(jupiterR, jupiterDist, "../textures/jupiter.tga");
    saturn = new Planet(saturnR, saturnDist, "../textures/saturn.tga");
    uranus = new Planet(uranusR, uranusDist, "../textures/uranus.tga");
    neptune = new Planet(neptuneR, neptuneDist, "../textures/neptune.tga");

    // ->setDrawNormals(displayNormals);
    viewer = new Viewer();

    lightPoint = new LightPoint(0.0, 0.00001, 0.0, GL_LIGHT0);

    lightPoint->setAmbient(0.1, 0.1, 0.1, 1.0);
    lightPoint->setDiffuse(1.0, 1.0, 1.0, 1.0);
    lightPoint->setSpecular(1.0, 1.0, 1.0, 1.0);

    // sphere->setDisplayMode(DisplayMode::filledTriangles);

    // background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    setupMaterial();
}

void changeSize(GLsizei horizontal, GLsizei vertical)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 1.0, 1.0, 300.0);

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

void viewerControlMode()
{
    // controlMode = 2;
    printf("\nSterowanie polozeniem obserwatora\n\n");
    printf("Przy wcisnietym lewym klawiszu myszy, ruch kursora myszy w kierunku poziomym powoduje proporcjonalna zmiane azymutu kata Theta.\n");
    printf("Przy wcisnietym lewym klawiszu myszy, ruch kursora myszy w kierunku pionowym powoduje proporcjonalna zmiane kata elewacji Phi.\n");
    printf("Przy wcisnietym prawym klawiszu myszy, ruchy kursora myszy w kierunku pionowym realizuja zmiane promienia R (odleglosci obserwatora od srodka ukladu wspolrzednych).\n");
}

void keys(unsigned char key, int x, int y)
{

    // renderScene();
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

    viewerControlMode();

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

    // timerStart(update, 150);
    glutTimerFunc(updateInterval, update, 100);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    exit(0);
}

void setupMaterial()
{
    // Definicja materiału z jakiego zrobiony jest czajnik

    // GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};

    // współczynniki ka =[kar,kag,kab] dla światła otoczenia

    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    // GLfloat mat_diffuse[] = {0.0, 0.0, 0.0, 0.0};

    // współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    // współczynniki ks =[ksr,ksg,ksb] dla światła odbitego

    GLfloat mat_shininess = {20.0};
    // współczynnik n opisujący połysk powierzchni

    /*************************************************************************************/
    // Ustawienie parametrów materiału i źródła światła

    lightPoint->setup();
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

    lightPoint->enable();
    // blueLightPoint->enable();

    glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

    /*************************************************************************************/
}

void update(int value)
{
    mercury->update();
    venus->update();
    earth->update();
    mars->update();
    jupiter->update();
    saturn->update();
    uranus->update();
    neptune->update();

    glutTimerFunc(updateInterval, update, 0);
    glutPostRedisplay();
}

void timerStart(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]()
                {
                    while (true)
                    {
                        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
                        func();
                        std::this_thread::sleep_until(x);
                    }
                })
        .detach();
}
