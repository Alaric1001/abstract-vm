# AbstractVM
Little pseudo-assembly interpretor written in cpp17.
The project coding guidelines were:
* Typed numerics
* Error handling via exception
* Use of the IOperand interface as it is given in the subject.

## Build & make

Just use `make` enventually with `-j`

## Usage
`./abstract-vm [file]`
#### Options
```
-i intercative mode
-v verbose mode
```

## Instructions
**Comments**: Comments start with a ’;’ and finish with a newline. A comment canbe either at the start of a line, or after an instruction.

**push *v***: Pushes the value at the top of the stack. The value must have one of the following form:

	int8(n): Creates an 8-bit integer with value n.
	int16(n): Creates a 16-bit integer with value n.
	int32(n): Creates a 32-bit integer with value n.
	float(z): Creates a float with value z.
	double(z): Creates a double with value z.

**pop**: Unstacks the value from the top of the stack. If the stack is empty, the program execution must stop with an error.

**dump**: Displays each value of the stack, from the most recent one to the oldest one.

**assert *v***: Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction. If it is not the case, the program execution stop with an error. The value has the same form that those passed as parameters to the instruction push.

**add**: Unstacks the first two values on the stack, adds them together and stacks the result.

**sub**: Unstacks the first two values on the stack, subtracts them, then stacks the result.

**mul**: Unstacks the first two values on the stack, multiplies them, then stacks the result.

**div**: Unstacks the first two values on the stack, divides them, then stacks the result.

**mod**: Unstacks the first two values on the stack, calculates the modulus, then stacks the result.

**print**: Asserts that the value at the top of the stack is an 8-bit integer. (If not,see the instruction assert), then interprets it as an ASCII value and displays the corresponding character on the standard output.

**exit**: Terminate the execution of the current program.

## Example program

```
; Example.avm

push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
exit
```

#### Output

```
$> ./abstract-vm Example.avm
42
42.42
3341.25
```

**This project is a student exercise and is by no mean intended to be used at all**
