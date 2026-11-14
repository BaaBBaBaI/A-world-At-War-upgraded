	{props "flesh" "animal_evil" "nocover" "vehicle" "tractor" "obstacle_ignore_height"}
	(include "/properties/animal_crew.ext") 
        (include "/properties/selection/vehicle.inc"  scale(0.5))
        	
	{obstacleID "human"}
	{PatherID "animal"}
	{collider "animal"}
	{lodclass "human"}
	{brain "vehicle"
		{state "vehicle"}
	}
	{targetClass 	"human"}
	{targetSelector "tank_bullet"}
	
	{able "emit_on_attack" "select"}
	{able "ally_crew"}
	{simulation {able 1}}
	{mass 400}
	
{boarder
	{anm "driver"
	{forward	{begin	"board_horse"} {end "seat_horse"} {base "open1"}}
	{reverse 	{end	"board_horse" -1} {base "open1" -1}}
	}
	}
	("crew_human" place(driver) bone(driver) door(emit1) animation(driver))

	{Placer
		{place "driver" {turnOff {targetable}}}
	}

(define "horse_trace_ex"
    {Track "left"
	    {Tracer
    		{View %fx} ; "tracks"
    		{Bone %boneleft}
	    	{Step %step}		; 0.7 meters
    	}
		{TextureScroller
	    	{Bone "TrackL"}
    		{Length %len}		; 0.6 meters per animation
    	}
    	}
    {Track "right"
    	{Tracer 
	    	{View %fx}
    		{Bone %boneright}
    		{Step %step}		; in meters
	    }
		{TextureScroller
	    	{Bone "TrackR"}
    		{Length %len}		; meters per animation
    	}
    	}
	)

	(define "horse_trace"
	("horse_trace_ex" fx(%fx) step(%step) len(%len) boneleft("FXtraceL1") boneright("FXtraceR1"))
	("horse_trace_ex" fx(%fx) step(%step) len(%len) boneleft("FXtraceL2") boneright("FXtraceR2"))
	)
	
	{Chassis "track"
	;("horse_trace" fx("tracks_horse") step(1.15) len(0.45))
	{Locomotion
		{maxspeed 40}
		{StartTime 0.1}
		{TurnStart 0.2}
		{TurnTime 0.5}
		}
		{disableBackward}
	}
	{extender "inventory"
		{box
			{Size 6 10}
			{weight 300}
			
		}
	}

;	{Weaponry
;		{place "gun"
;			{rotate}
;			{gunner "driver"}
;			{charger "driver"}
;		}
;	}
	{sensor
		{visor "main"
    		{vision
			{h_fov 270}
  			{v_fov 180}
			{uncover 10}
			{radius 50}
    		}
			{bone "head"}
		}
    }
 	{volume "body"
		{able {blast} {bullet} {contact}}
		{thickness 5}
	}
	{extender "vitality"
		{Health {max 500} {current 500} {inc 1}}
	}
	