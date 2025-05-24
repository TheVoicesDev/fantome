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

class FantomeCharacter2D;
class FantomeState2D;

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

    TypedArray<FantomeState2D> _sort_states(const TypedArray<FantomeState2D> &p_array) const;
    TypedArray<FantomeState2D> _merge_state_array(const TypedArray<FantomeState2D> &p_left, const TypedArray<FantomeState2D> &p_right) const;

    TypedDictionary<StringName, FantomeState2D> _state_map;
    TypedArray<FantomeState2D> _state_list;
};

#endif // FANTOME_STATE_CONTROLLER_2D_H