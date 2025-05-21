(define "spawner_contacter"
		{physics_work 0}
					{spawn "%e"}
		{delay 0.1	{spawn "%e"}}
		{delay 0.5	{spawn "%e"}}
		{delay 1	{spawn "%e"}}
		{delay 2	{spawn "%e"}}
		{delay 3	{spawn "%e"}}
		{delay 4	{spawn "%e"}}
		{delay 5	{spawn "%e"}}
		{delay 6	{spawn "%e"}}
		{delay 8	{spawn "%e"}}
		{delay 9	{spawn "%e"}{delete}}
)

(define "throwing_weapon"
	{on contact
		{if effector "human"
			{delay 0
				{constrain_velocity 1}
			}
		}
	}
)

(define "basic_part_contact_optimaiz"
	else effector "knife"
		{if not %did {start_sound "human/metall_on_flesh/"}}	;звук удара ножем
		("health_damage_clear" c(50))
	else
)

(define "health_damage_clear"
	{health_damage_count %c	{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}}
)

{"knife" 
	{on contact
		{if effector "human"
			{delay 0
				{constrain_velocity 1}
			}
		}
	}
}

{"prop_not_physics"
	{on spawn
		{physics_work 0}
		{volumes enable contact}
	}
}

{"melee_activator"
	{on spawn
		{if not tagged "detonate"
			{tags add "detonate"}
			{stuff_detonate}
		}
	}
}

{"melee_adaptive"		
	{on spawn
		{volumes "blade" disable contact}
		{volumes "blade" enable blast}
	}
	{on blast_hit
		{if stuff "melee_activator_03"
			{call "melee_on"}
			{volumes "blade" enable contact}
			{delay 0.3 {volumes "blade" disable contact}{call "melee_off"}}
		}
	}
}

{"stuff"
	{on spawn
		{if tagged "debag_stop"
			{delete}
		}
	}
	{on "crush_container"
		{impulse dir 2 1 up 2 1 rnd_dir 2 1 cx 0 1 cy 0 1}
		{delay 0.3	{call "debag_fall"}}{delay 4 {call "debag_stop"}}
	}
	{on "drop_item"
		{impulse dir 2 1 cx 0 1 cy 0 1}
		{delay 0.3	{call "debag_fall"}}{delay 3 {call "debag_stop"}}
	}
	{on blast_hit
		{if not linked
			{call "blast_physics"}
		}
	}
	{on "debag_fall"
		{if not altitude 0.4
		else not velocity 0
			{impulse up -0.5 0.2 dir 0.2 rnd_dir 0.1}
		}
		{delay 0.2 {if tagged "debag_stop" else altitude 0.4 {call "debag_fall"} else {call "debag_stop"}}}
		{tags add "chek"}{delay 0.3 {tags remove "chek"}} 
	}
	{on "debag_stop"
		{if altitude 0.8
			{impulse up -0.5 0.2 dir 0.2 rnd_dir 0.1}
			{delay 0.5	{if altitude 0.8 {impulse up -0.5 0.2 dir 0.2 rnd_dir 0.1}}}
			{tags add "debag_stop"}{delay 1 {tags remove "debag_stop"}} 
		else
			{tags add "debag_stop"}{delay 1 {tags remove "debag_stop"}} 
		}
	}
	{on ground_hit
		{call "debag_stop"}
	}
	{on contact
		{if effector "prop_not_physics"
			{physics_work 0}
			{delay 0.1
				{physics_work 1}
				{impulse up -0.01 dir 0.01}
			}
		else
		{tags add "qq1"}
		}
	}
	{on bullet_hit
		{if not linked
			{impulse up 0.4 0.2 dir 1 0.5}
		}
	}
	{on "blast_physics"
		{if min_energy 0.3
			{impulse up 4 1 dir 5 2 rnd_dir 2 1 cx 0 1 cy 0 1}
		}
		{delay 0.3	{call "debag_fall"}}{delay 3 {call "debag_stop"}}
	}
}