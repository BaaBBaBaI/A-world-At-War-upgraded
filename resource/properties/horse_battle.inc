	(define "stuff_view"
		;{con "horse_stuff_view"}
		{add_view "%item" "stuff_view_%item" "%bone"}
		{view show "stuff_view_%item"}
		{view start "stuff_view_%item"}
		{bone hide "gun_back"}
	)	
	(define "stuff_view_arrow"
		{add_view "%item" "stuff_view" "%bone"}
		{view show "stuff_view_arrow"}
		{view start "stuff_view_arrow"}
		{bone hide "gun_back"}
	)
	
	(define "stuff_view_off_h"
		{view pause "stuff_view"}
		{view hide "stuff_view"}
		{view stop "stuff_view"}
		{view pause "stuff_view_arrow"}
		{view hide "stuff_view_arrow"}
		{view stop "stuff_view_arrow"}
		{bone show "gun_back"}
	)
	(define "stuff_view_arrow_off"
		{view pause "stuff_view_arrow"}
		{view hide "stuff_view_arrow"}
		{view stop "stuff_view_arrow"}
	)
	(define "gun_horseman_stuff"
			{on %event
			{if not operatable
			else
				{if crew_in_place "driver"
					{call "stuff_view_off"}
					{call "stuff_view_all_off"}
					{with_linked_entity "driver"	
						{delay 0.05 
							("stuff_view" item(%item) bone(right_hand))
						}
					}
				}
			}
			}
	) 	
	(define "gun_horseman_stuff_bow"
			{on %event
			{if not operatable
			else
				{if crew_in_place "driver"
					{with_linked_entity "driver"	
						{delay 0.05
							("stuff_view_arrow" item(bow_arrow) bone(right_hand))
							("stuff_view" item(%item) bone(left_hand))
						}
					}
				}
			}
			}
	) 	
	(define "horseman_stuff_pistol_view"
		{"%name"
			("gun_horseman_stuff" item(%item) event(operatable on))
			("gun_horseman_stuff" item(%item) event(crew in))
		
		}
	)
	(define "horseman_stuff_view"
		{"%name"
			{on spawn
				{if not operatable
					("stuff_view" item(%item) bone(rifle))
				else
					{call "stuff_view_off"}
					{call "stuff_view_all_off"}
				}
			}
			{on operatable off
					("stuff_view" item(%item) bone(rifle))
			}
			("gun_horseman_stuff" item(%item) event(operatable on))
			("gun_horseman_stuff" item(%item) event(crew in))
		
		}
	)
	(define "horseman_stuff_bow_view"
		{"%name"
		("gun_horseman_stuff_bow" item(%item) event(operatable on))
		("gun_horseman_stuff_bow" item(%item) event(crew in))
		}
	)
	(define "gun_horseman_stuff_bow"
			{on %event
				{if not operatable
				else
					{if crew_in_place "driver"
						{with_linked_entity "driver"	
							{delay 0.05 
								("stuff_view_arrow" item(bow_arrow) bone(right_hand))
								("stuff_view" item(%item) bone(left_hand))
							}
						}
					}
				}
			}
	) 	
	(define "horseman_stuff_pistol_view"
		{"%name"
			("gun_horseman_stuff" item(%item) event(operatable on))
			("gun_horseman_stuff" item(%item) event(crew in))
		}
	)
	(define "horseman_stuff_view"
		{"%name"
			{on spawn
				{if not operatable
					("stuff_view" item(%item) bone(rifle))
				else
					{call "stuff_view_off"}	
				}
			}
			{on operatable off
					("stuff_view" item(%item) bone(rifle))
			}
			("gun_horseman_stuff" item(%item) event(operatable on))
			("gun_horseman_stuff" item(%item) event(crew in))
		}
	)
	(define "horseman_stuff_bow_view"
		{"%name"
			("gun_horseman_stuff_bow" item(%item) event(operatable on))
			("gun_horseman_stuff_bow" item(%item) event(crew in))
			{on "bow_off"
				{with_linked_entity "driver"	
					{call "stuff_view_off"}
				{call "stuff_view_all_off"}
				}
			}
			{on "bow_on"
				{with_linked_entity "driver"	
					("stuff_view" item(%item) bone(left_hand))
					("stuff_view_arrow" item(bow_arrow) bone(right_hand))
				}
			}
		}
	)
;======main preset weapon type
(define "gun_horseman_anima"
{"%name"
	{on operatable on
		{if not operatable
		else
			{if crew_in_place "driver"
				{with_linked_entity "driver"	
					{delay 0.1 
						{ani_play "%take" 0.5}
						{add_view "%flash" "flashbarrel_horse" "right_hand"}
					}
				}
			}
		}
	}
	{on fire "gun"
		{with_linked_entity "driver"	
				{if rand 0.13 
					{talk "in_action"}
				}
			;{spawn "%flash" "right_hand" x}
			{view show	"flashbarrel_horse"}
			{view start	"flashbarrel_horse"}
			;{con "horse_spawn_flash"}
			{ani_play "%aim"}
			{delay 0.5 {ani_play "%reload" %rs}}
		}
		{movement_limit slow}
		{weapon_work "gun" 0}
		{ik_enable "ik_right" 0}
		{ik_enable "ik_left" 0}
		{ik_enable "ik_centr" 0}
		{delay %rt
			{weapon_work "gun" 1}
			{ik_enable "ik_right" 1}
			{ik_enable "ik_left" 1}
			{ik_enable "ik_centr" 1}
			{movement_limit fast}
		}
	}
	{on ik begin "ik_centr"
		{with_linked_entity "driver"	
			{if not dead 
			{ani_stop "%aim_right"}
			{ani_stop "%aim_left"}
			{ani_play "%aim"}
			}
		}
	}
	{on ik begin "ik_right"
		;{if rand 0.2
			{with_linked_entity "driver"	
				{if not dead
				{ani_stop "%aim"}
				{ani_stop "%aim_left"}
					{ani_play "%aim_right" 0.5}
				}
			}
		;}
	}
	{on ik begin "ik_left"
		;{if rand 0.2
			{with_linked_entity "driver"	
				{if not dead
				{ani_stop "%aim"}
				{ani_stop "%aim_right"}
				{ani_play "%aim_left" 0.5}
				}
			}
		;}
	}
	{on "anima_move_update"
		{if not tagged "dead"
			{if not tagged "melee"
			{if tagged "move"
				{if velocity 26 ; > 26 km/h
					{with_linked_entity "driver"	
						{if rand 0.5
							{if not dead {ani_play "%move_fast" 0.5}}
							else
							{if not dead {ani_play "%move_fast1" 0.5}}
						}
					}
					else velocity 12 ; > 12 km/h
					{with_linked_entity "driver"	
						{if not dead {ani_play "%move" 0.5}}
					}
					else velocity 0 ; > 0  km/h
					{with_linked_entity "driver"	
						{if not dead {ani_play "%move" 0.5}}
					}
				}
			}
			}
		}
	}
}
)
(define "gun_horseman_bow_anima"
{"%name"
	{on operatable on
		{if not operatable
		else
			{if crew_in_place "driver"
				{with_linked_entity "driver"	
					{delay 0.1 
						{ani_play "%take" 0.5}
					}
				}
			}
		}
	}
	{on fire "gun"
		{with_linked_entity "driver"		
				{if rand 0.13 
					{talk "in_action"}
				}
			{ani_play "%aim"}
			{view pause "stuff_view_arrow"}
			{view hide "stuff_view_arrow"}
			{view stop "stuff_view_arrow"}
			{delay 0.8 
				{ani_play "%reload" %rs}
				{view show "stuff_view_arrow"}
				{view start "stuff_view_arrow"}
			}
		}
		{movement_limit slow}
		{weapon_work "gun" 0}
		{ik_enable "ik_right" 0}
		{ik_enable "ik_left" 0}
		{ik_enable "ik_centr" 0}
		{delay %rt
			{weapon_work "gun" 1}
			{ik_enable "ik_right" 1}
			{ik_enable "ik_left" 1}
			{ik_enable "ik_centr" 1}
			{movement_limit fast}
		}
	}
	{on ik begin "ik_centr"
		{ani_stop "%aim_right"}
		{ani_stop "%aim_left"}
		{with_linked_entity "driver"	
			{if not dead {ani_play "%aim"}}
		}
	}
	{on ik begin "ik_right"
		{ani_stop "%aim"}
		{ani_stop "%aim_left"}
		{with_linked_entity "driver"	
			{if not dead {ani_play "%aim_right" 0.5}}
		}
	}
	{on ik begin "ik_left"
		{ani_stop "%aim"}
		{ani_stop "%aim_right"}
		{with_linked_entity "driver"	
			{if not dead {ani_play "%aim_left" 0.5}}
		}
	}
	{on "anima_move_update"
		{if not tagged "dead"
			{if tagged "move"
				{if velocity 26 ; > 26 km/h
					{with_linked_entity "driver"	
						{if rand 0.5
							{if not dead {ani_play "%move_fast" 0.5}}
							else
							{if not dead {ani_play "%move_fast1" 0.5}}
						}
					}
					else velocity 12 ; > 12 km/h
					{with_linked_entity "driver"	
						{if not dead {ani_play "%move" 0.5}}
					}
					else velocity 0 ; > 0  km/h
					{with_linked_entity "driver"	
						{if not dead {ani_play "%move" 0.5}}
					}
				}	
			}
		}
	}
}
)
(define "gun_horseman_melee_anima"
{"%name"
	{on operatable on
		{if not operatable
		else
			{if crew_in_place "driver"
				{with_linked_entity "driver"	
					{delay 0.1 
						{ani_play "%take" 0.5}
					}
				}
			}
		}
	}
		{on fire "sword_front"
			{with_linked_entity "driver"		
					{if rand 0.13 
						{talk "in_action"}
					}
				{if rand 0.25
					{if not dead {ani_play "%attack_front" %rs}}
					else rand 0.25
					{if not dead {ani_play "%attack_front3" %rs}}
					else rand 0.25
					{if not dead {ani_play "%attack_front4" %rs}}
					else
					{if not dead {ani_play "%attack_front2" %rs}}
				}
			}
			{weapon_work "sword_front" 0}
			{weapon_work "sword_left" 0}
			{weapon_work "sword_right" 0}
			{delay %rt
				{weapon_work "sword_front" 1}
				{weapon_work "sword_left" 1}
				{weapon_work "sword_right" 1}
			}
		}
		{on fire "sword_left"
			{with_linked_entity "driver"		
					{if rand 0.13 
						{talk "in_action"}
					}
				{if rand 0.25
					{if not dead {ani_play "%attack_left" %rs}}
					else rand 0.25
					{if not dead {ani_play "%attack_left3" %rs}}
					else rand 0.25
					{if not dead {ani_play "%attack_left4" %rs}}
					else
					{if not dead {ani_play "%attack_left2" %rs}}
				}
			}
			{weapon_work "sword_front" 0}
			{weapon_work "sword_left" 0}
			{weapon_work "sword_right" 0}
			{delay %rt
				{weapon_work "sword_front" 1}
				{weapon_work "sword_left" 1}
				{weapon_work "sword_right" 1}
			}
		}
		{on fire "sword_right"
			{with_linked_entity "driver"		
					{if rand 0.13 
						{talk "in_action"}
					}
				{if rand 0.25
					{if not dead {ani_play "%attack_right" %rs}}
					else rand 0.25
					{if not dead {ani_play "%attack_right3" %rs}}
					else rand 0.25
					{if not dead {ani_play "%attack_right4" %rs}}
					else
					{if not dead {ani_play "%attack_right2" %rs}}
				}
			}
			{weapon_work "sword_front" 0}
			{weapon_work "sword_left" 0}
			{weapon_work "sword_right" 0}
			{delay %rt
				{weapon_work "sword_front" 1}
				{weapon_work "sword_left" 1}
				{weapon_work "sword_right" 1}
			}
		}
	
	{on "anima_move_update"
		{if not tagged "dead"
			{if tagged "move"
				{if velocity 26 ; > 26 km/h
					{with_linked_entity "driver"	
						{if rand 0.5
							{if not dead {ani_play "%move_fast" 0.5}}
							else
							{if not dead {ani_play "%move_fast1" 0.5}}
						}
					}
					else velocity 12 ; > 12 km/h
					{with_linked_entity "driver"	
						{if not dead {ani_play "%move" 0.5}}
					}
					else velocity 0 ; > 0  km/h
					{with_linked_entity "driver"	
						{if not dead {ani_play "%move" 0.5}}
					}
				}	
			}
		}
	}
}
)
;===================================================================пресет для пик
	("gun_horseman_melee_anima"
		name(horse_weapon_melee_pike)
		;====anima
		rt(1.2) rs(0.5) ;reload time\ anima reload speed
		take(horse_driver_take_pike)
		attack_front(horse_driver_pike_attack_front) attack_front2(horse_driver_pike_attack_front2) attack_front3(horse_driver_pike_attack_front3) attack_front4(horse_driver_pike_attack_front4)
		attack_left(horse_driver_pike_attack_left) attack_left2(horse_driver_pike_attack_left2) attack_left3(horse_driver_pike_attack_left3) attack_left4(horse_driver_pike_attack_left4)
		attack_right(horse_driver_pike_attack_right) attack_right2(horse_driver_pike_attack_right2) attack_right3(horse_driver_pike_attack_right3) attack_right4(horse_driver_pike_attack_right4)
		move(horse_driver_pike) move_fast(horse_driver_pike) move_fast1(horse_driver_pike_fast)
		;========================
	)
;===================================================================пресет для мечей
	("gun_horseman_melee_anima"
		name(horse_weapon_melee_1hand)
		;====anima
		rt(0.8) rs(0.53) ;reload time\ anima reload speed
		take(horse_driver_take_sword)
		attack_front(horse_driver_sword_attack_front) attack_front2(horse_driver_sword_attack_front2) attack_front3(horse_driver_sword_attack_front3) attack_front4(horse_driver_sword_attack_front4)
		attack_left(horse_driver_sword_attack_left) attack_left2(horse_driver_sword_attack_left2) attack_left3(horse_driver_sword_attack_left3) attack_left4(horse_driver_sword_attack_left4)
		attack_right(horse_driver_sword_attack_right) attack_right2(horse_driver_sword_attack_right2) attack_right3(horse_driver_sword_attack_right3) attack_right4(horse_driver_sword_attack_right4)
		move(horse_driver_sword) move_fast(horse_driver_sword) move_fast1(horse_driver_sword_fast)
		;========================
	)
;===================================================================пресет для пистолетов
	("gun_horseman_anima"
		name(horse_weapon_pistol_muzz)
		;flash(flash_gun_pistol_horse)
		flash(flash_gun_pistol)	
		;====anima
			rt(4.5) rs(0.5) ;reload time\ anima reload speed
			take(horse_driver_take_pistol)
			aim(horse_driver_pistol_aim)	aim_right(horse_driver_pistol_aim_right)	aim_left(horse_driver_pistol_aim_left)	
			reload(stand_reload_pistol) move(horse_driver_pistol) move_fast(horse_driver_pistol_fast) move_fast1(horse_driver_pistol_fast1)
		;========================
	)
;===================================================================пресет для револьверов
	("gun_horseman_anima"
		name(horse_weapon_pistol_rev)
		;flash(flash_gun_pistol_horse)	
		flash(flash_gun_small)	
		;====anima
			rt(0.3) rs(0.5) ;reload time\ anima reload speed
			take(horse_driver_take_pistol)
			aim(horse_driver_pistol_aim)	aim_right(horse_driver_pistol_aim_right)	aim_left(horse_driver_pistol_aim_left)	
			reload(stand_reload_pistol) move(horse_driver_pistol) move_fast(horse_driver_pistol_fast) move_fast1(horse_driver_pistol_fast1)
		;========================
	)
;===================================================================пресет для мушкетов
	("gun_horseman_anima"
		name(horse_weapon_rifle_muzz)
		;flash(flash_gun_rifle_horse)	
		flash(flash_gun_small)
		;====anima
			rt(12) rs(1.0) ;reload time\ anima reload speed
			take(horse_driver_take_rifle)
			aim(horse_driver_aim)	aim_right(horse_driver_aim_right)	aim_left(horse_driver_aim_left)	
			reload(squat_reload_gun_mz) move(horse_driver_new) move_fast(horse_driver_new_fast) move_fast1(horse_driver_new_fast1)
		;========================
	)
;===================================================================пресет для винтовок
	("gun_horseman_anima"
		name(horse_weapon_rifle_breec)
		;flash(flash_gun_rifle_1_horse)
		flash(flash_gun_small)		
		;====anima
			rt(0.35) rs(0.55) ;reload time\ anima reload speed
			take(horse_driver_take_rifle)
			aim(horse_driver_aim)	aim_right(horse_driver_aim_right)	aim_left(horse_driver_aim_left)	
			reload(stand_reload_gun) move(horse_driver_new) move_fast(horse_driver_new_fast) move_fast1(horse_driver_new_fast1)
		;========================
	)
;===================================================================пресет для луков
	("gun_horseman_bow_anima"
		name(horse_weapon_bow)
		;====anima
			rt(3) rs(0.5) ;reload time\ anima reload speed
			take(horse_driver_take_bow)
			aim(horse_driver_bow_aim)	aim_right(horse_driver_bow_aim_right)	aim_left(horse_driver_bow_aim_left)	
			reload(horse_driver_bow_reload) move(horse_driver_bow) move_fast(horse_driver_bow_fast) move_fast1(horse_driver_bow_fast1)
		;========================
	)
;=========================|MELEE
("horseman_stuff_view"	 	name(hb_meele_naginata) 		item(cav_melee_naginata)) ; 
("horseman_stuff_view"	 	name(hb_meele_yari) 			item(cav_melee_yari)) ; 
("horseman_stuff_view"	 	name(hb_meele_pike) 			item(cav_melee_pike)) ; 
("horseman_stuff_view"		 name(hb_meele_tom) 			item(cav_melee_tom)) ; 
("horseman_stuff_view"		 name(hb_meele_sw_eur) 			item(cav_sword_eur)) ; 
("horseman_stuff_view"		 name(hb_meele_sw_eur_g) 		item(cav_sword_eur_guard)) ; 
("horseman_stuff_view"		 name(hb_meele_sw_east) 		item(cav_sword_east)) ; 
("horseman_stuff_view"		 name(hb_meele_sw_jap) 			item(cav_sword_jap)) ; 

;=========================|PISTOL
("horseman_stuff_pistol_view" name(hb_p_1760) 		 item(pistol_1770)) ; 
("horseman_stuff_pistol_view" name(hb_p_colt1873) 	 item(colt_1873_cav)) ; 
("horseman_stuff_pistol_view" name(hb_p_colt_drag) 	 item(colt_dragoon_1848)) ; 
("horseman_stuff_pistol_view" name(hb_p_colt_pet) 	 item(colt_paterson_1836)) ; 
("horseman_stuff_pistol_view" name(hb_p_colt_walk) 	 item(colt_walker_butt) 	) ; 
("horseman_stuff_pistol_view" name(hb_p_lefau) 		 item(lefaucheux_m1858) 	) ; 
("horseman_stuff_pistol_view" name(hb_p_starr) 		 item(starr) 			) ; 
("horseman_stuff_pistol_view" name(hb_p_nagant)      item(nagan) 	) ; 
("horseman_stuff_pistol_view" name(hb_p_с98)      item(с98) 	) ;
("horseman_stuff_pistol_view" name(hb_p_webl) 		 item(webley_1868_ric) 	) ; 

;=========================|MUSKET& RIFLE
("horseman_stuff_view" name(hb_r_1760_eng)  item(brown_bess_1722_carabin)) ; ENG CONT IRO
("horseman_stuff_view" name(hb_r_1760_fra)  item(charleville_m1774_carabin)) ; FRA
("horseman_stuff_view" name(hb_r_1760_ger)  item(potzdam_1723_carabin) ) ; AUS PRU HES SWE
("horseman_stuff_view" name(hb_r_1760_rus)  item(m1752_musket_carabin) ) ; RUS GRE SPA TURK POL
("horseman_stuff_view" name(hb_r_1812_fra)  item(an-ix_musket_short) 	) ; FRA AUS DEN ITA SWISS
("horseman_stuff_view" name(hb_r_1812_eng)  item(1800_baker_carabin) 	) ; ENG PRU SPA
("horseman_stuff_view" name(hb_r_1812_rus)  item(m1752_musket_carabin) ) ;RUS TUR 
("horseman_stuff_view" name(hb_r_1812_usa)  item(springfild_1812_carabin)) ; USA
("horseman_stuff_view" name(hb_r_berd1870)  item(berdan_1870_car) 		) ; 
("horseman_stuff_view" name(hb_r_bernside)  item(bernsayd) 				) ; 
("horseman_stuff_view" name(hb_r_chassepot)  item(chassepot_1866_short) 	) ; 
("horseman_stuff_view" name(hb_r_colt1873)  item(colt_carabin_1973) 		) ; 
("horseman_stuff_view" name(hb_r_dreyse)  item(dreyse_1860_short) 		) ; 
("horseman_stuff_view" name(hb_r_henry)  item(henry_army) 				) ; 
("horseman_stuff_view" name(hb_r_martin)  item(martini_henry_1871_car) 	) ; 
("horseman_stuff_view" name(hb_r_mosin)  item(mosin_dragun) 	) ;
("horseman_stuff_view" name(hb_r_mauz_1871)  item(m1871_mauser_car) 		) ; 
("horseman_stuff_view" name(hb_r_peabody)  item(peabody_1862_short) 		) ; 
("horseman_stuff_view" name(hb_r_remingt)  item(remington_roll_rifle_1867_carabin) ) ; 
("horseman_stuff_view" name(hb_r_sharps)  item(sharps_carabin) 			) ; 
("horseman_stuff_view" name(hb_r_snider)  item(enfield_snider_rifle) 		) ; 
("horseman_stuff_view" name(hb_r_spencer)  item(spenser_carabin) 			) ; 
("horseman_stuff_view" name(hb_r_spr1873)  item(springfild_1873_carabin) 	) ; 
("horseman_stuff_view" name(hb_rtabaq)  item(tabatiere_rifle) 			) ; 
("horseman_stuff_view" name(hb_r_wanz1867)  item(m1867_wanzel_rifle_car)) ; 
("horseman_stuff_view" name(hb_r_wrndl1867)  item(m1867_werndl_car) ) ; 
("horseman_stuff_view" name(hb_r_enf1853)  item(enfild_1853_carabin) 		) ; 
("horseman_stuff_view" name(hb_r_kent)  item(kentucky_rifle_short) 		) ; 
("horseman_stuff_view" name(hb_r_lor_1862)  item(m1862_lorenz_rifle_car) 	) ; 
("horseman_stuff_view" name(hb_r_m1845)  item(m1845_rifle_carabin) 		) ; 
("horseman_stuff_view" name(hb_r_m1851)  item(m1851_rifle_carabin) 		) ; 
("horseman_stuff_view" name(hb_r_richm)  item(richmond_1861_carabin) 		) ; 
("horseman_stuff_view" name(hb_r_spr1816)  item(springfild_1816_carabin) 	) ; 
("horseman_stuff_view" name(hb_r_spr1842)  item(springfild_1842_carabin) 	) ; 
("horseman_stuff_view" name(hb_r_spr1861)  item(springfild_1861_carabin) 	) ; 

;=============BOWS
("horseman_stuff_bow_view" 	name(hb_bow_light) 	 item(light_bow_view) 			) ; 
("horseman_stuff_bow_view" 	name(hb_bow_med) 	 item(med_bow_view) 				) ; 
("horseman_stuff_bow_view" 	name(hb_bow_long) 	 item(long_bow_view) 			) ; 
;===================================================================
{"horse_battle_m"
	{on spawn
		{delay 0.5
			{if difficulty "multiplayer"
				{if user_control
					{tags add "cav_melee_user"}
					else
					{tags add "cav_melee_ai"}
				}
				{delay 4 {tags add "cav_melee"}}
			}
		}
	}
}
{"horse_battle_mp"
	;{on operatable on
	;	{tags remove "abandoned"}
	;}
	{on operatable off
		{delay 45 {call "check_abandon"}}
	}
	{on "check_abandon"
		{if not operatable
			{delay 10 15
				{call "dead"}
			}
		}	
	}
}
{"horse_battle"
	{on spawn
		{physics_work 0}
		{call "init_gun"}
		{if tagged "dead"
			{ani_play "death" 100}
			else
			{call "idle_try"}
		}
		;{con "horse_spawn"}
		{volumes "body1" enable overlap}
		{if not rain
			{add_view	"dustrun_small_horse"	"horse_on_ground"	"joint1"}
			{add_view	"dustrun_small_horse"	"horse_on_ground"	"joint2"}
			{add_view	"dustrun_small_horse"	"horse_on_ground"	"joint3"}
			{add_view	"dustrun_small_horse"	"horse_on_ground"	"joint4"}
			{add_view	"dustrun_small_horse"	"horse_on_sand"	"joint1"}
			{add_view	"dustrun_small_horse"	"horse_on_sand"	"joint2"}
			{add_view	"dustrun_small_horse"	"horse_on_sand"	"joint3"}
			{add_view	"dustrun_small_horse"	"horse_on_sand"	"joint4"}
		}
		{add_view	"drops_puddle_small"	"horse_on_puddle"	"joint1"}
		{add_view	"drops_puddle_small"	"horse_on_puddle"	"joint2"}
		{add_view	"drops_puddle_small"	"horse_on_puddle"	"joint3"}
		{add_view	"drops_puddle_small"	"horse_on_puddle"	"joint4"}
		{link_sound "move" "vehicle/horse_move/"}
		{link_sound "idle" "vehicle/horse_idle/"}

		{if rand 0.1 {play_sound "idle"}}
	}
	;{on "reload"
	;	{tags add "reload"}
	;	{delay 3 {tags remove "reload"}}
	;}
	{on "stuff_view_off"
		("stuff_view_off_h")
	}
	{on "stuff_view_arrow_off"
		("stuff_view_arrow_off")
	}
	{on "stuff_view_all_off"
		;("stuff_view_all_off")
		("off_stuff_view_all_item")
	}
	{on operatable off
		{if velocity 15
			{call "dead"}
		}
		{if able "sinking"
			{delay 0.5 
				{call "dead"} ; !!!!!!!!!!HORSE SINKING ANIMA NEED
			}
		}
	}
	{on "check_water_level" overload
		{if water_level 1.6
			{able "sinking" 1}
		}
	}
	{on turn on overload
		{ani_stop "eat"}
		{ani_stop "passive"}
		{ani_stop "passive2"}
		{ani_stop "passive1"}
		{play_sound "move" 1}
		{tags add "turn"}
		{call "anima_move_update_turns"}
		;{con "horse_turn_on"}
	}
	{on turn off overload
		{stop_sound "move"}
		{tags remove "turn"}
		{call "anima_move_update_turns"}
		;{con "horse_turn_off"}
		{call "idle_try"}
	}
	{on accelerate on overload
		{if not tagged "dead"
			{call "anima_move_update"}
		}
	}
	{on accelerate off overload
		{if not tagged "dead"
			{call "anima_move_update"}
		}
	}
	{on move on overload 
		{ani_stop "eat"}
		{ani_stop "passive"}
		{ani_stop "passive2"}
		{ani_stop "passive1"}
		{play_sound "move" 1}
		{tags add "move"}
		{call "anima_move_update"}
		;{with_linked_entity "driver"	
		;	{ani_play "horse_driver_new"}
		;}
	}
	{on move off overload
		{stop_sound "move"}
		{tags remove "move"}
		{ani_stop "run"}
		{ani_stop "run1"}
		{ani_stop "walk"}
		{call "idle_try"}
	}
	{on "idle" overload
		{if name "exit"              
			{set "stop_anm" 1}
			{ani_stop "passive1"}
			{ani_stop "passive2"}    
			{set "stop_anm" 0}
		}
		{inherited}
	}
	{on "idle_try" overload
		;{con "fauna_idle_try"}
		{if not dead
			{if not tagged "turn"
			{if not tagged "move"
			{if not tagged "dead"	
			{if rand 0.1
				{ani_play "eat" callback}  
			else rand 0.1
				{ani_play "passive" callback}
				{if rand 0.1 {play_sound "idle"}}
			else rand 0.1
				{ani_play "passive1" callback}
				{if rand 0.1 {play_sound "idle"}}
			else
				{ani_play "passive2" callback}
			}
			}
		
		}
		}
		}
	}
	{on animation_end "eat"
		{if not "stop_anm"
			{if not tagged "turn"
			{if not tagged "dead"	
			{if not tagged "move"
			{call "idle_try"}
			}
			}
		}
		}
	}
	{on animation_end "passive"
		{if not "stop_anm"
			{if not tagged "turn"
			{if not tagged "dead"	
			{if not tagged "move"
			{call "idle_try"}
			}
			}
		}}
	}
	{on animation_end "passive1"
		{if not "stop_anm"
			{if not tagged "turn"
			{if not tagged "dead"	
			{if not tagged "move"
			{call "idle_try"}
			}
			}}
		}
	}
	{on animation_end "passive2"
		{if not "stop_anm"
			{if not tagged "turn"
			{if not tagged "dead"	
			{if not tagged "move"
			{call "idle_try"}
			}
			}}
		}
	}
	{on "anima_move_update"
		{if not tagged "dead"
			{if tagged "move"
				;{kill_delay "anima_move_update_turns"}
				;{if Move_Forward
					{if velocity 26 ; > 26 km/h
					;{play_sound "move" 1}
						{ani_stop "run1"}
						{ani_stop "walk"}
						{ani_stop "walk_left"}
						{ani_stop "walk_right"}
							{if not tagged "dead" {ani_play "run" loop}}
						else velocity 12 ; > 12 km/h
					;{play_sound "move" 1}
						{ani_stop "run"}
						{ani_stop "walk"}
						{ani_stop "walk_left"}
						{ani_stop "walk_right"}
							{if not tagged "dead" {ani_play "run1" loop}}
						else velocity 0 ; > 0  km/h
						;{play_sound "move" 1}
						{ani_stop "run"}
						{ani_stop "run1"}
						{ani_stop "walk_left"}
						{ani_stop "walk_right"}
							{if not tagged "dead" {ani_play "walk" loop}}
					}	
					{delay 1.5
						{if not tagged "dead"
							{call "anima_move_update"}
						}
					}
				;	else
				;		{ani_stop "run"}
				;		{ani_stop "run1"}
				;		{ani_stop "walk"}
				;		{ani_stop "walk_left"}
				;		{ani_stop "walk_right"}
				;		{ani_play "walk" -1 loop}
				;}
			else
				{if not tagged "move"
					{ani_stop "run"}
					{ani_stop "run1"}
					{ani_stop "walk"}
				}
				{if not tagged "turn"
					{ani_stop "walk_left"}
					{ani_stop "walk_right"}
				}
				;{stop_sound "move"}
				
				{if rand 0.1 {play_sound "idle"}}
			}
		}
	}
	{on "anima_move_update_turns"
		{if not tagged "dead"
			{if tagged "turn"
				{if Turn_Left
					;{play_sound "move" 1}
					{ani_stop "walk"}
					{ani_stop "run"}
					{ani_stop "run1"}
					{ani_stop "walk_left"}
					{ani_stop "walk_right"}
						{if not tagged "dead" {ani_play "walk_left" 1 loop}}
				else
					;{play_sound "move" 1}
					{ani_stop "run"}
					{ani_stop "run1"}
					{ani_stop "walk"}
					{ani_stop "walk_left"}
					{ani_stop "walk_right"}
						{if not tagged "dead" {ani_play "walk_right" 1 loop}}
				}	
				{delay 2.5
					{if not tagged "dead"
						{call "anima_move_update_turns"}
					}
				}
			else
				{if not tagged "move"
					{ani_stop "run"}
					{ani_stop "run1"}
					{ani_stop "walk"}
				}
				{if not tagged "turn"
					{ani_stop "walk_left"}
					{ani_stop "walk_right"}
				}
				;{stop_sound "move"}
				;{kill_delay "anima_move_update_turns"}
				{if rand 0.1 {play_sound "idle"}}
			}
		}
	}
	{inflammation_time 5}
	{on "stop_on"
		{if not tagged "dead"
		{ani_stop "start"}
		{if not tagged "dead"
			{ani_play "stop"}
		}
		{view show "stop_signal"}
		{view start "stop_signal"}
		{delay 1
			{view hide "stop_signal"}
		}
		}
	}
	{on "exhaust_on"
	}
	{on "exhaust_off"
		{stop_sound "exhaust"}
		{view pause "exhaust"}
	}
	{on brake on
	}
	{on engine on
	}
	{on engine off overload
	}
	{on "link_weapon"
	}
	{on contact overload
		;{con "horse_contact"}
		{if not tagged "dead"
			{volumes "contact_vol" disable contact}
			{delay 1.0
				{volumes "contact_vol" enable contact}
			}
			{if effector "cheval_de_frise_01"
				{if velocity 25
					{if not tagged "dead"
						{call "dead"}
					}
					{with_effector
						{call "break"}
					}
					else
					{if not tagged "dead"
						{if rand 0.9 {ani_play "horse_ride_off"}}
					}
				}
			}
			{if effector "tent"
				{if velocity 10
					{with_effector
						{call "break"}
					}
				}
			}
			{if effector "fence"
				{if velocity 15
					{if not tagged "dead"
						{if rand 0.9 {ani_play "horse_ride_off"}}
					}
					{with_effector
						{call "break"}
					}
				}
			}
			{if velocity 10
				{if effector "human"
					{if not tagged "dead" {ani_play "demage_back"}}
					{with_effector
						{if not dead
							{if rand 0.6
								{throw_off up 1.3 0.5 dir 5.5 2 forward 4 turn 0 360 die force}
								else
								{throw_off up 1.3 0.5 dir 5.5 2 forward 4 turn 0 360 force}
								{health_damage_count 60
									{effects "" "hit" "damage" "die" "die"}
								}
							}
						}
					}
				}
				else
					{volumes "contact_vol" disable contact}
					{delay 1.0
						{volumes "contact_vol" enable contact}
					}
			}
			{if effector "human"
				{if not tagged "dead" {ani_play "demage_back"}}
				{with_effector
					{if not dead
						{throw_off up 1.3 0.5 dir 5.5 2 forward 4 turn 0 360 force}
					}
				}
			}
		}
	}
	{on "damage" overload
		;{con "horse_dam"}
	}
	{on "pierce_damage" overload
		;{con "horse_pierce_dam"}
	}
	{on "grenade_stick" overload
	}
	{on "contact_airborne" overload
	}
	{on "update_moveable" overload
		;{con "horse_updt_move"}
	}
	{on "check_work_mover" overload
		;{con "horse_check move"}
	}
	{on blast_hit overload
	}
	{on "explosion" overload
	}
	{on "_explosion" overload
		{kick_entity_manager}
	}
	{on "explosion_blastwave" overload
	}
	{on "explosion_sound" overload
	}
	{on "die_with_blood" overload
		{call "dead"}

	}
	{on "die_without_blood" overload
		{call "dead"}
	}
	{on "delete_mp" 
		{delay 5
			{hide 5}
		}
	}
	
	{on "break_all" overload
		{with_linked_entity "driver"
			{call "stuff_view_off"}
		}
		{crew_throw_off up 0.5 0.5 dir 0.5 0.1 turn 0 180 forward 0.5 force}
		{call "dead"}
	}
	{on "kill_crew" overload
		{kill_crew}
	}
	{on "_burn" overload
		{call "dead"}
	}
	
	{on break overload
		{call "dead"}
	}
	{on break_armor overload
		{call "dead"}
	}
	{on break_armor_again overload
		{call "dead"}
	}
	{on "blast_body" overload
		{if min_energy 2
			{call "dead"}
		}
	}
	{on "burn_emit" overload
	}
	{on "burn_volume" overload
	
	}
	{on "stat_break" overload
			
	}
	(define "horse_scream"
			{if rand 0.55
							{start_sound "animal/horse/whin" 1}
			else rand 0.3
							{start_sound "animal/horse/gr" 1}			
			}
	)
	{on "process_bullet_hit" overload
	}
	{on bullet_hit overload
		{if stuff "melee_cav"
			{spawn "bloodsparks_slash"}
			{bullet_detonate}
		}
		{if not tagged "dead"
			{bullet_detonate}
			{if volume "body1"
				{if rand 0.50 {call "dead"}}
				else rand 0.75
				{if rand 0.25
					{if not tagged "dead"
					{if rand 0.25 {ani_play "demage_back"}}
					}
						("horse_scream")
					else rand 0.25
						{if not tagged "dead"
						{if rand 0.25 {ani_play "demage_front"}}
						}
							("horse_scream")	
					else rand 0.25
						{if not tagged "dead"
						{if rand 0.25 {ani_play "demage_right"}}
						}
							("horse_scream")		
					else rand 0.25
						{if not tagged "dead"
						{if rand 0.25 {ani_play "demage_left"}}
						}
							("horse_scream")
					else 
						{if rand 0.35
							{call "dead"}
							("horse_scream")
						}
				}
				else
					{if not tagged "dead"
					{if rand 0.25 {ani_play "horse_ride_off"}}
					}
					("horse_scream")
			}
		}
	}
	{on "hit-light" overload
		{call "die_without_blood"}
		{if not tagged "dead"
			{if rand 0.05 {knockdown 2 1}}
			{spawn "s3_blood_small"}			
			{spawn "s3_blood_tiny"}
			{if rand 0.35 {spawn "s3_blood"}}
			{if rand 0.5 {spawn "blood_small_dec"}}
			{if rand 0.25 {spawn "blood"}}
			{if rand 0.05 {spawn "bloodsparks_big"}}		
			else
				{call "dead"}
		}
	}	
	{on "hit-heavy" overload
		{if not tagged "dead"
			{call "die_without_blood"}
			{if stuff "shell ap" {if rand 0.2 {call "dead"}}
			else
				{if stuff "shell fg" {if rand 0.4 {call "dead"}}
				else
					{if stuff "ap" {if rand 0.4 {call "dead"}}
					else
						{if stuff "fg" {if rand 0.15 {call "dead"}}
						else
							{if rand 0.2 {knockdown 2 1}}
							{spawn "s3_blood_small"}			
							{spawn "s3_blood_tiny"}
							{if rand 0.75 {spawn "s3_blood"}}	
							{if rand 0.8 {spawn "blood_small_dec"}}
							{if rand 0.5 {spawn "blood"}}
							{if rand 0.5 {spawn "bloodsparks_big"}}

						}
					}
				}
			}
			else
				{if rand 0.3 {call "dead"}}	
		}
	}
	{on "die" overload
		{with_linked_entity "driver"	
			{call "in_ani_stop"}
			{call "stuff_view_off"}
			{call "stuff_view_arrow_off"}
			
		}
		{crew_throw_off up 0.3 0.2 dir 0.3 0.2 forward 0.1 rnd_die 0.5}
		{call "dead"}
	}
	{on "dead" overload
		{if not tagged "dead"
			;{con "horse_dead"}
			{tags add "dead"}  
			{drop_orders}
			{components destroy}
			{reset_manual_control}
			{able select 0}
			{player -1}
			{able repaired 0}
			{unlink_trailer}
			{clear_inventory}        
			{set "stop_anm" 1}
			{with_linked_entity "driver"	
				{call "in_ani_stop"}
				{call "stuff_view_off"}
			}
			
			{call "stuff_view_arrow_off"}
			{crew_throw_off up 0.3 0.2 dir 0.3 0.2 forward 0.1 rnd_die 0.15}     
			{call "stop_all_anm"}
			("horse_scream")
			{delay 0.1 {call "stop_all_anm"} {delay 0.5 {ani_play "death"}}}
			{start_sound "animal/horse/fall" 1}
			{crew_emit}
			{spawn "bloodsparks_small"}	
			(mod "mp"
				{delay 15
					{call "delete_mp"}
					{kick_entity_manager}
				}
			)
		}
	}
	{on "stop_all_anm"
		{ani_stop "demage_back"}	
		{ani_stop "demage_front"}	
		{ani_stop "demage_right"}	
		{ani_stop "demage_left"}	
		{ani_stop "eat"}	
		{ani_stop "passive"}		
		{ani_stop "passive1"}		
		{ani_stop "passive2"}	
		{ani_stop "run"}	
		{ani_stop "run_left"}	
		{ani_stop "run_right"}	
		{ani_stop "run1"}	
		{ani_stop "run1_left"}	
		{ani_stop "run1_right"}	
		{ani_stop "slow_walk"}	
		{ani_stop "walk"}	
		{ani_stop "walk_left"}	
		{ani_stop "walk_right"}	
		{ani_stop "horse_ride_off"}	
	}
	{on "leave_unit" overload
	}

	(define "terrain_fx_human"
		{on terrain_fx %0 enter
			{view start "horse_on_%1"}
		}
		{on terrain_fx %0 leave
			{view pause "horse_on_%1"}
		}
	)                                                             
	("terrain_fx_human" args "puddle"		puddle)
	("terrain_fx_human" args "shallow_water"	puddle)  
	("terrain_fx_human" args "ground"	ground)   
	("terrain_fx_human" args "sand"	sand)   
	
	{on "explosion_delete"
		{set "delete_parts" 1}
		{call "explosion"}
		{delay 20
			{hide 3}
		}
	}
	{on "hit-explosion"
		{call "die_without_blood"}
	}
}
;===================================colors randomize
(define "random_horse_color"
{"%name"
	{on spawn
		{if rand 0.25
			{tex_mod "%t1"}
		else rand 0.25
			{tex_mod "%t2"}
		else rand 0.22
			{tex_mod "%t4"}
		else 
			{tex_mod "%t3"}
		}
	}
}
)

("random_horse_color" name(horse_color_euro) 	t1(1a) t2(1) t3(2) t4(3))
("random_horse_color" name(horse_color_guard) 	t1(4) t2(5) t3(6) t4(7))
("random_horse_color" name(horse_color_ind) 	t1(sioux1) t2(sioux2) t3(sioux3) t4(sioux4))
("random_horse_color" name(horse_color_jap) 	t1(2) t2(4) t3(2) t4(4))
("random_horse_color" name(horse_color_east) 	t1(east1) t2(east2) t3(east4) t4(east3))




;=======================================RELOADS for one more shoots

{"horseman_5_shooter_pistol"
	{on spawn
		{tags add "r1 r2 r3 r4 r5"}
	}
	{on fire "gun" overload
		{with_linked_entity "driver"	
			{if rand 0.13 
				{talk "in_action"}
			}
			{ani_play "horse_driver_pistol_aim"}
			;{con "horse_spawn_flash_5shotter_pist"}
			{spawn "flash_gun_pistol_horse" "right_hand" x}

		}
		{delay 0.1
			{if tagged "r5"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r5"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r4"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r4"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r3"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r3"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r2"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r2"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r1"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_reload" 0.15}
				}
				{tags remove "r1"}
				{tags add "r1 r2 r3 r4 r5"}
				{weapon_work "gun" 0}
				{delay 6 {weapon_work "gun" 1}}
				
			}
		}
		{movement_limit slow}
		{ik_enable "ik_right" 0}
		{ik_enable "ik_left" 0}
		{ik_enable "ik_centr" 0}
		{delay 0.2
			{ik_enable "ik_right" 1}
			{ik_enable "ik_left" 1}
			{ik_enable "ik_centr" 1}
			{movement_limit fast}
		}
	}
}

{"horseman_6_shooter_pistol"
	{on spawn
		{tags add "r1 r2 r3 r4 r5 r6"}
	}
	{on fire "gun" overload
		{with_linked_entity "driver"	
			{if rand 0.13 
				{talk "in_action"}
			}
			{ani_play "horse_driver_pistol_aim"}
			;{con "horse_spawn_flash_6shotter_pist"}
			{spawn "flash_gun_pistol_horse" "right_hand" x}

		}
		{delay 0.1
			{if tagged "r6"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r6"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r5"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r5"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r4"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r4"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r3"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r3"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r2"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_recoil" 0.5}
				}
				{tags remove "r2"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r1"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_pistol_reload" 0.15}
				}
				{tags remove "r1"}
				{tags add "r1 r2 r3 r4 r5 r6"}
				{weapon_work "gun" 0}
				{delay 6 {weapon_work "gun" 1}}
			}
		}
		{movement_limit slow}
		{ik_enable "ik_right" 0}
		{ik_enable "ik_left" 0}
		{ik_enable "ik_centr" 0}
		{delay 0.5
			{ik_enable "ik_right" 1}
			{ik_enable "ik_left" 1}
			{ik_enable "ik_centr" 1}
			{movement_limit fast}
		}
	}
}
{"horseman_5_shooter_rifle"
	{on spawn
		{tags add "r1 r2 r3 r4 r5"}
	}
	{on fire "gun" overload
		{with_linked_entity "driver"	
			{if rand 0.13 
				{talk "in_action"}
			}
			{ani_play "horse_driver_aim"}
			;{con "horse_spawn_flash_6shotter_rifle"}
			{spawn "flash_gun_rifle_1_horse" "right_hand" x}

		}
		{delay 0.1
			{if tagged "r5"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r5"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r4"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r4"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r3"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r3"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r2"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r2"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r1"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_reload_6" 0.15}
				}
				{tags remove "r1"}
				{tags add "r1 r2 r3 r4 r5"}
				{weapon_work "gun" 0}
				{delay 1 {movement_limit slow}}
				{delay 6 {weapon_work "gun" 1} {movement_limit fast}}
			}
		}
		{movement_limit slow}
		{ik_enable "ik_right" 0}
		{ik_enable "ik_left" 0}
		{ik_enable "ik_centr" 0}
		{delay 0.5
			{ik_enable "ik_right" 1}
			{ik_enable "ik_left" 1}
			{ik_enable "ik_centr" 1}
			{movement_limit fast}
		}
	}
}
{"horseman_6_shooter_rifle"
	{on spawn
		{tags add "r1 r2 r3 r4 r5 r6"}
	}
	{on fire "gun" overload
		{with_linked_entity "driver"	
			{if rand 0.13 
				{talk "in_action"}
			}
			{ani_play "horse_driver_aim"}
			;{con "horse_spawn_flash_6shotter_rifle"}
			{spawn "flash_gun_rifle_1_horse" "right_hand" x}

		}
		{delay 0.1
			{if tagged "r6"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r6"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r5"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r5"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r4"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r4"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r3"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r3"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r2"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r2"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r1"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_reload_6" 0.15}
				}
				{tags remove "r1"}
				{tags add "r1 r2 r3 r4 r5 r6"}
				{weapon_work "gun" 0}
				{delay 1 {movement_limit slow}}
				{delay 6 {weapon_work "gun" 1} {movement_limit fast}}
			}
		}
		{movement_limit slow}
		{ik_enable "ik_right" 0}
		{ik_enable "ik_left" 0}
		{ik_enable "ik_centr" 0}
		{delay 0.5
			{ik_enable "ik_right" 1}
			{ik_enable "ik_left" 1}
			{ik_enable "ik_centr" 1}
			{movement_limit fast}
		}
	}
}
{"horseman_7_shooter_rifle"
	{on spawn
		{tags add "r1 r2 r3 r4 r5 r6 r7"}
	}
	{on fire "gun" overload
		{with_linked_entity "driver"	
			{if rand 0.13 
				{talk "in_action"}
			}
			{ani_play "horse_driver_aim"}
			;;{con "horse_spawn_flash_7shotter_rifle"}
			{spawn "flash_gun_rifle_1_horse" "right_hand" x}

		}
		{delay 0.1
			{if tagged "r7"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r7"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r6"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r6"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r5"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r5"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r4"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r4"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r3"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r3"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r2"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r2"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r1"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_reload_6" 0.15}
				}
				{tags remove "r1"}
				{tags add "r1 r2 r3 r4 r5 r6 r7"}
				{delay 1 {movement_limit slow}}
				{delay 8 {weapon_work "gun" 1} {movement_limit fast}}
			}
		}
		{movement_limit slow}
		{ik_enable "ik_right" 0}
		{ik_enable "ik_left" 0}
		{ik_enable "ik_centr" 0}
		{delay 0.5
			{ik_enable "ik_right" 1}
			{ik_enable "ik_left" 1}
			{ik_enable "ik_centr" 1}
			{movement_limit fast}
		}
	}
}

{"horseman_10_shooter_rifle"
	{on spawn
		{tags add "r1 r2 r3 r4 r5 r6 r7 r8 r9 r10"}
	}
	{on fire "gun" overload
		{with_linked_entity "driver"	
			{if rand 0.13 
				{talk "in_action"}
			}
			{ani_play "horse_driver_aim"}
			;;{con "horse_spawn_flash_10shotter_rifle"}
			{spawn "flash_gun_rifle_1_horse" "right_hand" x}

		}
		{delay 0.1
			{if tagged "r10"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r10"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r9"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r9"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r8"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r8"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r7"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r7"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r6"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r6"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r5"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r5"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r4"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r4"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r3"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r3"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r2"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_recoil" 0.5}
				}
				{tags remove "r2"}
				{weapon_work "gun" 0}
				{delay 0.4 {weapon_work "gun" 1}}
			else tagged "r1"
				{with_linked_entity "driver"	
					{ani_play "horse_driver_rifle_reload_10" 0.15}
				}
				{tags remove "r1"}
				{tags add "r1 r2 r3 r4 r5 r6 r7 r8 r9 r10"}
				{weapon_work "gun" 0}
				{delay 1 {movement_limit slow}}
				{delay 10 {weapon_work "gun" 1} {movement_limit fast}}
			}
		}
		{movement_limit slow}
		{ik_enable "ik_right" 0}
		{ik_enable "ik_left" 0}
		{ik_enable "ik_centr" 0}
		{delay 0.5
			{ik_enable "ik_right" 1}
			{ik_enable "ik_left" 1}
			{ik_enable "ik_centr" 1}
			{movement_limit fast}
		}
	}
}
;=======================================
;=======================================2nd melee weapon

;=======================================left melee view
;sv_l_sw_eur
;sv_l_sw_east
;sv_l_sw_jap
;sv_l_sw_ind

{"left_weapon_view_eur"
	{on "sword_left_view"
		{with_linked_entity "driver"
			{add_view "sword_officer" "sv_l_sw_eur" "left_hand"} {view show "sv_l_sw_eur"} {view start "sv_l_sw_eur"}
		}
	}
	{on "sword_left_view_off"
		{with_linked_entity "driver"
			{view pause "sv_l_sw_eur"} {view stop "sv_l_sw_eur"} {view hide "sv_l_sw_eur"}
		}
	}
}
{"left_weapon_view_east"
	{on "sword_left_view"
		{with_linked_entity "driver"
			{add_view "afg_sabre" "sv_l_sw_east" "left_hand"} {view show "sv_l_sw_east"} {view start "sv_l_sw_east"}
		}
	}
	{on "sword_left_view_off"
		{with_linked_entity "driver"
			{view pause "sv_l_sw_east"} {view stop "sv_l_sw_east"} {view hide "sv_l_sw_east"}
		}
	}
}
{"left_weapon_view_jap"
	{on "sword_left_view"
		{with_linked_entity "driver"
			{add_view "katana_samurai" "sv_l_sw_jap" "left_hand"} {view show "sv_l_sw_jap"} {view start "sv_l_sw_jap"}
		}
	}
	{on "sword_left_view_off"
		{with_linked_entity "driver"
			{view pause "sv_l_sw_jap"} {view stop "sv_l_sw_jap"} {view hide "sv_l_sw_jap"}
		}
	}
}
{"left_weapon_view_ind"
	{on "sword_left_view"
		{with_linked_entity "driver"
			{add_view "melee_tomahawk" "sv_l_sw_ind" "left_hand"} {view show "sv_l_sw_ind"} {view start "sv_l_sw_ind"}
		}
	}
	{on "sword_left_view_off"
		{with_linked_entity "driver"
			{view pause "sv_l_sw_ind"} {view stop "sv_l_sw_ind"} {view hide "sv_l_sw_ind"}
		}
	}
}
;==========================left melee main
{"horseman_left_weapon"
	{on ik begin "ik_front"
		{if not tagged "melee"
			{tags add "melee"}
			{weapon_work "sword_front" 0}
			{with_linked_entity "driver"	
				{ani_stop "horse_driver_rifle_reload_6"}
				{ani_stop "horse_driver_rifle_reload_10"}
				{ani_stop "horse_driver_pistol_reload"}
				{ani_stop "horse_driver_bow_reload"}
				{ani_stop "squat_reload_gun_mz"}
				{ani_stop "stand_reload_gun_mz"}
				{ani_play "horse_driver_sword_left_take" 0.6}
			}
			{delay 0.1 {call "sword_left_view"}}
			{call "bow_off"}
			{delay 1 
				{movement_limit fast}
				{weapon_work "sword_front" 1}
			}
		}
	}
	{on ik begin "ik_centr"
		{if tagged "melee"
			{tags remove "melee"}
			{with_linked_entity "driver"	
				{ani_play "horse_driver_sword_left_take" -0.6}
			}
			{call "sword_left_view_off"}
			{delay 0.1 {call "bow_on"}}
		}
		{weapon_work "gun" 0}
		{delay 1 
			{movement_limit fast}
			{weapon_work "gun" 1}
		}
	}
	{on fire "sword_front"
		{if tagged "melee"
			{with_linked_entity "driver"		
					{if rand 0.13 
						{talk "in_action"}
					}
				{if rand 0.33
					{if not dead {ani_play "horse_driver_sword_attack_left_sw_01" 0.5}}
					else rand 0.33
					{if not dead {ani_play "horse_driver_sword_attack_left_sw_03" 0.5}}
					else
					{if not dead {ani_play "horse_driver_sword_attack_left_sw_02" 0.5}}
				}
			}
		}
		{weapon_work "sword_front" 0}
		{weapon_work "gun" 0}
		{delay 0.8
			{weapon_work "sword_front" 1}
		}
		{delay 1.5
			{weapon_work "gun" 1}
		}
	}
}