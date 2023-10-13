# Making a compiler in C for custom language
## Introduction
This is a compiler for a custom language written in C. The language is called `VV` and is a compiled, strictly typed version of `Python` with features from other lagnuages. The compiler is written in C.

## What language should have?

- [ ] Comments
- [ ] Variables
- [ ] Functions
- [ ] Classes
- [ ] Arrays
- [ ] If statements
- [ ] For loops
- [ ] While loops

## Syntax

### Comments
Comments are written with `#` and are single line comments and are ignored by the compiler.

```python
# This is a comment
```

### Variables
`VV` is strictly typed language, so every variable must have a type. There are 4 types in `VV`:
- `int` - integer
- `float` - floating point number
- `string` - string
- `bool` - boolean

Variables are declared with `:` and are assigned with `=`. Variable names can contain letters, numbers and underscores, but must start with a letter.

```
a : integer = 5;
a : string = "Lorem";
a : float = 5.5;
a : bool = true;
```