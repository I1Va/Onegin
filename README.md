# Onegin


Program that performs transformations on text

## Installation

```shell
git clone https://github.com/I1Va/Onegin.git

make
```

## Usage
```shell
./build/onegin.out <input_file> <output_file>
```
Before running, create an input data file in the root directory of the project and specify its name in <input_file>
<!-- ![example_mode.png](images/example_mode.png)

```shell
make testing
```
![testing_mode.png](images/testing_mode.png)

```shell
make launch
```
![User_mode.png](images/user_mode.png)

```shell
make parsing
```
![parsing mode](images/parsing_mode.png)

## Features
1.  ***testing mode***
  * Support manual testing mode:
    * Write your tests into `MANUAL_TESTS[]` variable of `quadr_equ_solver_funcs.cpp` file
    * Or write your tests into `PATH_AUTO_TESTS`, launch auto tests mode and enter 0 in tests generate number question. In this case programm won't erase data from your tests file
  * Support auto testing mode
    * Generates chosen number of random quadratic equations into file `PATH_AUTO_TESTS`
  * Suppor reading tests from array and file

2.  ***Self-written random generator***

    Based on *Linear congruential generator*:

    $X_{i+1} = (aX_{i} + c) \mod m$

    With *Borland C/C++ constants* ([see other constants](https://en.wikipedia.org/wiki/Linear_congruential_generator))

    $m = 2^{32};\ a = 22695477;\ c = 1;$
    Writes current seed into file located by `PATH_CUR_SEED[]` (see section: ([Settings](https://github.com/I1Va/quadr_equ/tree/progress?tab=readme-ov-file#settings)))

3. ***Color output***

4. ***Quadratic equation parsing mode***
  * Parse entered quadratic equation
  * Process extra spaces
  * Maintains x**2 or x^2 records of x² member

## Settings

You can change system variables in file `quadr_equ/quadr_config.h`:

`PATH_AUTO_TESTS[]` — path to auto tests generating in testing mode


`PATH_CUR_SEED[]` — path to file in which random generator will write current random number


`PATH_EXAMPLE[]` — path, where example quadratic equation is located (from example mode)

## Documentation
To create documentation by doxygen by command:

```shell
doxygen doxygen.config
```

Html file locates in `quadr_equ/html/index.html`

 -->










