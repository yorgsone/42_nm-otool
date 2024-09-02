# nm-otool
This project involves rewriting the `nm` command for both **macOS** and **Linux**, and the `otool` command for **macOS**. 

### Compatibility

- The project works on both macOS and Linux.
- `otool` is specific to **macOS**.
- Each operating system uses its native executable format:
  - On **Linux**, `nm` parses **ELF** format files.
  - On **macOS**, both `nm` and `otool` parse **Mach-O** format files.

## Compilation

To compile both `ft_nm` and `ft_otool`, run:

```sh
make
```

## `ft_nm`

The `ft_nm` command displays the name list (symbol table) of an executable, library, object file, or fat file. 

If run without arguments, it uses `a.out` if it exists.

**Usage:**

```sh
./ft_nm <args>
```

## `ft_otool`

The `ft_otool` command displays specified parts of object files or libraries.

**Usage:**

```sh
./ft_otool -<flags> <args>
```

### Flags:

- **`-f`**: Display the headers of fat files  
- **`-a`**: Display the headers of static libraries  
- **`-h`**: Display the Mach-O headers  
- **`-t`**: Display the contents of the `(__TEXT, __text)` section  
- **`-l`**: Display the load commands  
