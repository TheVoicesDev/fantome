#ifndef FANTOME_ENGINE_H
#define FANTOME_ENGINE_H

#include "core/object/object.h"
#include "core/object/class_db.h"
#include "core/variant/typed_array.h"

template <typename T>
class TypedArray;

class FantomeEngine : public Object {
    GDCLASS(FantomeEngine, Object);

public:
    enum TickMode {
        TICK_MODE_MANUAL,
        TICK_MODE_PROCESS,
        TICK_MODE_PHYSICS_PROCESS
    };

    TickMode tick_mode = TICK_MODE_PHYSICS_PROCESS;
    
    bool initialize();

    void process_ticks();
    int64_t get_ticks_passed();
    int64_t get_delta_ticks();

    void register_state_controller();
    void unregister_state_controller();

protected:
    static void _bind_methods();

private:
    bool _initialized = false;

    int64_t _delta_ticks = 0;
    int64_t _last_physics_frame_count = 0;
};

VARIANT_ENUM_CAST(FantomeEngine::TickMode);

#endif