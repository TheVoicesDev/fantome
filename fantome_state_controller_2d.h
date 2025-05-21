#ifndef FANTOME_STATE_CONTROLLER_2D_H
#define FANTOME_STATE_CONTROLLER_2D_H

#include "core/object/class_db.h"
#include "core/variant/typed_array.h"
#include "scene/main/node.h"
#include "fantome_character_2d.h"
#include "fantome_state_2d.h"

template <typename T>
class TypedArray;

class FantomeStateController2D : public Node {
    GDCLASS(FantomeStateController2D, Node);

public:
    FantomeCharacter2D* get_character() const;

    void register_state(FantomeState2D* p_state);
    void deregister_state(FantomeState2D* p_state);

protected:
    void _notification(int p_what);

private:
    FantomeCharacter2D* _character;
    TypedArray<FantomeState2D> _states;
};

#endif // FANTOME_STATE_CONTROLLER_2D_H