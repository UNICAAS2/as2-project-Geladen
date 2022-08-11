#include <cg3/viewer/mainwindow.h>

#include "managers/trapezoidalmap_manager.h"
#include "data_structures/trapezoid.h"
#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>

int main(int argc, char *argv[]) {

    /*cg3::Point2d punto1(1,1);
    cg3::Point2d punto2(1,2);
    cg3::Point2d punto3(2,1);
    cg3::Point2d punto4(2,2);
    cg3::Segment2d s1(punto1, punto2);
    cg3::Segment2d s2(punto3, punto4);
    cg3::Point2d punto5(4,8);
    cg3::Point2d punto6(3,9);
    Trapezoid trap(punto5,punto6,s1,s2);

    qDebug() << punto3.x() ;;*/

    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

    QApplication app(argc, argv);

    //Main window, it contains QGLViewer canvas
    cg3::viewer::MainWindow gui;

    //Voronoi manager initialization
    TrapezoidalMapManager vm(&gui);
    gui.addManager(&vm, "Trapezoidal map Manager");

    //Show the GUI
    gui.updateCanvas();
    gui.show();

    return app.exec();
}
