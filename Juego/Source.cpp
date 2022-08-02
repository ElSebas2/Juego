#include <stdio.h>
#include <string>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Windows.h>
#include <math.h>
#include <stdlib.h>
#include "Imagenes.h"
#include "Define.h"
#include "Estructuras.h"

//struct bala_ *colisiones_jugador(int num_enem, int x, int y, int i, int cont, struct enemy_ enem[max_enemy],struct bala_ disparos[max_disparos], int omega[16]);
int col_jugador__enemigo(int num_enem, int x, int y, int i, int cont, struct enemy_ enem[max_enemy], struct bala_ disparos[max_disparos], int omega[16], int flag[max_enemy]);
//struct jugador vida_jugador(int num_enem, int x, int y, int i, int cont, struct enemy_ enem[max_enemy], struct bala_ disparos[max_disparos], int omega[16], struct jugador jugador1);

int main()
{
	int choque[16] = { 0 };
	int llaves = 1;
	int fpss = 0;
	bool play = false;
	int puntajes = 0;
	int rachas_ = 1;
	int vida_player = 0;
	int flag[max_enemy] = { 0 };
	int i;
	int aux = 0;
	int num_enem = 0;
	int contt = 1;
	int contt_ = 1;
	bool freno = true;
	bool disparo = false;
	int x1, y1;
	float vel_x[16];
	float vel_y[16];
	int aux1 = 0;
	int k;
	int omega[16];
	int recarga_ = 0;
	int cont = 0;
	int cont1[max_disparos];
	int	cont2 = 0;
	int cant_disparos = 0;
	int enemy_x = 200, enemy_y = 1080;
	int llave_x = 0;
	int llave_y = 0;
	int segundo = 0;
	float x = 700, y = 700;
	int j;
	int n = 0;

	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	int ancho = GetSystemMetrics(SM_CXSCREEN);
	int alto = GetSystemMetrics(SM_CYSCREEN);

	ALLEGRO_SAMPLE* disparo_ = NULL;
	ALLEGRO_SAMPLE* musicas = NULL;
	ALLEGRO_SAMPLE_INSTANCE* instans = NULL;

	al_reserve_samples(10);

	musicas = al_load_sample(song);
	disparo_ = al_load_sample(disparos_);
	instans = al_create_sample_instance(musicas);
	al_set_sample_instance_playmode(instans, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instans, al_get_default_mixer());


	ALLEGRO_EVENT_QUEUE* cola = al_create_event_queue();
	ALLEGRO_BITMAP* fondo = al_load_bitmap("Imagenes/fondo.jpg");
	ALLEGRO_BITMAP* vida[6] = { al_load_bitmap(vida1),al_load_bitmap(vida2) ,al_load_bitmap(vida3) ,al_load_bitmap(vida4) ,al_load_bitmap(vida5),al_load_bitmap(vida6) };
	ALLEGRO_BITMAP* a0[16] = { al_load_bitmap(p0), al_load_bitmap(p1),al_load_bitmap(p2), al_load_bitmap(p3), al_load_bitmap(p4), al_load_bitmap(p5), al_load_bitmap(p6), al_load_bitmap(p7), al_load_bitmap(p8), al_load_bitmap(p9), al_load_bitmap(p10), al_load_bitmap(p11), al_load_bitmap(p12),al_load_bitmap(p13), al_load_bitmap(p14),al_load_bitmap(p15) };
	ALLEGRO_BITMAP* bala1[17] = { al_load_bitmap(bala_derecha), al_load_bitmap(bala112), al_load_bitmap(bala134), al_load_bitmap(bala156), al_load_bitmap(bala_abajo), al_load_bitmap(bala202), al_load_bitmap(bala224), al_load_bitmap(bala246), al_load_bitmap(bala_izquierda), al_load_bitmap(bala292), al_load_bitmap(bala314), al_load_bitmap(bala336),al_load_bitmap(bala_arriba),al_load_bitmap(bala22),al_load_bitmap(bala44),al_load_bitmap(bala68),al_load_bitmap(nulo) };
	ALLEGRO_BITMAP* circulo_ = al_load_bitmap(circulo);
	ALLEGRO_BITMAP* recargas = al_load_bitmap(bala_completa);
	ALLEGRO_BITMAP* enemy1 = al_load_bitmap(enemy1_);
	ALLEGRO_BITMAP* fuegos[6] = { al_load_bitmap(fuego1),al_load_bitmap(fuego2) ,al_load_bitmap(fuego3) ,al_load_bitmap(fuego4) ,al_load_bitmap(fuego5),al_load_bitmap(nulo) };
	ALLEGRO_BITMAP* hitbox = al_load_bitmap(hitbox1);
	ALLEGRO_BITMAP* isla = al_load_bitmap(isla_);
	ALLEGRO_BITMAP* isla_2 = al_load_bitmap("Imagenes/Isla2.png");
	ALLEGRO_BITMAP* tabla_puntajes = al_load_bitmap(tabla_puntaje);
	ALLEGRO_BITMAP* racha = al_load_bitmap(rachas);
	ALLEGRO_BITMAP* menu[3] = { al_load_bitmap(menu1),al_load_bitmap(menu_play),al_load_bitmap(menu_high) };
	ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
	ALLEGRO_DISPLAY* ventana = al_create_display(ancho, alto);
	ALLEGRO_TIMER* seg = al_create_timer(1.0);
	ALLEGRO_TIMER* fps = al_create_timer(1 / 2.0);
	ALLEGRO_TIMER* recarga = al_create_timer(1.0);
	ALLEGRO_FONT* letra = al_load_font("Sernes-Light.otf", 30, 0);
	ALLEGRO_FONT* letra1 = al_load_font("Sernes-Light.otf", 15, 0);
	ALLEGRO_BITMAP* llave = al_load_bitmap(llave_);

		



	al_set_window_title(ventana, "Battleship 1945");
	al_set_window_position(ventana, 0, 0);
	al_register_event_source(cola, al_get_keyboard_event_source());
	al_register_event_source(cola, al_get_timer_event_source(seg));
	al_register_event_source(cola, al_get_timer_event_source(recarga));
	al_register_event_source(cola, al_get_timer_event_source(fps));
	al_register_event_source(cola, al_get_mouse_event_source());
	al_start_timer(seg);
	al_start_timer(recarga);
	srand(time(0));
	for (i = 0; i < max_enemy; i++)
	{
		enem[i].pos_x = 300 + rand() % 50;
		enem[i].pos_y = 1080;
		enem[i].ndisparos = 0;
	}
	omega[0] = 0;
	for (k = 0; k <= 15; k++)
	{
		omega[k] = 22 * k;
		if (omega[k] >= 88)
		{
			omega[k] = omega[k] + 2;
		}
		if (omega[k] >= 178)
		{
			omega[k] = omega[k] + 2;
		}
		if (omega[k] >= 268)
		{
			omega[k] = omega[k] + 2;
		}
	}
	for (k = 0; k <= 15; k++)
	{
		vel_y[k] = (speed * cos(omega[k] * f));
		vel_x[k] = (speed * sin(omega[k] * f));
	}
	ALLEGRO_EVENT Evento;
	while (true)
	{
		//al_play_sample_instance(instans);
		al_wait_for_event(cola, &Evento);

		if (play == false)
		{
			al_draw_bitmap(menu[n], 0, 0, 0);
			if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				x1 = Evento.mouse.x;
				y1 = Evento.mouse.y;
				//printf("X : %d\tY: %d\n", x1, y1);
				if (x1 <= 1171 && x1 >= 695)
				{
					if (y1 <= 706 && y1 >= 495)
					{
						n = 1;
						if (Evento.mouse.button)
						{

							play = true;
						}
					}
				}
				else if (x1 <= 584 && x1 >= 986)
				{
					if (y1 <= 826 && y1 >= 646)
					{
						
						n = 2;
					}
				}
				else
				{
					n = 0;
				}
			}
		}


		if (play == true)
		{
			al_draw_bitmap(fondo, 0, 0, 0);
			al_draw_bitmap(isla, 1300, 500, 0);
			al_draw_bitmap(isla_2, 1000, 200, 0);
			if (Evento.type == ALLEGRO_EVENT_TIMER)
			{

				if (Evento.timer.source == fps)
				{
					fpss = fpss + 1;
				}
			}



			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (Evento.keyboard.keycode == ALLEGRO_KEY_UP)
				{
					freno = false;
				}
				if (Evento.keyboard.keycode == ALLEGRO_KEY_DOWN)
				{
					freno = true;

				}
				if (Evento.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				{
					cont++;
					if (cont > 15)
					{
						cont = 0;
					}
				}
				if (Evento.keyboard.keycode == ALLEGRO_KEY_LEFT)
				{
					cont = cont - 1;
					if (cont < 0)
					{
						cont = 15;
					}
				}
			}
			/*//==============     AJUSTAR VELOCIDAD PARA LAS POSICIONES    ================================//*/
			if (freno == false)
			{
				if (choque[cont] == 0)
				{
					y = y - vel_y[cont];
					x = x + vel_x[cont];

				}
			}
			//================== CARGAR POSICIONES DE LAS BALAS    ==============================//

			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (Evento.keyboard.keycode == ALLEGRO_KEY_SPACE)
				{
					if (cant_disparos < max_disparos_ply)
					{
						cont1[cant_disparos] = cont;
						if (omega[cont1[cant_disparos]] >= 66 && omega[cont1[cant_disparos]] <= 90)
						{
							disparos_ply[cant_disparos].pos_y = y + 53 * cos(omega[cont1[cant_disparos]] * f) + 70;
						}
						else if ((omega[cont1[cant_disparos]] >= 112 && omega[cont1[cant_disparos]] <= 134))
						{
							disparos_ply[cant_disparos].pos_y = y + 53 * cos(omega[cont1[cant_disparos]] * f) + 130;
						}
						else if ((omega[cont1[cant_disparos]] >= 156 && omega[cont1[cant_disparos]] <= 180))
						{
							disparos_ply[cant_disparos].pos_y = y + 53 * cos(omega[cont1[cant_disparos]] * f) + 170;
						}
						else if ((omega[cont1[cant_disparos]] >= 202 && omega[cont1[cant_disparos]] <= 224))
						{
							disparos_ply[cant_disparos].pos_y = y + 53 * cos(omega[cont1[cant_disparos]] * f) + 170;
						}
						else if ((omega[cont1[cant_disparos]] >= 246 && omega[cont1[cant_disparos]] <= 270))
						{
							disparos_ply[cant_disparos].pos_y = y + 53 * cos(omega[cont1[cant_disparos]] * f) + 100;
						}
						else
						{
							disparos_ply[cant_disparos].pos_y = y + 53 * cos(omega[cont1[cant_disparos]] * f);
						}
						disparos_ply[cant_disparos].pos_x = x + 53 * sin(omega[cont1[cant_disparos]] * f) + 100;
						disparos_ply[cant_disparos].vel_x = speed_bala * cos(omega[cont1[cant_disparos]] * f);
						disparos_ply[cant_disparos].vel_y = speed_bala * sin(omega[cont1[cant_disparos]] * f);
						cant_disparos++;
						al_play_sample(disparo_, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

					}

				}
			}
			if (cant_disparos > 0)
			{
				for (i = 0; i < cant_disparos; i++)
				{
					disparos_ply[i].pos_x = disparos_ply[i].pos_x + disparos_ply[i].vel_x;
					disparos_ply[i].pos_y = disparos_ply[i].pos_y + disparos_ply[i].vel_y;
					if (disparos_ply[i].pos_x < 1980 && disparos_ply[i].pos_x > 0)
					{
						if (disparos_ply[i].pos_y < 1080 && disparos_ply[i].pos_y > 0)
						{
							al_draw_bitmap(bala1[cont1[i]], disparos_ply[i].pos_x, disparos_ply[i].pos_y, 0);
						}
					}
				}
			}



			//===================    RECARGAS    ====================//

			if (cant_disparos == max_disparos_ply)
			{
				if (Evento.type == ALLEGRO_EVENT_TIMER)
				{
					if (Evento.timer.source == recarga)
					{
						if (recarga_ < 1)
						{
							recargas = al_load_bitmap(circulo);
						}
						if (recarga_ >= 1 && recarga_ < 2)
						{
							recargas = al_load_bitmap(bala1_4);
						}
						if (recarga_ >= 2 && recarga_ < 3)
						{
							recargas = al_load_bitmap(bala2_4);
						}
						if (recarga_ >= 3 && recarga_ < 4)
						{
							recargas = al_load_bitmap(bala3_4);
						}
						if (recarga_ >= 4)
						{
							recargas = al_load_bitmap(bala_completa);
							cant_disparos = 0;
							recarga_ = -1;
						}
						recarga_++;
					}
				}
			}

			//====================    APARICION DE ENEMEGOS   ========================//

			if (Evento.type == ALLEGRO_EVENT_TIMER)
			{

				if (Evento.timer.source == seg)
				{
					segundo = segundo +1;
				}
			}


			if (aux1 == 0 && num_enem < max_enemy)
			{
				num_enem++;
				enem[num_enem].pos_x = 50 + rand() % 300;
				enem[num_enem].pos_y = 1080;
				enem[num_enem].vel_x = 0;
				enem[num_enem].vel_y = vel_enemy;
				enem[num_enem].ndisparos = 0;
				aux1 = 1;
			}

			if (cont2++ > 120)
			{
				aux1 = 0; cont2 = 0;
			}

			if (num_enem > 0)
			{
				for (i = 1; i <= num_enem; i++)
				{
					if (enem[i].pos_y != -150 && enem[i].pos_y > -150)
					{
						enem[i].pos_y = enem[i].pos_y - enem[i].vel_y;
						if (flag[i] == 0)
						{
							al_draw_bitmap(enemy1, enem[i].pos_x, enem[i].pos_y, flag[i]);
						}
						else
						{
							if (flag[i] != 0)
							{
								enem[i].pos_x = -150;
								enem[i].pos_y = -150;
								enem[i].vel_x = 0;
								enem[i].vel_y = 0;
								enem[i].ndisparos = 0;
							}
						}
					}
				}
			}

			//================= CREACION DE LAS BALAS ENEMIGAS  =======================//
			if (contt++ > 30)
			{
				aux = 0; contt = 0;

			}
			for (j = 1; j <= num_enem; j++)
			{

				if (segundo > 2 && aux == 0)
				{
					if (enem[j].ndisparos <= max_disparos)
					{
						if (flag[j] == 0)
						{
							enem[j].ndisparos++;
							disparos[enem[j].ndisparos].x = enem[j].pos_x + 97;
							disparos[enem[j].ndisparos].y = enem[j].pos_y + 39;
							disparos[enem[j].ndisparos].vel_x = 20;
							disparos[enem[j].ndisparos].vel_y = 0;
						}
						else
						{
							disparos[enem[j].ndisparos].x = 0;
							disparos[enem[j].ndisparos].y =0;
							disparos[enem[j].ndisparos].vel_x = 0;
							disparos[enem[j].ndisparos].vel_y = 0;
						}
						if (j == num_enem)
						{
							aux = 1;
						}
					}
				}
			}
			for (i = 1; i < max_disparos; i++)
			{
				disparos[i].x = disparos[i].x + disparos[i].vel_x;
				if (disparos[i].x <= 1980)
				{
					if (flag[i] == 0)
					{
						al_draw_bitmap(bala1[0], disparos[i].x, disparos[i].y, flag[i]);
					}
				}
			}


			//==================   COLISION BALA-----ENEMIGO   =================//
			if (cant_disparos > 0)
			{
				for (k = 1; k < num_enem+1; k++)
				{
					for (i = 0; i <= cant_disparos; i++)
					{
						if (disparos_ply[i].pos_x >= enem[k].pos_x + 57 && disparos_ply[i].pos_x <= enem[k].pos_x + 97)
						{
							if (disparos_ply[i].pos_y >= enem[k].pos_y && disparos_ply[i].pos_y <= enem[k].pos_y + 157)
							{
								enem[k].vida++;
								puntajes = puntajes + 100 * rachas_;
								if (rachas_ < 6)
								{
									rachas_++;
								}

								if (enem[k].vida >= 3)
								{
									flag[k] = 1;
								}
								disparos_ply[i].pos_y = 5000;
							}
						}
					}
				}

			}
			//////////////////////////////============= GENERACION DE ITEM PARA CURAR=========================///////////////////

			if (segundo > 5 && segundo != 0 && llaves == 1)
			{
				llave_x = 500;
				llave_y = 500;
				llaves = 0;
			}	
			if (llaves == 0)
			{
				if (segundo <= 150)
				{
					if (n != 0)
					{
						al_draw_bitmap(llave, llave_x, llave_y, n);
					}
				}
					
			}

			///////////////////////////================ COLISION ITEM PARA CURAR Y JUGADOR =============//////////////////
			if (n != 0)
			{
				if (omega[cont] == 0)
				{
					if (llave_x + 100 >= x + 80 + 100 * sin(omega[cont] * f) && llave_x <= x + 122.5 - 100 * sin(omega[cont] * f))
					{
						if (llave_y + 100 >= y + 100 - 100 * cos(omega[cont] * f) && llave_y <= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player >= 2)
							{
								vida_player = vida_player - 2;
							}
							n = 0;
						}
					}
				}
				if (omega[cont] == 180)
				{
					if (llave_x + 100 >= x + 80 + 100 * sin(omega[cont] * f) && llave_x <= x + 122.5 - 100 * sin(omega[cont] * f))
					{
						if (llave_y <= y + 100 - 100 * cos(omega[cont] * f) && llave_y + 100 >= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player >= 2)
							{
								vida_player = vida_player - 2;
							}
							n = 0;
						}
					}
				}
				if (omega[cont] == 90)
				{
					if (llave_x <= x + 100 + 100 * sin(omega[cont] * f) && llave_x + 100 >= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (llave_y <= y + 122.5 - 100 * cos(omega[cont] * f) && llave_y + 100 >= y + 80 + 100 * cos(omega[cont] * f))
						{
							if (vida_player >= 2)
							{
								vida_player = vida_player - 2;
							}
							n = 0;
						}
					}
				}
				if (omega[cont] == 270)
				{
					if (llave_x >= x + 100 + 100 * sin(omega[cont] * f) && llave_x + 100 <= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (llave_y + 100 <= y + 122.5 - 100 * cos(omega[cont] * f) && llave_y + 100 >= y + 80 + 100 * cos(omega[cont] * f))
						{
							if (vida_player >= 2)
							{
								vida_player = vida_player - 2;
							}
							n = 0;
						}
					}
				}
				if (omega[cont] > 0 && omega[cont] < 90)
				{
					if (llave_x <= x + 100 + 100 * sin(omega[cont] * f) && llave_x + 100 >= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (llave_y + 100 >= y + 100 - 100 * cos(omega[cont] * f) && llave_y <= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player >= 2)
							{
								vida_player = vida_player - 2;
							}
							n = 0;
						}
					}
				}
				if (omega[cont] > 90 && omega[cont] < 180)
				{
					if (llave_x <= x + 100 + 100 * sin(omega[cont] * f) && llave_x + 100 >= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (llave_y <= y + 100 - 100 * cos(omega[cont] * f) && llave_y + 100 >= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player >= 2)
							{
								vida_player = vida_player - 2;
							}
							n = 0;
						}
					}
				}
				if (omega[cont] > 180 && omega[cont] < 270)
				{
					if (llave_x + 100 >= x + 100 + 100 * sin(omega[cont] * f) && llave_x <= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (llave_y <= y + 100 - 100 * cos(omega[cont] * f) && llave_y + 100 >= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player >= 2)
							{
								vida_player = vida_player - 2;
							}
							n = 0;
						}
					}
				}
				if (omega[cont] > 270)
				{
					if (llave_x + 100 >= x + 100 + 100 * sin(omega[cont] * f) && llave_x <= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (llave_y + 100 >= y + 100 - 100 * cos(omega[cont] * f) && llave_y <= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player >= 2)
							{
								vida_player = vida_player - 2;
							}
							n = 0;
						}
					}
				}
			}

			/*
				//======================== VIDA JUGADOR  =========================//
				vida_jugador(num_enem, x, y, i, cont, enem, disparos, omega, jugador1);
				//====================	COLISION BALA-------JUGADOR	================//
				disparos[i] = *colisiones_jugador(num_enem, x, y, i, cont, enem ,disparos, omega);*/


				//==================== COLISION JUGADOR-----ENEMIGOS   ======================//

			flag[i] = col_jugador__enemigo(num_enem, x, y, i, cont, enem, disparos, omega, flag);


			////////////////////////////////////////////////==========================================//////////////////////////////////////////////////////

			for (i = 1; i <= enem[num_enem].ndisparos; i++)
			{
				if (omega[cont] == 0)
				{
					if (disparos[i].x >= x + 80 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 122.5 - 100 * sin(omega[cont] * f))
					{
						if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player < 6)
							{
								vida_player++;
							}
							disparos[i].x = 1980;
						}
					}
				}
				if (omega[cont] == 180)
				{
					if (disparos[i].x >= x + 80 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 122.5 - 100 * sin(omega[cont] * f))
					{
						if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player < 6)
							{
								vida_player++;
							}
							disparos[i].x = 1980;
						}
					}
				}
				if (omega[cont] == 90)
				{
					if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
					{

						if (disparos[i].y <= y + 122.5 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 80 + 100 * cos(omega[cont] * f))
						{
							if (vida_player < 6)
							{
								vida_player++;
							}
							disparos[i].x = 1980;
						}
					}
				}
				if (omega[cont] == 270)
				{
					if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (disparos[i].y <= y + 122.5 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 80 + 100 * cos(omega[cont] * f))
						{
							if (vida_player < 6)
							{
								vida_player++;
							}
							disparos[i].x = 1980;
						}
					}
				}
				if (omega[cont] > 0 && omega[cont] < 90)
				{
					if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player < 6)
							{
								vida_player++;
							}
							disparos[i].x = 1980;
						}
					}
				}
				if (omega[cont] > 90 && omega[cont] < 180)
				{
					if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player < 6)
							{
								vida_player++;
							}
							disparos[i].x = 1980;
						}
					}
				}
				if (omega[cont] > 180 && omega[cont] < 270)
				{
					if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player < 6)
							{
								vida_player++;
							}
							disparos[i].x = 1980;
						}
					}
				}
				if (omega[cont] > 270)
				{
					if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
					{
						if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
						{
							if (vida_player < 6)
							{
								vida_player++;
							}
							disparos[i].x = 1980;
						}
					}
				}
			}


			//////////////////////====================== COLISION ===============================//////////////////////

			al_draw_filled_rectangle(500, 500, 600, 600, negro);

			if (omega[cont] == 0)
			{
				if (600 >= x + 80 + 100 * sin(omega[cont] * f) && 500 <= x + 122.5 - 100 * sin(omega[cont] * f))
				{
					if (600 >= y + 100 - 100 * cos(omega[cont] * f) && 500 <= y + 100 + 100 * cos(omega[cont] * f))
					{
						choque[cont] = 1;
					}
					else
					{
						choque[cont] = 0;
					}
					
				}
				else
				{
					choque[cont] = 0;
				}
			}
		
			if (omega[cont] == 180)
			{
				if (600 >= x + 80 + 100 * sin(omega[cont] * f) && 500 <= x + 122.5 - 100 * sin(omega[cont] * f))
				{
					if (500 <= y + 100 - 100 * cos(omega[cont] * f) && 600 >= y + 100 + 100 * cos(omega[cont] * f))
					{
						choque[cont] = 1;
					}
					else
					{
						choque[cont] = 0;
					}
				}
				else
				{
					choque[cont] = 0;
				}
			}
			if (omega[cont] == 90)
			{
				if (500 <= x + 100 + 100 * sin(omega[cont] * f) && 600 >= x + 100 - 100 * sin(omega[cont] * f))
				{
					if (500 <= y + 122.5 - 100 * cos(omega[cont] * f) && 600 >= y + 80 + 100 * cos(omega[cont] * f))
					{
						choque[cont] = 1;
					}
					else
					{
						choque[cont] = 0;
					}
				}
				else
				{
					choque[cont] = 0;
				}
			}
			if (omega[cont] == 270)
			{
				if (600 >= x + 100 + 100 * sin(omega[cont] * f) && 600 <= x + 200 - 100 * sin(omega[cont] * f))
				{
					if (500 <= y + 122.5 - 100 * cos(omega[cont] * f) && 600 >= y + 80 + 100 * cos(omega[cont] * f))
					{
						choque[cont] = 1;
					}
					else
					{
						choque[cont] = 0;
					}
				}
				else
				{
					choque[cont] = 0;
				}
			}
			if (omega[cont] > 0 && omega[cont] < 90)
			{
				if (500 <= x + 100 + 100 * sin(omega[cont] * f) && 600 >= x + 100 - 100 * sin(omega[cont] * f))
				{
					if (600 >= y + 100 - 100 * cos(omega[cont] * f) && 500 <= y + 100 + 100 * cos(omega[cont] * f))
					{
						choque[cont] = 1;
					}
					else
					{
						choque[cont] = 0;
					}
				}
				else
				{
					choque[cont] = 0;
				}
			}
			if (omega[cont] > 90 && omega[cont] < 180)
			{
				if (500 <= x + 100 + 100 * sin(omega[cont] * f) && 600 >= x + 100 - 100 * sin(omega[cont] * f))
				{
					if (500 <= y + 100 - 100 * cos(omega[cont] * f) && 600 >= y + 100 + 100 * cos(omega[cont] * f))
					{
						choque[cont] = 1;
					}
					else
					{
						choque[cont] = 0;
					}
				}
				else
				{
					choque[cont] = 0;
				}
			}
			if (omega[cont] > 180 && omega[cont] < 270)
			{
				if (600 >= x + 100 + 100 * sin(omega[cont] * f) && 500 <= x + 100 - 100 * sin(omega[cont] * f))
				{
					if (500 <= y + 100 - 100 * cos(omega[cont] * f) && 600 >= y + 100 + 100 * cos(omega[cont] * f))
					{
						choque[cont] = 1;
					}
					else
					{
						choque[cont] = 0;
					}
				}
				else
				{
					choque[cont] = 0;
				}
			}
			if (omega[cont] > 270)
			{
				if (600 >= x + 100 + 100 * sin(omega[cont] * f) && 500 <= x + 100 - 100 * sin(omega[cont] * f))
				{
					if (600 >= y + 100 - 100 * cos(omega[cont] * f) && 500 <= y + 100 + 100 * cos(omega[cont] * f))
					{
						choque[cont] = 1;
					}
					else
					{
						choque[cont] = 0;
					}
				}
				else
				{
					choque[cont] = 0;
				}
			}







			//====================  COLISION JUGADOR--ISLA1   ==================//
			al_draw_line(1300, 693, 1562, 492, negro, 3);
			al_draw_line(1300, 693, 1300, 756, negro, 3);
			al_draw_line(1300, 756, 1462, 893, negro, 3);
			al_draw_line(1462, 893, 1632, 723, negro, 3);
			al_draw_line(1632, 723, 1642, 510, negro, 3);
			al_draw_line(1562, 492, 1642, 510, negro, 3);

			al_draw_bitmap(circulo_, 50, 933, 0);
			al_draw_bitmap(recargas, 50, 933, 0);
			al_draw_bitmap(a0[cont], x, y, 0);
			al_draw_bitmap(tabla_puntajes, 1200, 0, 0);
			al_draw_bitmap(racha, 1385, 90, 0);
			al_draw_textf(letra, negro, 1250, 30, 0, "Puntaje:    %d", puntajes);
			al_draw_textf(letra1, negro, 1415, 100, 0, "Racha:   x%d", rachas_);
			al_draw_bitmap(vida[vida_player], 900, 0, 0);

		}
		if (Evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			al_destroy_bitmap(a0[cont]);
			al_destroy_bitmap(circulo_);
			al_destroy_bitmap(recargas);
			return 0;
		}
		al_flip_display();
	}
}


/*struct bala_* colisiones_jugador(int num_enem, int x, int y, int i, int cont, struct enemy_ enem[max_enemy], struct bala_ disparos[max_disparos], int omega[16])
{
	for (i = 1; i <= enem[num_enem - 1].ndisparos; i++)
	{
		if (omega[cont] == 0)
		{
			if (disparos[i].x >= x + 80 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 122.5 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					disparos[i].x = 1980;
					
				}
			}
		}
		if (omega[cont] == 180)
		{
			if (disparos[i].x >= x + 80 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 122.5 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					disparos[i].x = 1980;
				
				}
			}
		}
		if (omega[cont] == 90)
		{
			if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
			{

				if (disparos[i].y <= y + 122.5 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 80 + 100 * cos(omega[cont] * f))
				{
					disparos[i].x = 1980;
			
				}
			}
		}
		if (omega[cont] == 270)
		{
			if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y <= y + 122.5 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 80 + 100 * cos(omega[cont] * f))
				{
					disparos[i].x = 1980;
			
				}
			}
		}
		if (omega[cont] > 0 && omega[cont] < 90)
		{
			if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					disparos[i].x = 1980;
				
				}
			}
		}
		if (omega[cont] > 90 && omega[cont] < 180)
		{
			if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					disparos[i].x = 1980;
				
				}
			}
		}
		if (omega[cont] > 180 && omega[cont] < 270)
		{
			if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					disparos[i].x = 1980;
				
				}
			}
		}
		if (omega[cont] > 270)
		{
			if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					disparos[i].x = 1980;
			
				}
			}
		}
	}
	return disparos;
}*/

int col_jugador__enemigo(int num_enem, int x, int y, int i, int cont, struct enemy_ enem[max_enemy], struct bala_ disparos[max_disparos], int omega[16], int flag[max_enemy])
{
	for (i = 0; i <= num_enem; i++)
	{
		if (omega[cont] == 0)
		{
			if (enem[i].pos_x + 58 >= x + 80 + 100 * sin(omega[cont] * f) && enem[i].pos_x + 95 <= x + 122.5 - 100 * sin(omega[cont] * f))
			{

				if (enem[i].pos_y >= y + 100 - 100 * cos(omega[cont] * f) && enem[i].pos_y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					flag[i] = 1;
				}
			}
		}
		if (omega[cont] == 180)
		{
			if (enem[i].pos_x + 58 <= x + 80 + 100 * sin(omega[cont] * f) && enem[i].pos_x + 120 >= x + 122.5 - 100 * sin(omega[cont] * f))
			{
				if (enem[i].pos_y <= y + 100 - 100 * cos(omega[cont] * f) && enem[i].pos_y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					flag[i] = 1;
				}
			}
		}
		if (omega[cont] == 90)
		{
			if (enem[i].pos_x + 95 <= x + 100 + 100 * sin(omega[cont] * f) && enem[i].pos_x + 58 >= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (enem[i].pos_y <= y + 122.5 - 100 * cos(omega[cont] * f) && enem[i].pos_y >= y + 80 + 100 * cos(omega[cont] * f))
				{
					flag[i] = 1;
				}
			}
		}
		if (omega[cont] == 270)
		{
			if (enem[i].pos_x + 95 >= x + 100 + 100 * sin(omega[cont] * f) && enem[i].pos_x + 58 <= x + 200 - 100 * sin(omega[cont] * f))
			{
				if (enem[i].pos_y <= y + 122.5 - 100 * cos(omega[cont] * f) && enem[i].pos_y >= y + 80 + 100 * cos(omega[cont] * f))
				{
					flag[i] = 1;
				}
			}
		}
		if (omega[cont] > 0 && omega[cont] < 90)
		{
			if (enem[i].pos_x + 95 <= x + 100 + 100 * sin(omega[cont] * f) && enem[i].pos_x + 58 >= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (enem[i].pos_y >= y + 100 - 100 * cos(omega[cont] * f) && enem[i].pos_y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					flag[i] = 1;
				}
			}
		}
		if (omega[cont] > 90 && omega[cont] < 180)
		{
			if (enem[i].pos_x + 95 <= x + 100 + 100 * sin(omega[cont] * f) && enem[i].pos_x + 58 >= x + 100 - 100 * sin(omega[cont] * f))
			{

				if (enem[i].pos_y <= y + 100 - 100 * cos(omega[cont] * f) && enem[i].pos_y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					flag[i] = 1;
				}
			}
		}
		if (omega[cont] > 180 && omega[cont] < 270)
		{
			if (enem[i].pos_x + 95 >= x + 100 + 100 * sin(omega[cont] * f) && enem[i].pos_x + 58 <= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (enem[i].pos_y <= y + 100 - 100 * cos(omega[cont] * f) && enem[i].pos_y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					flag[i] = 1;
				}
			}
		}
		if (omega[cont] > 270)
		{
			if (enem[i].pos_x + 58 >= x + 100 + 100 * sin(omega[cont] * f) && enem[i].pos_x + 95 <= x + 100 - 100 * sin(omega[cont] * f))
			{

				if (enem[i].pos_y >= y + 100 - 100 * cos(omega[cont] * f) && enem[i].pos_y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					flag[i] = 1;
				}
			}
		}
	}
	return flag[i];
}

/*struct jugador vida_jugador(int num_enem, int x, int y, int i, int cont, struct enemy_ enem[max_enemy], struct bala_ disparos[max_disparos], int omega[16], struct jugador jugador1)
{
	for (i = 0; i <= enem[num_enem - 1].ndisparos; i++)
	{
		if (omega[cont] == 0)
		{
			if (disparos[i].x >= x + 80 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 122.5 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					jugador1.vida++;

				}
			}
		}
		if (omega[cont] == 180)
		{
			if (disparos[i].x >= x + 80 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 122.5 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					jugador1.vida++;

				}
			}
		}
		if (omega[cont] == 90)
		{
			if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
			{

				if (disparos[i].y <= y + 122.5 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 80 + 100 * cos(omega[cont] * f))
				{
					jugador1.vida++;

				}
			}
		}
		if (omega[cont] == 270)
		{
			if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y <= y + 122.5 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 80 + 100 * cos(omega[cont] * f))
				{
					jugador1.vida++;

				}
			}
		}
		if (omega[cont] > 0 && omega[cont] < 90)
		{
			if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					jugador1.vida++;

				}
			}
		}
		if (omega[cont] > 90 && omega[cont] < 180)
		{
			if (disparos[i].x <= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x >= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					jugador1.vida++;

				}
			}
		}
		if (omega[cont] > 180 && omega[cont] < 270)
		{
			if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y <= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y >= y + 100 + 100 * cos(omega[cont] * f))
				{
					jugador1.vida++;

				}
			}
		}
		if (omega[cont] > 270)
		{
			if (disparos[i].x >= x + 100 + 100 * sin(omega[cont] * f) && disparos[i].x <= x + 100 - 100 * sin(omega[cont] * f))
			{
				if (disparos[i].y >= y + 100 - 100 * cos(omega[cont] * f) && disparos[i].y <= y + 100 + 100 * cos(omega[cont] * f))
				{
					jugador1.vida++;

				}
			}
		}
	}
	return jugador1;
}*/
