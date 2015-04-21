#include "resource.h"

namespace resource
{
    Resources ui;

    void load()
    {
        //load our resources
        ui.loadXML("res.xml");
    }

    void free()
    {
        //unload
        ui.free();
    }
}