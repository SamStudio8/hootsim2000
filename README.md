hootsim2000
===========

A sequel to the extensible agent event based simulator, Hootsim.  
Now with added flat-pack meddelandekö!

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
    -1	-1	health_loss	Controller C1 listening for health_pack
    -1	-1	health_loss	Controller C1 listening for new_dawn
    -1	1	add_require	Controller C1 adds hooting as requirement
    -1	1	add_require	Controller C1 adds nocturnal as requirement
    -1	-1	health_loss	Controller C3 listening for health_crit
    -1	-1	health_loss	Controller C3 listening for time_noon
    -1	3	add_require	Controller C3 adds has_doctorate as requirement
    -1	-1	health_loss	Controller C5 listening for sim_tick
    -1	5	add_require	Controller C5 adds is_world as requirement
    -1	5	add_require	Controller C5 adds time as requirement
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
    -1	6	add_prop	Entity E6 adds property pair is_world:1
    -1	0	sim_dcon	Simulator received instruction to destroy all controllers after add_property
    -1	0	auto_attach	Simulator auto attached E2 to C1 after meeting requirements
    -1	0	auto_attach	Simulator auto attached E4 to C3 after meeting requirements
    -1	6	add_prop	Entity E6 adds property pair time:0
    -1	0	sim_dcon	Simulator received instruction to destroy all controllers after add_property
    -1	0	auto_attach	Simulator auto attached E2 to C1 after meeting requirements
    -1	0	auto_attach	Simulator auto attached E4 to C3 after meeting requirements
    -1	0	auto_attach	Simulator auto attached E6 to C5 after meeting requirements
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:1
    -1	6	new_hour	World Entity E6 updates hour to 1
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:90
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:2
    -1	6	new_hour	World Entity E6 updates hour to 2
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:80
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:3
    -1	6	new_hour	World Entity E6 updates hour to 3
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:70
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:4
    -1	6	new_hour	World Entity E6 updates hour to 4
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:60
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:5
    -1	6	new_hour	World Entity E6 updates hour to 5
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:50
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:6
    -1	6	new_hour	World Entity E6 updates hour to 6
    -1	6	new_dawn	A new day dawns...
    -1	2	hoot_hoot	Entity E2 hoots!
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:40
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:7
    -1	6	new_hour	World Entity E6 updates hour to 7
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:30
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:8
    -1	6	new_hour	World Entity E6 updates hour to 8
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:20
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:9
    -1	6	new_hour	World Entity E6 updates hour to 9
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:10
    -1	2	health_crit	Entity health is critical! Call a doctor!
    2	4	health_pack	Doctor E4 sends medical aid to Entity E2
    -1	2	health_okay	Entity E2 health restored!
    -1	2	update_prop	Entity E2 updates property pair health:100
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:10
    -1	6	new_hour	World Entity E6 updates hour to 10
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:90
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:11
    -1	6	new_hour	World Entity E6 updates hour to 11
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:80
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:12
    -1	6	new_hour	World Entity E6 updates hour to 12
    -1	6	time_noon	It's noon. Hope you're hungry.
    -1	4	doc_noon	Doctor E4 eats lunch.
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:70
    -1	0	sim_tick	Simulation tick.
    -1	6	update_prop	Entity E6 updates property pair time:13
    -1	6	new_hour	World Entity E6 updates hour to 13
    -1	2	health_loss	Entity E2 suffers attrition!
    -1	2	update_prop	Entity E2 updates property pair health:60
