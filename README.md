## MetaPopulation Fragmentation Model (mpfm)

#### Installation and Running

Compile mpfm by running `make`.
Clean directory with `make clean`.
Run mpfm with `make run` or `./mpfm`
Use `mpfm -h` for usage. 	

Data will be created in `$(MPFM_DIRECTORY)/data`. By default, each run is stored in a directory named for the epoch time at the run's start (this can be overridden with the `-p` flag). Various visualization tools can be invoked from this run directory using the symlinks to visualization scripts.

----

### Directory Structure

### `src`
`src` contains all of the source code. It is structured as

	|--mpfm
	     |--src/
		|--board/
		|--patch/
		|--individual/
		|--envFactor/
		|--fractal/
		|--fragment
		|--genome/
		|--logger/
		|--random/
		|--util/
		|--include.h
		|--params.h
		|--main.cc

##### Core Classes
`board` contains the source and header files for the `Board` class.
`patch` contains the source and header files for the `Patch` class.
`individual` contains the source and header files for the `Individual` class.
`envFactor` contains the source and header files for the `envFactor` class.

##### Utilities
`logger` containers the `Logger` class, which is used to write and save data.
`random` contains the `Random` class, which is used for random number generation.
`util` contains various utility functions, primarily involved in command line argument parsing.
##### Files
`include.h` contains includes for libraries used across all files.
`params.h` contains `#define`s for default parameter values
`main.cc` includes the `int main()` function, and setup and running of the model.

-----
### `vis-tools`

`vis-tools` contains Python scripts used for visualizing data from `mpfm`'s source.

These should rarely be run from the `vis-tools` directory because symlinks to these scripts are created in each run directory.

-----
### `data`

Data contains directories from each run. Each run has its own directory within `data/`, with the directory's name being the epoch time of the start of the run.

Each run data contains the following:
`metadata.txt`: Includes `RANDOM_SEED` value, parameter values, and time of run.
`EnvFactors/` : contains `.csv`s of the Environmental factor maps.
`Fragment/` : contains`fragment_map.csv`, which shows all the patches that will be marked fragmented, and `fragment_data.csv` contains fragmentation data.

-----
