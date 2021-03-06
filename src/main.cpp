#include "main.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

bool displayNormals = false;

// Time in ms between each update
int updateInterval = 15;

GLfloat skyR = 100000;

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

    sun->display();
    sky->display();

    for (CelestialBody *planet : planets)
    {
        planet->display();
    }

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

    GLfloat scale = 10000;

    GLfloat sunR = 26000.0 / scale;

    GLfloat radiuses[planetCount] = {
        2439.7f / scale,
        6051.8f / scale,
        6371.0f / scale,
        3389.5f / scale,
        16000.0f / scale,
        12000.0f / scale,
        9000.0f / scale,
        8500.0f / scale};

    float spacing = 4000.0 / scale;

    const char *textures[planetCount] = {
        "../textures/mercury.tga",
        "../textures/venus.tga",
        "../textures/earth.tga",
        "../textures/mars.tga",
        "../textures/jupiter.tga",
        "../textures/saturn.tga",
        "../textures/uranus.tga",
        "../textures/neptune.tga"};

    sun = new CelestialBody(sunR, 0.0, 0.0, 0.0, "../textures/sun.tga");
    sky = new CelestialBody(skyR, 0.0, 0.0, 0.0, "../textures/sky.tga");

    sun->invertNormals();
    sky->invertNormals();

    GLfloat distances[planetCount];

    GLfloat orbitalPeriods[planetCount] = {
        0.240846,
        0.615198,
        1,
        1.9,
        11.9,
        29.5,
        84.0,
        164.8};

    float distance = sunR;
    for (int i = 0; i < planetCount; ++i)
    {
        distance += spacing;
        distance += radiuses[i];
        distance += radiuses[i];

        const GLfloat timeScale = 0.5;

        GLfloat orbitalAngularSpeed = timeScale / orbitalPeriods[i];

        planets[i] = new CelestialBody(radiuses[i], distance, orbitalAngularSpeed, 0.5, textures[i]);
    }

    const GLfloat moonR = 1737.5 / scale;

    CelestialBody *moon = new CelestialBody(moonR, 0.9, 13, 13, "../textures/moon.tga");

    // Set earth's axial tilt
    planets[2]->setAxialTilt(23.4392811);

    // Add the moon to the earth
    planets[2]->setMoon(moon);

    viewer = new Viewer();

    lightPoint = new LightPoint(0.0, 0.00001, 0.0, GL_LIGHT0);

    lightPoint->setAmbient(0.1, 0.1, 0.1, 1.0);
    lightPoint->setDiffuse(1.0, 1.0, 1.0, 1.0);
    lightPoint->setSpecular(1.0, 1.0, 1.0, 1.0);

    // background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    setupMaterial();
}

void changeSize(int horizontal, int vertical)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = (GLfloat)horizontal / (GLfloat)vertical;

    glViewport(0, 0, (GLsizei)horizontal, (GLsizei)vertical);
    gluPerspective(70, aspect, 0.1, skyR * 3);

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

    glutCreateWindow("Solar system model");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keys);
    glutMotionFunc(motion);

    init();

    glutTimerFunc(updateInterval, update, 100);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    exit(0);
}

void setupMaterial()
{
    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess = {20.0};
    lightPoint->setup();
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    lightPoint->enable();

    glEnable(GL_DEPTH_TEST);
}

void update(int value)
{

    for (CelestialBody *planet : planets)
    {
        planet->update();
    }

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
                    } })
        .detach();
}
