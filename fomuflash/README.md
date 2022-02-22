# Fomu FPGA Tools

Micropython fork of [Fomuflash](https://github.com/im-tomu/fomu-flash).  Working with Flash memories can be quite tricky as there are a 
wide array of commands. Each memory chip can have its own pecularities.
Fomuflash takes care of a lot of these challenges.
I therefore ported this library to Micropython using C. I was too lazy to write a pure Python library.

Compile following the instruction on Micropython main [website](https://docs.micropython.org/en/latest/develop/extendingmicropython.html).
```
make USER_C_MODULES=enter_correct_path_here/fomuflash/micropython.cmake
```

Most functions are ported from the original library but only a few are exposed to python.  
The following functions can be called from Micropython;  
* reset fpga chip
* read memory id
* flash binary to memory
