hootsim2000
===========

A sequel to the extensible agent event based simulator, Hootsim.

### Requirements

The usual C++ building and compiling tools available from all good distributions and ```cmake```.

### Install

    $ mkdir build
    $ cd build
    $ cmake ../
    $ make

### Example

    $ build/hootsim2000
    TO	FROM	MESSAGE
    -1	1	Controller C1 adds hooting as requirement
    -1	1	Controller C1 adds nocturnal as requirement
    -1	2	Entity E2 adds property pair nocturnal:1
    -1	0	Simulator received instruction to destroy all controllers after add_property
    -1	2	Entity E2 adds property pair hooting:1
    -1	0	Simulator received instruction to destroy all controllers after add_property
    -1	0	Simulator auto attached E2 to C1 after meeting requirements
    -1	2	Entity E2 adds property pair health:100
    -1	0	Simulator received instruction to destroy all controllers after add_property
    -1	0	Simulator auto attached E2 to C1 after meeting requirements
