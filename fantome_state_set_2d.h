#ifndef FANTOME_STATE_SET_2D
#define FANTOME_STATE_SET_2D

#include "scene/main/node.h"
#include "fantome_state_2d.h"
#include "fantome_state_controller_2d.h"

class FantomeStateSet2D : public Node {
    GDCLASS(FantomeStateSet2D, Node);

public:
    TypedArray<FantomeState2D> states;

    TypedArray<FantomeState2D> get_states() const;

protected:
    void _notification(int p_what);
    static void _bind_methods();
    
private:
    FantomeStateController2D* _controller;
};

#endif