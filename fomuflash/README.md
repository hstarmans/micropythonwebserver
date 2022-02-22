# Fomu FPGA Tools

Micropython fork of [Fomuflash](https://github.com/im-tomu/fomu-flash).  Working with Flash memories can be quite tricky as there are a 
wide array of commands. Each memory chip can have it's own pecularities.
Fomuflash takes care of a lot of these challenges.
I therefore ported this library to Micropython using C. I was too lazy to write a pure Python library.

Most functions are ported from the original library but only a few are exposed to python.  
The following functions can be called from Micropython;  
* reset fpga chip
* read memory id
* flash binary to memory
