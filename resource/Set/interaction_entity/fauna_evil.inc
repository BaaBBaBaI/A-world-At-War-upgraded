{"animal_evil" ; redatto il giorno 20 07 2015
	{inflammation_time 0.35}
	{on spawn
		{link_sound "pascolo" "fauna/horse/eat"}
		{link_sound "brontolio" "fauna/horse/grunt"}
		{link_sound "sbruffo" "fauna/horse/snurf"}
		{link_sound "zoccolo" "fauna/horse/toe"}
		{link_sound "briglie" "fauna/horse/bridle"}
		{link_sound "galoppo" "fauna/horse/run"}
		{link_sound "affanno" "fauna/horse/noise"}
		{link_sound "trotto" "fauna/horse/walk2"}
		{link_sound "passo" "fauna/horse/walk"}
		{link_sound "nitrito" "fauna/horse/winny"}
		{link_sound "traino" "fauna/horse/trail"}
		{link_sound "sparo" "fauna/horse/shoot"}
		{link_sound "ferita" "fauna/horse/hit"}
		{link_sound "tromba_carica" "fauna/horse/charge"}
		{link_sound "morte" "fauna/horse/death"}
		
		{add_view	"healing" "healing" "head"}
		
		{call "idle"}
	}
	{on move on
		{call "stop_idle"}
	{if stuff "tromba"
		{play_sound "tromba_carica" 1}
		}
		{if not "blocked"
			{ani_play "run" 2.5 loop}
			{play_sound "galoppo" 1}
		}
	}
	{on move off
		{ani_stop "run"}
		{stop_sound "galoppo"}
		{stop_sound "tromba_carica"}
		{call "idle"}
	}
	{on turn on
		{call "stop_idle"}
		{if not "blocked"
			{ani_play "walk" 1.0 loop}
		}
	}
	{on turn off
		{ani_stop "walk"}
		{call "idle"}
	}
	{on "idle"
		{if dead
			{delete}
		}
		{set "idle" 1}
		{if not "blocked"
			{if rand 0.95
				{play_sound "brontolio"}
				{play_sound "zoccolo"}
				{play_sound "briglie"}
				{ani_play "passive" 0.5 callback} ; batte zoccolo
			else
				{play_sound "brontolio"}
				{play_sound "zoccolo"}
				{play_sound "briglie"}
				{ani_play "passive2" 0.5 callback} ; scuote testa dx - sx
				
			}
		}
	}
	{on "safe-idle"
		{if "idle"
			{call "idle"}
		}
	}
	{on "start-idle"
		{set "idle" 1}
		{delay_effect 1 "safe-idle"}
	}
	{on animation_end "passive"
		{delay_effect 20 1.5 "safe-idle"}
	}
	{on animation_end "passive2"
		{delay_effect 20 1.5 "safe-idle"}
	}
	{on "stop_idle"
		{set "idle" 0}
		{ani_stop "passive"}
		{ani_stop "passive2"}
		{stop_sound "brontolio"}
		{stop_sound "zoccolo"}
		{stop_sound "briglie"}
		{play_sound "nitrito"}
	}
	

	{on fire "gun"
		{set "blocked" 1}
		{call "stop_idle"}
		{ani_stop "walk"}
		{ani_stop "run"}
		{ani_play "attack" callback}
	}

	{on animation_end "attack"
		{set "blocked" 0}
		{call "start-idle"}
	}

	{on ik begin "foresight3"
		{call "stop_idle"}
	}
	{on contact 
		{if effector "vehicle"
			{if effector_velocity 0.1
				{health_damage_crush "die" "explosion"}
			}
		else effector "knife"
			{if contact_velocity 5
				{health_damage_count 110 {effects "" "hit" "damage" "die" "die"}}
			}
		else effector "axe"
			{if contact_velocity 5
				{health_damage_count 180 {effects "" "hit" "damage" "die" "die"}}
			}
		else effector "big part"
			{if contact_velocity 3
				{health_damage_count 60 {effects "" "hit" "damage" "die" "crush"}}
			}
		else effector "medium part"
			{if contact_velocity 6
				{health_damage_count 40 {effects "" "hit" "damage" "die" "crush"}}
			}
		else effector "small part"
			{if contact_velocity 10
				{health_damage_count 20 {effects "" "hit" "damage" "die" "die"}}
			}
else effector "wire"
				{health_damage_count 20
					{effects "" "hit" "damage" "die" "die"}
				}
			else effector "flame_piece"
				{health_damage_count (mod "mp" 15) (mod not "mp" 15)
					{effects "" "hit" "hit" "die" "die"}
				}
		}
	}
{on "throw_high"
		{if senseless
			{if not dead
				{if not user_control
					{call "die"}
				}
			}
		else
			{if not dead
				{if linked "vehicle"
					{if "die_after_throw"
						{throw_off up 1.3 0.5 dir 5.5 2 forward 4 turn 0 360 die force}
					else
						{throw_off up 1.3 0.5 dir 5.5 2 forward 4 turn 0 360 force}
					}
				else
					{if "die_after_throw"
						{throw_off up 4 0.8 dir 3.5 0.5 forward 0 0 die}
					else
						{throw_off up 4 0.8 dir 3.5 0.5 forward 0 0}
					}
				}
			else
				{call "explosion"}
			}
		}
	}
	{on "throw_off_end"
		{if not user_control
			{health_damage_count 50
				{effects "" "hit" "damage" "die" "die"}
			}
		}
		{call "knock_down"}
	}
	{on "throw_off_end_die"
		{call "die"}
	}
	
	{on blast
		{health_damage_blast
			{effects "" "" "damage" "die" "explosion" "explosion" "explosion"}
		}
	}
	{on blow opponent
		{health_damage_blow
			{effects "hit" "hit" "die" "die" "explosion" "explosion" "explosion"}
		}
		{call "damage"}
	}
	{on bullet_hit
		{call "pierce_damage"}
	}
	{on "pierce_damage"
		{health_damage_pierce
			{effects "" "" "damage" "die" "explosion" "explosion" "explosion"}
		}
	}
	{on "damage-low"
		{spawn "bloodsparks_small"}
	}
	{on "damage"
		{spawn "bloodsparks_small"}
	}
	
	{on "leave_unit"
		{if work "body"
			{if not tagged "abandoned"
				{unlink_trailer}
				{reset_manual_control}
				{if not tagged "emit_label"		
					{damage_report "body" "component/leave_unit"}
					{tags add "emit_label"}
					{crew_emit}
				}
				{delay 1		
					{crew_emit}
				}
				{delay 2		
					{crew_emit}
				}
				{delay 3		
					{crew_emit}
				}
				{delay 4	{if operatable {tags remove "emit_label"}}}
				{delay 6	{if operatable {tags remove "emit_label"}}}
				{delay 8	{if operatable {tags remove "emit_label"}}}
				{delay 10	{if operatable {tags remove "emit_label"}}}
				{delay 12	{if operatable {tags remove "emit_label"}}}
				{delay 14	{if operatable {tags remove "emit_label"}}}
				{delay 15
					{if not operatable
						{tags add "abandoned"}
						{set "broken" 1}
						{able select 0}
						{able repaired 0}
						{explosive 1}
						{player -1}
						{stat_notify leave}
						{kick_entity_manager}
						{explosive 1}
						{damage_report "body" "component/empty"}
						{delay 3 1					
							{explosive 0}
							{tags add "destroyed"}
							{call "delete"}
						}
					}
				}			
			}
		}
	}
	{on "die"
		{if not dead
		{ani_play "death"}
		{start_sound "fauna/horse/death"}
		}
		{volumes disable contact}
		{kill_crew}
		{die}
		{delay 3
			{volumes enable contact}
			{update_visibility_patch}
		}
		{delay 15
			{if dead {delete}
		}
}
}
	{on "explosion"
		;{call "die"}
		{delete}
	}
;{on "delete"
;		{delete}
;	}
;
}

{"horse_bugler" ; redatto il giorno 14 04 2015
	
	{on move on
		{call "stop_idle"}
		{if not "blocked"
			{ani_play "run" 2.5 loop}
			{play_sound "galoppo" 1}
			{play_sound "tromba_carica" 1}
		}
	}
	{on move off
		{ani_stop "run"}
		{stop_sound "galoppo"}
		{stop_sound "tromba_carica"}
		{call "idle"}
	}
}

{"horse_2cv" ; redatto il giorno 14 04 2015
	
	{on move on
		{call "stop_idle"}
		{if not "blocked"
			{ani_play "run" 2.5 loop}
			{stop_sound "galoppo"}
			{play_sound "passo" 1}
			
		}
	}
	{on move off
		{ani_stop "run"}
		{stop_sound "passo"}
		
		{call "idle"}
	}
}

{"horse_4cv" ; redatto il giorno 14 04 2015
	
	{on move on
		{call "stop_idle"}
		{if not "blocked"
			{ani_play "run" 2.5 loop}
			{stop_sound "galoppo"}
			{play_sound "passo" 1}
			
		}
	}
	{on move off
		{ani_stop "run"}
		{stop_sound "passo"}
		
		{call "idle"}
	}
}
{"horse_double" ; redatto il giorno 14 04 2015
	
	{on move on
		{call "stop_idle"}
		{if not "blocked"
			{ani_play "run" 2.5 loop}
			{stop_sound "galoppo"}
			{play_sound "passo" 1}
			
		}
	}
	{on move off
		{ani_stop "run"}
		{stop_sound "passo"}
		
		{call "idle"}
	}
}