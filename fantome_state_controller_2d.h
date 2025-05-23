#ifndef FANTOME_STATE_CONTROLLER_2D_H
#define FANTOME_STATE_CONTROLLER_2D_H

#include "core/object/class_db.h"
#include "core/variant/typed_array.h"
#include "core/variant/typed_dictionary.h"
#include "scene/main/node.h"
#include "fantome_character_2d.h"
#include "fantome_state_2d.h"
#include "fantome_state_set_2d.h"

template <typename T>
class TypedArray;

template <typename K, typename V>
class TypedDictionary;

class FantomeStateController2D : public Node {
    GDCLASS(FantomeStateController2D, Node);

public:
    FantomeCharacter2D* get_character() const;
    void update_states();

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);

private:
    FantomeCharacter2D* _character;
    TypedDictionary<StringName, FantomeState2D> _states;
};

#endif // FANTOME_STATE_CONTROLLER_2D_H