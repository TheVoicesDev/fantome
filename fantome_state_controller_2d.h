#ifndef FANTOME_STATE_CONTROLLER_2D_H
#define FANTOME_STATE_CONTROLLER_2D_H

#include "core/object/class_db.h"
#include "core/variant/array.h"
#include "core/variant/dictionary.h"
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
    FantomeState2D* initial_state = nullptr;
    TypedArray<String> state_queue;

    void set_initial_state(FantomeState2D* p_value);
    FantomeState2D* get_initial_state() const;
    void set_state_queue(const TypedArray<String> &p_value);
    TypedArray<String> get_state_queue() const;

    FantomeCharacter2D* get_character() const;

    FantomeState2D* get_state(const StringName &p_name) const;
    bool has_state(const StringName &p_name) const;

    Array get_state_names() const;
    Array get_registered_states() const;
    Array get_all_states() const;
    
    void update_states();

    void change_state(const StringName &p_state_name);
    FantomeState2D* get_current_state() const;

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);
    static void _bind_methods();

private:
    FantomeCharacter2D* _character;

    TypedArray<FantomeState2D> _sort_states(const TypedArray<FantomeState2D> &p_array) const;
    TypedArray<FantomeState2D> _merge_state_array(const TypedArray<FantomeState2D> &p_left, const TypedArray<FantomeState2D> &p_right) const;

    TypedDictionary<StringName, FantomeState2D> _state_map;
    TypedArray<FantomeState2D> _state_list;

    FantomeState2D* _current_state = nullptr;
    Dictionary _state_parameters;
};

#endif // FANTOME_STATE_CONTROLLER_2D_H