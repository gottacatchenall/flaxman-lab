## MetaPopulation Fragmentation Model (mpfm)

#### Installation and Running

Compile mpfm by running `make`.
Clean directory with `make clean`.
Run mpfm with `make run` or `./mpfm`
Use `mpfm -h` for usage. 	

----

### Directory Structure

### `src`
`src` contains all of the source code. It is structured as

	|mpfm
	  |--src/
	      |--board/
	      |--tile/
		  |--individual/
		  |--envFactor/
		  |--logger/
		  |--random/
		  |--util/
		  |--include.h
		  |--params.h
		  |--main.cc

##### Core Classes
`board` contains the source and header files for the `Board` class.
`tile` contains the source and header files for the `Tile` class.
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

-----
### `data`

Data contains directories from each run. Each run has its own directory within `data/`, with the directories name being the epoch time of the start of the run.

Each run data contains the following:
`metadata.txt`: Includes `RANDOM_SEED` value, parameter values, and time of run.
`EnvFactors/` : contains `.csv`s of the Environmental factor maps.

-----
