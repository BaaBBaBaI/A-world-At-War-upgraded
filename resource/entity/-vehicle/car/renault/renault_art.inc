
	(include "/properties/car.ext")
	(include "/properties/shadow/tank.inc"  scale(1.0))
	(include "/properties/selection/vehicle.inc"  scale(1.1))
	{props "vehicle" "car" "wheeled" "vision_vehicle_medium"}
  	{able "emit_on_attack"}
	
  	("crew_2_human")
  	("board_animation"
    		place(driver)
   		board_begin(board_big-highcar_driver)
   		board_end(seat_driver_car)
   		base(doorleft)
  	)
  	("board_animation"
		place(commander)	
		board_begin(board_big-highcar)
    		board_end(seat_passenger)
  		base(doorright)
  	)

	("wheel" args "wheelright1")
	("wheel" args "wheelleft1")
	("wheel" args "wheelright2")
	("wheel" args "wheelleft2")

	{Volume "shield"
		{thickness 2}
	}
	{mass 4000}

  	{Chassis
    		{Locomotion ("locomotion")
      			{TurnRadius 6}
      			{MaxSpeed   36}
      			{maxSpeedAtMaxTurn 12}
    		}
		{FuelBag
			{volume 82 }	
			{rate	20 }   
			{remain 82 }
			{fuel "fuel"}
		}
		{speed
        		{Normal  12}
        		{Slow  20}
    		}
		("car_trace" fx("tracewheel02") step(0.09) wheell("wlf") wheelr("wrf") bonel("FXtraceL1") boner("FXtraceR1"))
		("car_trace" fx("tracewheel02") step(0.09) wheell("wlr") wheelr("wrr") bonel("FXtraceL2") boner("FXtraceR2"))
  	}

	{extender "shield"
		{on}
	}


	{Extension "renault_art.mdl"}
