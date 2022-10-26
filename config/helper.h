/*
 * helper.h
 *
 * Convenience macros simplifying ZMK's keymap configuration.
 * See https://github.com/urob/zmk-nodefree-config for documentation.
 */

#pragma once

#define ZMK_HELPER_STRINGIFY(x) #x

/* ZMK_BEHAVIOR */

#define ZMK_BEHAVIOR_CORE_caps_word   compatible = "zmk,behavior-caps-word";  #binding-cells = <0>
#define ZMK_BEHAVIOR_CORE_hold_tap    compatible = "zmk,behavior-hold-tap";   #binding-cells = <2>
#define ZMK_BEHAVIOR_CORE_key_repeat  compatible = "zmk,behavior-key-repeat"; #binding-cells = <0>
#define ZMK_BEHAVIOR_CORE_macro       compatible = "zmk,behavior-macro";      #binding-cells = <0>
#define ZMK_BEHAVIOR_CORE_mod_morph   compatible = "zmk,behavior-mod-morph";  #binding-cells = <0>
#define ZMK_BEHAVIOR_CORE_sticky_key  compatible = "zmk,behavior-sticky-key"; #binding-cells = <1>
#define ZMK_BEHAVIOR_CORE_tap_dance   compatible = "zmk,behavior-tap-dance";  #binding-cells = <0>

#define ZMK_BEHAVIOR(name, type, ...) \
    / { \
        behaviors { \
            name: name { \
                label = ZMK_HELPER_STRINGIFY(ZB_ ## name); \
                ZMK_BEHAVIOR_CORE_ ## type; \
                __VA_ARGS__ \
            }; \
        }; \
    };

/* ZMK_LAYER */

#define ZMK_LAYER(name, layout) \
    / { \
        keymap { \
            compatible = "zmk,keymap"; \
            name { \
                bindings = <layout>; \
            }; \
        }; \
    };

/* ZMK_COMBOS */

#define ALL 0xff
#if !defined COMBO_TERM
    #define COMBO_TERM 30
#endif

#define ZMK_COMBO(name, combo_bindings, keypos, combo_layers) \
    / { \
        combos { \
            compatible = "zmk,combos"; \
            combo_ ## name { \
                timeout-ms = <COMBO_TERM>; \
                bindings = <combo_bindings>; \
                key-positions = <keypos>; \
                layers = <combo_layers>; \
            }; \
        }; \
    };

#if !defined COMBO_HOOK
    #define COMBO_HOOK
#endif
#define ZMK_COMBO_ADV(name, combo_bindings, keypos, combo_layers, combo_timeout) \
    / { \
        combos { \
            compatible = "zmk,combos"; \
            combo_ ## name { \
                timeout-ms = <combo_timeout>; \
                bindings = <combo_bindings>; \
                key-positions = <keypos>; \
                layers = <combo_layers>; \
                COMBO_HOOK \
            }; \
        }; \
    };

/* ZMK_CONDITIONAL_LAYER */

#define ZMK_CONDITIONAL_LAYER(if_layers, then_layer) \
    / { \
        conditional_layers { \
            compatible = "zmk,conditional-layers"; \
            tri_layer { \
                if-layers = <if_layers>; \
                then-layer = <then_layer>; \
            }; \
        }; \
    };

/* ZMK_MOD_SHIFT */
#define ZMK_MOD_SHIFT(name, base_key, shift_key) \
    / { \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                label = ZMK_HELPER_STRINGIFY(ZMK_MOD_SHIFT_ ## name); \
                #binding-cells = <0>; \
                bindings = <&kp base_key>, <&kp shift_key>; \
                mods = <(MOD_LSFT|MOD_RSFT)>; \
            }; \
        }; \
    };
