#include <cg3/viewer/mainwindow.h>

#include "managers/trapezoidalmap_manager.h"
#include "data_structures/trapezoid.h"
#include "data_structures/trapezoidalmap.h"
#include "data_structures/dag.h"
#include "algorithms/algorithms.h"
#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>
using namespace Algorithms;

int main(int argc, char *argv[]) {

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
