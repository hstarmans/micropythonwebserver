// Include MicroPython API.
#include "py/runtime.h"

// test rik
#include <fomu-flash.h>
#include "py/obj.h"
#include <stdio.h>
#include <string.h>

// This is the function which will be called from Python as fomuflash.main('-h').
STATIC mp_obj_t example_var(size_t n_args, const mp_obj_t *args) {
    // const char *opt=NULL;
    // const char *filename=NULL;
    // mp_uint_t len;
    // printf("door het eerste loepje");
    // for (size_t i = 0; i < n_args; ++i) {
    //     if (i==0)
    //       opt = mp_obj_str_get_data(args[i], &len);
    //     else if (i==1)
    //       filename = mp_obj_str_get_data(args[i], &len);
    // }
    printf("roep nu functie aan");
    int res = expose();
    // Calculate the addition and convert to MicroPython object.
    // int res = 0;
    return mp_obj_new_int(res); 
}
// Define a Python reference to the function above.
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(example_add_ints_obj, 1, 2, example_var);

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t example_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_fomuflash) },
    { MP_ROM_QSTR(MP_QSTR_main), MP_ROM_PTR(&example_add_ints_obj) },
};
STATIC MP_DEFINE_CONST_DICT(example_module_globals, example_module_globals_table);

// Define module object.
const mp_obj_module_t example_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&example_module_globals,
};

// Register the module to make it available in Python.
// Note: the "1" in the third argument means this module is always enabled.
// This "1" can be optionally replaced with a macro like MODULE_CEXAMPLE_ENABLED
// which can then be used to conditionally enable this module.
MP_REGISTER_MODULE(MP_QSTR_fomuflash, example_user_cmodule, 1);
