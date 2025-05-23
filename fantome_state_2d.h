#ifndef FANTOME_STATE_2D_H
#define FANTOME_STATE_2D_H

#include "core/string/string_name.h"
#include "core/object/class_db.h"
#include "core/object/gdvirtual.gen.inc"
#include "scene/main/node.h"
#include "fantome_state_controller_2d.h"
#include "fantome_state_set_2d.h"

class FantomeState2D : public Node {
    GDCLASS(FantomeState2D, Node);

public:
    int64_t priority = 0;
    bool relative_to_set = true;

    void set_priority(const int64_t p_priority);
    int64_t get_priority() const;
    void set_relative_to_set(const bool p_value);
    bool get_relative_to_set();

    void enter_controller(FantomeStateController2D* p_controller);
    void exit_controller();

    FantomeStateController2D* get_controller();
    FantomeStateSet2D* get_state_set();

    bool can_switch();

    void begin();
    void end();

    static bool compare_by_priority(const Variant &p_a, const Variant &p_b);

protected:
    GDVIRTUAL0(_enter_controller);
    GDVIRTUAL0(_exit_controller);

    GDVIRTUAL0R(bool, _can_switch);

    GDVIRTUAL0(_begin);
    GDVIRTUAL0(_end);

    void _notification(int p_what);
    static void _bind_methods();

private:
    FantomeStateController2D* _controller = nullptr;
};

#endif // FANTOME_STATE_2D_H