#include "register_types.h"
#include "voronoi.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#define JC_VORONOI_IMPLEMENTATION
#define JC_VORONOI_IMPLEMENTATION
#define JCV_REAL_TYPE double
#define JCV_ATAN2 atan2
#define JCV_SQRT sqrt
#define JCV_FLT_MAX DBL_MAX
#define JCV_PI 3.141592653589793115997963468544185161590576171875
#define JCV_EDGE_INTERSECT_THRESHOLD 1.0e-5F

#include "jc_voronoi.h"

using namespace godot;

void initialize_voronoi_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<Voronoi>();
    ClassDB::register_class<Site>();
    ClassDB::register_class<Edge>();
    ClassDB::register_class<GraphEdge>();
}

void terminate_voronoi_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT
voronoi_init(GDExtensionInterfaceGetProcAddress
             p_get_proc_address, const GDExtensionClassLibraryPtr p_library,
             GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_voronoi_module);
    init_obj.register_terminator(terminate_voronoi_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}