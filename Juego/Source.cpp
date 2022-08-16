#include <stdio.h>
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
#include "Funciones.h"

//struct bala_ *colisiones_jugador(int num_enem, int x, int y, int i, int orientacion_jugador, struct enemy_ enem[max_enemy],struct bala_ disparos[max_disparos], int omega[16]);
//struct jugador vida_jugador(int num_enem, int x, int y, int i, int orientacion_jugador, struct enemy_ enem[max_enemy], struct bala_ disparos[max_disparos], int omega[16], struct jugador jugador1);


void cargar_mapa(char nombre[10], char** mapa);
struct jefe movimiento(struct jefe boss, struct jugador player);

int main()
{
	FILE* mini_matriz;
	FILE* mapa1;
	FILE* mapa2;
	FILE* mapa3;


	FILE* item_curacion;
	FILE* mapa_juego;
	
	int sonido_disparos_boss = 0;
	float error_x;
	float error_y;
	int angulo_y;
	int angulo_x;
	int auxxx = 0;
	int a = 0;
	int pos_bitmap_boss = 3;
	int contx = 0;
	int dx[15];
	int dy[15];
	bool auxx = false;
	bool reloading = false;
	char mini_mapa[mini_SIZE][mini_SIZE];
	char mapa[SIZE][SIZE];
	char item_cura[mini_SIZE][mini_SIZE];
	char basura;
	int choque[16] = { 0 };
	int llaves = 1;
	int fpss = 0;
	bool play = false;
	int puntajes = 0;
	int rachas_ = 1;
	int vida_player = 0;
	int flag[20] = { 0 };
	int i;
	int aux = 0;
	int num_enem = 0;
	int contt = 1;
	bool freno = true;
	bool disparo = false;
	int x1, y1;
	int k;
	int omega[16];
	int recarga_ = 0;
	int orientacion_jugador = 0;
	int cont1[max_disparos];
	int cant_disparos = 0;
	int llave_x = 0;
	int llave_y = 0;
	int segundo = 0;
	int j;
	int n = 0;
	int dx1[100], dy1[100], contx1 = 0;
	int repara = 0;
	int cantFrame_Disparo = 0;
	int cantFrame_Fuego = 0;
	bool animacion = false;
	int animacion_x, animacion_y;
	int mapa_total[MAPA_JUEGO][MAPA_JUEGO];

	init();
	

	int ancho = GetSystemMetrics(SM_CXSCREEN);
	int alto = GetSystemMetrics(SM_CYSCREEN);
		
	item_curacion = fopen("llave.txt","r");
	mini_matriz = fopen("isla.txt", "r");
	mapa1 = fopen("mapa1.txt", "r");
	mapa2 = fopen("mapa2.txt", "r");
	mapa3 = fopen("mapa3.txt", "r");

	mapa_juego = fopen("juego_mapa.txt", "r");

	if (mapa_juego == NULL)
	{
		printf("Error");
		return 0;
	}

	if (mini_matriz == NULL)
	{
		printf("Error");
		return 0;
	}

	if (mapa1 == NULL)
	{
		printf("Error");
		return 0;
	}


	for (i = 0; i < MAPA_JUEGO; i++)
	{
		for (j = 0; j < MAPA_JUEGO; j++)
		{
			fscanf(mapa_juego, "%d", &mapa_total[i][j]);
		}
		//fscanf(mapa_juego, "%c", &basura);
	}

	for (i = 0; i < mini_SIZE; i++)
	{
		for (j = 0; j < mini_SIZE; j++)
		{
			fscanf(mini_matriz, "%c", &mini_mapa[i][j]);
		}
		fscanf(mini_matriz, "%c", &basura);
	}

	for (i = 0; i < mini_SIZE; i++)
	{
		for (j = 0; j < mini_SIZE; j++)
		{
			fscanf(item_curacion, "%c", &item_cura[i][j]);
		}
		fscanf(item_curacion, "%c", &basura);
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fscanf(mapa1, "%c", &mapa[i][j]);
		}
		fscanf(mapa1, "%c", &basura);
	}


	fclose(mapa1);
	fclose(mini_matriz);
	fclose(item_curacion);
	fclose(mapa_juego);

	for (i = 0; i < MAPA_JUEGO; i++)
	{
		for (j = 0; j < MAPA_JUEGO; j++)
		{
			printf("%d", mapa_total[i][j]);
		}
		printf("\n");
	}





	ALLEGRO_SAMPLE* machine_gun = NULL;
	ALLEGRO_SAMPLE* ametralladora = NULL;
	ALLEGRO_SAMPLE* disparo_ = NULL;
	ALLEGRO_SAMPLE* musicas = NULL;
	ALLEGRO_SAMPLE* reparacion = NULL;
	ALLEGRO_SAMPLE_INSTANCE* instans = NULL;
	

	al_reserve_samples(15);

	machine_gun = al_load_sample(machinegun);
	ametralladora = al_load_sample(disp_avion);
	musicas = al_load_sample(song);
	disparo_ = al_load_sample(disparos_);
	reparacion = al_load_sample(repair);


	instans = al_create_sample_instance(musicas);


	al_set_sample_instance_playmode(instans, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instans, al_get_default_mixer());


	ALLEGRO_EVENT_QUEUE* cola = al_create_event_queue();
	ALLEGRO_BITMAP* avion_[4] = { al_load_bitmap(avion),al_load_bitmap(avion1),al_load_bitmap(avion2),al_load_bitmap(avion3) };
	ALLEGRO_BITMAP* fondo = al_load_bitmap("Imagenes/fondo.bmp");
	ALLEGRO_BITMAP* vida[6] = { al_load_bitmap(vida1),al_load_bitmap(vida2) ,al_load_bitmap(vida3) ,al_load_bitmap(vida4) ,al_load_bitmap(vida5),al_load_bitmap(vida6) };
	ALLEGRO_BITMAP* jugador = al_load_bitmap(p0);
	ALLEGRO_BITMAP* bala1[17] = { al_load_bitmap(bala_derecha), al_load_bitmap(bala112), al_load_bitmap(bala134), al_load_bitmap(bala156), al_load_bitmap(bala_abajo), al_load_bitmap(bala202), al_load_bitmap(bala224), al_load_bitmap(bala246), al_load_bitmap(bala_izquierda), al_load_bitmap(bala292), al_load_bitmap(bala314), al_load_bitmap(bala336),al_load_bitmap(bala_arriba),al_load_bitmap(bala22),al_load_bitmap(bala44),al_load_bitmap(bala68),al_load_bitmap(nulo) };
	ALLEGRO_BITMAP* circulo_ = al_load_bitmap(circulo);
	ALLEGRO_BITMAP* recargas = al_load_bitmap(bala_completa);
	ALLEGRO_BITMAP* enemy1 = al_load_bitmap(enemy1_);
	ALLEGRO_BITMAP* disparos_[6] = { al_load_bitmap(disparo1), al_load_bitmap(disparo2), al_load_bitmap(disparo3), al_load_bitmap(disparo4), al_load_bitmap(disparo5), al_load_bitmap(disparo6) };
	ALLEGRO_BITMAP* fuegos[5] = { al_load_bitmap(fuego1),al_load_bitmap(fuego2) ,al_load_bitmap(fuego3) ,al_load_bitmap(fuego4) ,al_load_bitmap(fuego5)};
	ALLEGRO_BITMAP* isla = al_load_bitmap(isla_);
	ALLEGRO_BITMAP* isla_2 = al_load_bitmap("Imagenes/Isla2.png");
	ALLEGRO_BITMAP* tabla_puntajes = al_load_bitmap(tabla_puntaje);
	ALLEGRO_BITMAP* racha = al_load_bitmap(rachas);
	ALLEGRO_BITMAP* menu[3] = { al_load_bitmap(menu1),al_load_bitmap(menu_play),al_load_bitmap(menu_high) };
	ALLEGRO_BITMAP* rec = al_load_bitmap(negro_);
	ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
	ALLEGRO_DISPLAY* ventana = al_create_display(2*ancho/3, 2*alto/3);
	ALLEGRO_TIMER* fps = al_create_timer(1.0/5);
	ALLEGRO_TIMER* seg = al_create_timer(1.0);
	ALLEGRO_TIMER* recarga = al_create_timer(1.0);
	ALLEGRO_FONT* letra = al_load_font("Sernes-Light.TTF", 30, 0);
	ALLEGRO_FONT* letra1 = al_load_font("Sernes-Light.TTF", 20, 0);
	ALLEGRO_BITMAP* llave = al_load_bitmap(llave_);

		

	printf("ANCHO = %d \t ALTO = %d\n", 2 * ancho / 3, 2 * alto / 3);
	al_set_window_title(ventana, "Battleship 1945");
	al_set_window_position(ventana, ancho/2 - ancho/3, alto/2- alto/3);
	al_register_event_source(cola, al_get_keyboard_event_source());
	al_register_event_source(cola, al_get_timer_event_source(seg));
	al_register_event_source(cola, al_get_timer_event_source(recarga));
	al_register_event_source(cola, al_get_timer_event_source(fps));
	al_register_event_source(cola, al_get_mouse_event_source());
	al_start_timer(fps);
	al_start_timer(seg);
	al_start_timer(recarga);
	srand(time(0));
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
		player.vel_y[k] = (speed * cos(omega[k] * f));
		player.vel_x[k] = (speed * sin(omega[k] * f));
	}
	ALLEGRO_EVENT Evento;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (mapa[j][i] == 'I')
			{
				dx[contx] = i * 256;
				dy[contx] = j * 144;
				contx++;
			}
			if (mapa[j][i] == 'L')
			{
				llave_x = i * 256;
				llave_y = j * 144;
			}
		}
	}
	
	
	for (i = 0; i < mini_SIZE; i++)
	{
		for (j = 0; j < mini_SIZE; j++)
		{
			if (item_cura[j][i] == 'C')
			{
				dx1[contx1] = i * 16 + llave_x;
				dy1[contx1] = j * 9 + llave_y;
				contx1++;
			}
		}
		printf("\n");
	}

	salas[0];

	


	while (true)
	{
		al_wait_for_event(cola, &Evento);


		if (play == false)
		{
			al_play_sample_instance(instans);

			al_draw_scaled_bitmap(menu[n], 0, 0, 1900, 1080, 0, 0, al_get_display_width(ventana), al_get_display_height(ventana), 0);
			if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				x1 = Evento.mouse.x;
				y1 = Evento.mouse.y;
				//printf("X : %d\tY: %d\n", x1, y1);
				if (x1 <= 784 && x1 >= 480)
				{
					if (y1 <= 463 && y1 >= 351)
					{
						n = 1;
						if (Evento.mouse.button)
						{
							play = true;
							al_destroy_bitmap(menu[n]);
						}
					}
					else
					{
						n = 0;
					}
				}
				else
				{
					n = 0;
				}
			}
			if (Evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				al_destroy_bitmap(jugador);
				al_destroy_bitmap(circulo_);
				al_destroy_bitmap(recargas);
				return 0;
			}
		}


		if (play == true)
		{


			
			al_draw_scaled_bitmap(fondo, 0, 0, 1900,1080,0,0,al_get_display_width(ventana), al_get_display_height(ventana),0);
			
			for (i = 0; i <= contx; i++)
			{
				al_draw_scaled_bitmap(isla,0,0,al_get_bitmap_width(isla),al_get_bitmap_height(isla), dx[i], dy[i],256,144,0);
			}
				

			if (Evento.type == ALLEGRO_EVENT_TIMER)
			{

				if (Evento.timer.source == fps)
				{
					fpss = fpss + 1;
				}
			}
			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{

				switch (Evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					freno = false;
					break;

				case ALLEGRO_KEY_DOWN:
					freno = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					orientacion_jugador++;
					if (orientacion_jugador > 15)
					{
						orientacion_jugador = 0;
					}
					break;

				case ALLEGRO_KEY_LEFT:
					orientacion_jugador = orientacion_jugador - 1;
					if (orientacion_jugador < 0)
					{
						orientacion_jugador = 15;
					}
					break;
				}
			}
			/*//==============     AJUSTAR VELOCIDAD PARA LAS POSICIONES    ================================//*/
			//player = velocidades_jugador(player, orientacion_jugador, freno, choque);
			if (freno == false)
			{
				if (choque[orientacion_jugador] == 0)
				{
					player.y = player.y - player.vel_y[orientacion_jugador];
					player.x = player.x + player.vel_x[orientacion_jugador];
				}
			}
		
			//================== CARGAR POSICIONES DE LAS BALAS    ==============================//

			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (Evento.keyboard.keycode == ALLEGRO_KEY_SPACE)
				{
					if (cant_disparos < max_disparos_ply && reloading == false)
					{
						animacion = true;
						cantFrame_Disparo = 0;
						al_play_sample(disparo_, 5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						cont1[cant_disparos] = orientacion_jugador;

						player.disparos_ply[cant_disparos].pos_y = player.y - 54 * cos(omega[cont1[cant_disparos]] * f);
						player.disparos_ply[cant_disparos].pos_x = player.x + 53 * sin(omega[cont1[cant_disparos]] * f);

						player.disparos_ply[cant_disparos].vel_x = speed_bala * cos(omega[cont1[cant_disparos]] * f);
						player.disparos_ply[cant_disparos].vel_y = speed_bala * sin(omega[cont1[cant_disparos]] * f);
						cant_disparos++;
						animacion_x = player.disparos_ply[cant_disparos - 1].pos_x + 35 * cos(omega[orientacion_jugador] * f);
						animacion_y = player.disparos_ply[cant_disparos - 1].pos_y + 35 * sin(omega[orientacion_jugador] * f);
						if (cant_disparos % 3 == 0)
						{
							auxx = true;
						}						

					}

				}
			}
			
			if (cant_disparos > 0)
			{
				for (i = 0; i < cant_disparos; i++)
				{
					player.disparos_ply[i].pos_x = player.disparos_ply[i].pos_x + player.disparos_ply[i].vel_x;
					player.disparos_ply[i].pos_y = player.disparos_ply[i].pos_y + player.disparos_ply[i].vel_y;
					if (player.disparos_ply[i].pos_x < 1280 && player.disparos_ply[i].pos_x > 0)
					{
						if (player.disparos_ply[i].pos_y < 720 && player.disparos_ply[i].pos_y > 0)
						{
							al_draw_bitmap(bala1[cont1[i]], player.disparos_ply[i].pos_x, player.disparos_ply[i].pos_y, 0);
						}
					}
				}
			}



			//===================    RECARGAS    ====================//

			if (cant_disparos % 3 == 0 && auxx == true)
			{
				reloading = true;
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
							recarga_ = -1;
							reloading = false;
							auxx = false;
							if (cant_disparos == max_disparos_ply)
							{
								cant_disparos = 0;
							}
						}
						recarga_++;
					}
				}
			}


			if (Evento.type == ALLEGRO_EVENT_TIMER)
			{
				if (++cantFrame_Fuego >= 5)
				{
					cantFrame_Fuego = 0;
				}
				if (animacion == true)
				{
					if (cantFrame_Disparo < 5)
					{
						cantFrame_Disparo++;
					}
					else
					{
						animacion = false;
					}
					
					

					
				}
			}
			

			//====================    APARICION DE ENEMEGOS   ========================//

			if (timer_enem.aux == 0 && num_enem   < max_enemy)
			{
				
				num_enem++;
				enem[num_enem].pos_x = 50 + rand() % 300;
				enem[num_enem].pos_y = 720;
				enem[num_enem].vel_x = 0;
				enem[num_enem].vel_y = vel_enemy;
				enem[num_enem].ndisparos = 0;
				timer_enem.aux = 1;
				
			}
			if (timer_enem.timer++ > 60)
			{
				timer_enem.aux = 0; timer_enem.timer = 0;
			}

			if (num_enem > 0)
			{
				for (i = 1; i <= num_enem; i++)
				{
					//if (enem[i].activo==1)
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
								enem[i].pos_x = -1500;
								enem[i].pos_y = -1500;
								enem[i].vel_x = 0;
								enem[i].vel_y = 0;
								enem[i].ndisparos = 0;
							}
						}
					}
					else
					{
						
						enem[i].pos_x = -1500;
						enem[i].pos_y = -1500;
						enem[i].vel_x = 0;
						enem[i].vel_y = 0;
						enem[i].ndisparos = 0;
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

				if (aux == 0)
				{
					if (enem[j].ndisparos <= max_disparos)
					{
						if (flag[j] == 0)
						{
							enem[j].ndisparos++;
							disparos[enem[j].ndisparos].x = enem[j].pos_x + 97;
							disparos[enem[j].ndisparos].y = enem[j].pos_y + 39;
							disparos[enem[j].ndisparos].vel_x = speed_bala;
							disparos[enem[j].ndisparos].vel_y = 0;
						}
						else
						{
							disparos[enem[j].ndisparos].x = 0;
							disparos[enem[j].ndisparos].y = 0;
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
				if (disparos[i].x <= 1280)
				{
					if (flag[i] == 0)
					{
						al_draw_bitmap(bala1[0], disparos[i].x, disparos[i].y, flag[i]);
					}
				}
				else
				{
					disparos[i].vel_x = 0;
				}
			}

			
			//==================   COLISION BALA-----ENEMIGO   =================//




			
			
					
			if (col_bala_enemigo(player, enem, num_enem, cant_disparos, disparos_ply) == 1)
			{
				for (k = 1; k <= num_enem; k++)
				{
					enem[k].vida++;
					if (enem[k].vida >= 3)
					{
						flag[k] = 1;
					}
					printf("\n%d", num_enem);
					for (i = 0; i <= cant_disparos; i++)
					{
						player.disparos_ply[i].pos_y = 2000;
						player.disparos_ply[i].pos_x = 2000;
						player.disparos_ply[i].vel_x = 0;
						player.disparos_ply[i].vel_y = 0;
						puntajes = puntajes + 100 * rachas_;
						if (rachas_ < 6)
						{
							rachas_++;
						}
					}
				}
			}

			///////////////////////////================ COLISION ITEM PARA CURAR Y JUGADOR =============//////////////////
			angulo_x = 100 * sin(omega[orientacion_jugador] * f);
			angulo_y = 100 * cos(omega[orientacion_jugador] * f);
			if (mapa[(player.y - angulo_y) / 144][(player.x + angulo_x) / 256] == 'L')
			{
				for (k = 0; k < contx; k++)
				{
					if (item_cura[(player.y - angulo_y - dy[k]) / 9][(player.x + angulo_x - dx[k]) / 16] == 'C' && repara == 0)
					{
						
						if (vida_player > 1)
						{
							vida_player = vida_player - 2;
							al_play_sample(reparacion, 5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
							repara = 1;
						}
						else if(vida_player >= 1)
						{
							vida_player = vida_player - 1;
							al_play_sample(reparacion, 5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
							repara = 1;


						}
						
					}
					
				}
			}
			

	
		////////////////////////////////////////////////================= COLISION BALA ------ PLAYER ==================//////////////////////////////////////////////////////
			
			
			error_x = error_x_jugador(omega, orientacion_jugador);
			error_y = error_y_jugador(omega, orientacion_jugador);
			al_draw_rectangle((player.x + 100 * sin(omega[orientacion_jugador] * f)) + error_x, (player.y - 100 * cos(omega[orientacion_jugador] * f)) - error_y, (player.x - 100 * sin(omega[orientacion_jugador] * f)) - error_x, (player.y + 100 * cos(omega[orientacion_jugador] * f)) + error_y, negro, 5);

			for (i = 1; i <= max_disparos; i++)
			{
				if (omega[orientacion_jugador] >= 0 && omega[orientacion_jugador] < 180)
				{
					if (disparos[i].x <= (player.x + 100 * sin(omega[orientacion_jugador] * f)) + error_x && disparos[i].x >= (player.x - 100 * sin(omega[orientacion_jugador] * f)) - error_x)
					{
						if (disparos[i].y >= (player.y - 100 * cos(omega[orientacion_jugador] * f)) - error_y && disparos[i].y <= (player.y + 100 * cos(omega[orientacion_jugador] * f)) + error_y)
						{
							if (vida_player < 5)
							{
								vida_player++;
							}
							disparos[i].x = 2000;
						}
					}
				}
				if (omega[orientacion_jugador] >= 180 && omega[orientacion_jugador] < 360)
				{
					if (disparos[i].x >= (player.x + 100 * sin(omega[orientacion_jugador] * f)) + error_x && disparos[i].x <= (player.x - 100 * sin(omega[orientacion_jugador] * f)) - error_x)
					{
						if (disparos[i].y <= (player.y - 100 * cos(omega[orientacion_jugador] * f)) - error_y && disparos[i].y >= (player.y + 100 * cos(omega[orientacion_jugador] * f)) + error_y)
						{
							if (vida_player < 5)
							{
								vida_player++;
							}
							disparos[i].x = 2000;
						}
					}
				}
			}

			//==================== COLISION JUGADOR-----ENEMIGOS   ======================//
			al_draw_rectangle((player.x + 100 * sin(omega[orientacion_jugador] * f)) + error_x, (player.y - 100 * cos(omega[orientacion_jugador] * f)) - error_y, (player.x - 100 * sin(omega[orientacion_jugador] * f)) - error_x, (player.y + 100 * cos(omega[orientacion_jugador] * f)) + error_y, negro, 5);

			//al_draw_rectangle(enem[k].pos_x + 57, enem[k].pos_y, enem[k].pos_x + 97, enem[k].pos_y + 157, negro, 5);

			for (i = 1; i <= num_enem; i++)
			{
				if (true)
				{
					if (enem[i].pos_x + 57 <= (player.x + 100 * sin(omega[orientacion_jugador] * f)) + error_x && enem[i].pos_x + 97 >= (player.x - 100 * sin(omega[orientacion_jugador] * f)) - error_x)
					{
						if (enem[i].pos_y + 150 >= (player.y - 100 * cos(omega[orientacion_jugador] * f)) - error_y && enem[i].pos_y <= (player.y + 100 * cos(omega[orientacion_jugador] * f)) + error_y)
						{
							//al_draw_line(200, 200, 300, 300, negro, 5);
							flag[i] = 1;
							if (vida_player < 5)
							{
								vida_player++;
								vida_player++;
							}
							
						}
					}
				}
				
			}



			
			
			

			//////////////////////====================== COLISION ===============================//////////////////////

			


			

			if (mapa[(player.y - angulo_y) / 144][(player.x + angulo_x) / 256] == 'I')
			{
				for (k = 0; k < contx; k++)
				{
					if (mini_mapa[(player.y  - angulo_y - dy[k]) / 9][(player.x + angulo_x - dx[k]) / 16] == 'C')
					{
						choque[orientacion_jugador] = 1;
					}
					else
					{		
						choque[orientacion_jugador] = 0;
					}					
				}
			}
			else
			{
				choque[orientacion_jugador] = 0;
			}
		



























			
	
			


			///////////////////======================= CREAR JEFE ========================///////////////////////

			

			//if (false)
			//{
			//	/// ============================ MOVIMIENTO ======================////////
			//	if (boss.pos_x > -200 && pos_bitmap_boss == 3)
			//	{
			//		boss = movimiento(boss, player);
			//	}
			//	if (boss.pos_x < -200 && pos_bitmap_boss == 3)
			//	{
			//		pos_bitmap_boss = 2;
			//		boss.pos_y = -200;
			//		boss.pos_x = player.x;
			//	}
			//	if (boss.pos_y < 1280  && pos_bitmap_boss == 2 )
			//	{
			//		if (player.y > boss.pos_y)
			//		{
			//			boss.pos_x = player.x;
			//		}
			//		boss.pos_y = boss.pos_y + boss_speed;
			//	}
			//	else if (boss.pos_y > 820 && pos_bitmap_boss == 2)
			//	{
			//		pos_bitmap_boss = 3;
			//		boss.pos_x = 1280;
			//		boss.pos_y = player.y;
			//	}

			//	/////////////////////////////////////========================== DISPAROS DEL BOSS =========================////////////////////////////
			//	if (a++ > 10)
			//	{
			//		auxxx = 0; a = 0;

			//	}
			//	if (sonido_disparos_boss++ > 20)
			//	{
			//		al_play_sample(ametralladora, 0.2, 0, 1.8, ALLEGRO_PLAYMODE_ONCE, 0);
			//		sonido_disparos_boss = 0;
			//	}
			//	
			//	if (pos_bitmap_boss == 3)
			//	{
			//		if (boss.ndisparos <= boss_max_disparos && auxxx == 0)
			//		{
			//			if (boss.pos_y > 0 && boss.pos_x > 0)
			//			{
			//				boss.ndisparos++;
			//				disparos_boss[boss.ndisparos].x = boss.pos_x - 64;
			//				disparos_boss[boss.ndisparos].y = boss.pos_y + 33;
			//				disparos_boss[boss.ndisparos].vel_x = 40;
			//				disparos_boss[boss.ndisparos].vel_y = 0;
			//				if (boss.ndisparos == 2)
			//				{
			//					al_play_sample(machine_gun, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			//				}
			//				boss.ndisparos++;
			//				disparos_boss[boss.ndisparos].x = boss.pos_x - 64;
			//				disparos_boss[boss.ndisparos].y = boss.pos_y + 160;
			//				disparos_boss[boss.ndisparos].vel_x = speed_bala;
			//				disparos_boss[boss.ndisparos].vel_y = 0;
			//				auxxx = 1;
			//			}
			//		}
			//	}
			//	
			//	for (i = 1; i < boss.ndisparos; i++)
			//	{
			//		if (disparos_boss[i].x >= 0)
			//		{
			//			disparos_boss[i].x = disparos_boss[i].x - disparos_boss[i].vel_x;
			//			al_draw_bitmap(bala1[8], disparos_boss[i].x, disparos_boss[i].y, 0);
			//		}
			//	}

			//}
			if (repara == 0)
			{
				al_draw_bitmap(llave, llave_x, llave_y, repara);
			}

			

			al_draw_bitmap(circulo_,1100 ,600 ,0);
			al_draw_bitmap(recargas, 1100, 600, 0);
			al_draw_rotated_bitmap(jugador, 100, 100, player.x, player.y, omega[orientacion_jugador] * f, 0);
			if (animacion == true)
			{
				al_draw_scaled_rotated_bitmap(disparos_[cantFrame_Disparo], al_get_bitmap_width(disparos_[cantFrame_Disparo]) / 2, al_get_bitmap_height(disparos_[cantFrame_Disparo]) / 2, animacion_x, animacion_y, 0.2, 0.2, omega[orientacion_jugador] * f, 0);

			}		
			if (vida_player >= 2)
			{
				al_draw_rotated_bitmap(fuegos[cantFrame_Fuego],40,40, player.x + 30 * sin(omega[orientacion_jugador] * f), player.y  - 30 * cos(omega[orientacion_jugador] * f),0,0);
			}
			if (vida_player >= 4)
			{
				al_draw_rotated_bitmap(fuegos[cantFrame_Fuego], 40, 40, player.x + 60 * sin(omega[orientacion_jugador] * f), player.y - 60 * cos(omega[orientacion_jugador] * f), 0, 0);

			}
			
			al_draw_bitmap(avion_[pos_bitmap_boss], boss.pos_x, boss.pos_y, 0);
			al_draw_scaled_bitmap(tabla_puntajes,0,0,al_get_bitmap_width(tabla_puntajes),al_get_bitmap_height(tabla_puntajes),900,0,2* al_get_bitmap_width(tabla_puntajes)/3,2* al_get_bitmap_height(tabla_puntajes)/3,0);
			al_draw_scaled_bitmap(racha,0,0,al_get_bitmap_width(racha),al_get_bitmap_height(racha),1025,58, 2*al_get_bitmap_width(racha)/3, 2* al_get_bitmap_height(racha)/3, 0);
			al_draw_textf(letra, negro, 940, 20, 0, "Puntaje: %d", puntajes);
			al_draw_textf(letra1, negro, 1035, 60, 0, "Racha: x%d", rachas_);
			al_draw_scaled_bitmap(vida[vida_player], 0, 0, al_get_bitmap_width(vida[vida_player]), al_get_bitmap_height(vida[vida_player]), 700, 10, 2 * al_get_bitmap_width(vida[vida_player]) / 3, 2 * al_get_bitmap_height(vida[vida_player]) / 3, 0);
			if (Evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				al_destroy_bitmap(jugador);
				al_destroy_bitmap(circulo_);
				al_destroy_bitmap(recargas);
				return 0;
			}
		}
		al_flip_display();
	}
}



struct jefe movimiento(struct jefe boss, struct jugador player)
{
	if (boss.pos_x > player.x)
	{
		boss.pos_y = player.y;
	}
	boss.pos_x = boss.pos_x - boss_speed;
	return boss;
}










