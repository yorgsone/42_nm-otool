# nm-otool
Rewritting of nm and otool commands as found on MacOS.
! If compiled in a Linux environent it nm will be parsing ELF format instead of Mach-o.

## Compilation
run
```
make
```
and both nm and otool will be compiled

## ft_nm
displays name list (symbol table) of an executable, library, object file and fat file.
If run without args is using a.out if it exists
```
./ft_nm <args>
```

#ft_otool
The otool command displays specified parts of object files or libraries
```
./ft_otool -<flags> <args> 
```
flags:
- f: display the headers of fat files
- a: display the headers of static libraries
- h: display the MACH-O headers
- t: display the contents of the (__TEXT,__text) section
- l: display the load commands
