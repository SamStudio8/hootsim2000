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
    TO	FROM	MSG_TYPE	MESSAGE
    -1	-1	health_loss	Controller C0 listening for add_prop
    -1	0	add_require	Controller C0 adds is_simulator as requirement
    -1	-1	health_loss	Controller C6 listening for health_pack
    -1	1	add_require	Controller C1 adds hooting as requirement
    -1	1	add_require	Controller C1 adds nocturnal as requirement
    -1	-1	health_loss	Controller C-1132421201 listening for health_crit
    -1	3	add_require	Controller C3 adds has_doctorate as requirement
    -1	2	add_prop	Entity E2 adds property pair nocturnal:1
    -1	0	sim_dcon	Simulator received instruction to destroy all controllers after add_property
    -1	2	add_prop	Entity E2 adds property pair hooting:1
    -1	0	sim_dcon	Simulator received instruction to destroy all controllers after add_property
    -1	0	auto_attach	Simulator auto attached E2 to C1 after meeting requirements
    -1	2	add_prop	Entity E2 adds property pair health:100
    -1	0	sim_dcon	Simulator received instruction to destroy all controllers after add_property
    -1	0	auto_attach	Simulator auto attached E2 to C1 after meeting requirements
    -1	4	add_prop	Entity E4 adds property pair has_doctorate:1
    -1	0	sim_dcon	Simulator received instruction to destroy all controllers after add_property
    -1	0	auto_attach	Simulator auto attached E2 to C1 after meeting requirements
    -1	0	auto_attach	Simulator auto attached E4 to C3 after meeting requirements
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:90
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:80
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:70
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:60
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:50
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:40
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:30
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:20
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:10
    -1	2	health_crit	Entity health is critical! Call a doctor!
    2	4	health_pack	Doctor E4 sends medical aid to Entity E2
    -1	2	health_okay	Entity E2 health restored!
    -1	2	update_prop	Entity E2 updates property pair health:100
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:90
    -1	0	sim_tick	Simulation tick.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:80
