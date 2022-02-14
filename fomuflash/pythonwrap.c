// Include MicroPython API.
#include "py/runtime.h"


#include "spi.h"
#include "fpga.h"
#include <fomu-flash.h>
#include "py/obj.h"
#include <stdio.h>
#include <string.h>

// Python call as fomuflash.memory_id
STATIC mp_obj_t print_memory_id() {
    struct ff_spi *spi; 
    struct ff_fpga *fpga;
    spi = spiAlloc();
    fpga = fpgaAlloc();
    initfomu(spi, fpga);
    memory_id(spi);
    releasefomu(spi, fpga);
    return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(print_memory_id_obj, print_memory_id);


// Python call as fomuflash.reset_fpga
STATIC mp_obj_t reset_fpga() {
    struct ff_spi *spi;
    struct ff_fpga *fpga;
    spi = spiAlloc();
    fpga = fpgaAlloc();
    initfomu(spi, fpga);
    resetfpga(fpga);
    releasefomu(spi, fpga);
    return mp_const_none; 
}

STATIC MP_DEFINE_CONST_FUN_OBJ_0(reset_fpga_obj, reset_fpga);

// Python call as fomuflash.write_bin
STATIC mp_obj_t write_binary(mp_obj_t file_name) {
    mp_uint_t len;
    const char *p_filename;
    p_filename = mp_obj_str_get_data(file_name, &len);
    printf("DEBUG: filename is = %s\n", p_filename);
    struct ff_spi *spi;
    struct ff_fpga *fpga;
    spi = spiAlloc();
    fpga = fpgaAlloc();
    initfomu(spi, fpga);
    write_bin(spi, p_filename);
    resetfpga(fpga);
    releasefomu(spi, fpga);
    return mp_const_none; 
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(write_bin_obj, write_binary);

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t pythonwrap_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_fomuflash) },
    { MP_ROM_QSTR(MP_QSTR_memoryid), MP_ROM_PTR(&print_memory_id_obj) },
    { MP_ROM_QSTR(MP_QSTR_resetfpga), MP_ROM_PTR(&reset_fpga_obj) },
    { MP_ROM_QSTR(MP_QSTR_writebin), MP_ROM_PTR(&write_bin_obj) },
};
STATIC MP_DEFINE_CONST_DICT(pythonwrap_globals, pythonwrap_globals_table);

// Define module object.
const mp_obj_module_t pythonwrap_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&pythonwrap_globals,
};

// Register the module to make it available in Python.
// Note: the "1" in the third argument means this module is always enabled.
// This "1" can be optionally replaced with a macro like MODULE_CEXAMPLE_ENABLED
// which can then be used to conditionally enable this module.
MP_REGISTER_MODULE(MP_QSTR_fomuflash, pythonwrap_module, 1);
