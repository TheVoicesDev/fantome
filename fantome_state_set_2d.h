#ifndef FANTOME_STATE_SET_2D
#define FANTOME_STATE_SET_2D

#include "core/variant/typed_array.h"
#include "scene/main/node.h"
#include "fantome_state_2d.h"
#include "fantome_state_controller_2d.h"

template <typename T>
class TypedArray;

class FantomeState2D;
class FantomeStateController2D;

class FantomeStateSet2D : public Node {
    GDCLASS(FantomeStateSet2D, Node);

public:
    TypedArray<FantomeState2D> states;

    TypedArray<FantomeState2D> get_states() const;
    void update_states();

    FantomeStateController2D* get_controller() const;

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);
    static void _bind_methods();
    
private:
    FantomeStateController2D* _controller;
};

#endif