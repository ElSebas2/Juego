#include <stdio.h>
#include <string>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <Windows.h>
#include <math.h>
#define speed_x 4
#define speed_y 4
#define pi 3.141592
#define speed_bala 20
#define n_balas 2
#define f pi/180
#define max_disparos 20
#define max_disparos_ply 3
#define pos 16
#define vel_enemy 5
#define max_enemy 10

int main()
{
	struct enemy_
	{
		int pos_x;
		int pos_y;
		int vel_x;
		int vel_y;
		int ndisparos;

	}enem[max_enemy];

	struct bala_  
	{
		int x;
		int y;
		int vel_x;
		int vel_y;
	}disparos[max_disparos];

	struct bala_player
	{
		int pos_x;
		int pos_y;
		int vel_x;
		int vel_y;
	}disparos_ply[max_disparos_ply];

		
	int i;
	int aux = 0;
	int b = -1;
	int contt = 1;
	int contt_ = 1;
	bool fuego = false;
	bool freno = true;
	bool disparo = false;
	//int x1, y1;
	float vel_x[16];
	float vel_y[16];
	int aux1 = 0;
	int k;
	int omega [16];
	int recarga_ = 0;
	int cont = 0;
	int cont1[max_disparos];
	int	cont2 = 0;
	int cant_disparos = 0;
	int enemy_x = 200, enemy_y = 1080;
	float pos_x_bala[16];
	float pos_y_bala[16];
	float segundo = 0;
	float pos_y_bala2 = 1;
	float pos_x_bala2 = 1;
	float x = 800, y = 600;
	int borrar = 0;

	const char* fuego1 = "Imagenes/Frame/fuego1.png";
	const char* fuego2 = "Imagenes/Frame/fuego2.png";
	const char* fuego3 = "Imagenes/Frame/fuego3.png";
	const char* fuego4 = "Imagenes/Frame/fuego4.png";
	const char* fuego5 = "Imagenes/Frame/fuego5.png";
	
	const char* p0 = "Imagenes/Rotaciones/A0.png";
	const char* p1 = "Imagenes/Rotaciones/A1.png";
	const char* p2 = "Imagenes/Rotaciones/A2.png";
	const char* p3 = "Imagenes/Rotaciones/A3.png";
	const char* p4 = "Imagenes/Rotaciones/A4.png";
	const char* p5 = "Imagenes/Rotaciones/A5.png";
	const char* p6 = "Imagenes/Rotaciones/A6.png";
	const char* p7 = "Imagenes/Rotaciones/A7.png";
	const char* p8 = "Imagenes/Rotaciones/A8.png";
	const char* p9 = "Imagenes/Rotaciones/A9.png";
	const char* p10 = "Imagenes/Rotaciones/A10.png";
	const char* p11 = "Imagenes/Rotaciones/A11.png";
	const char* p12 = "Imagenes/Rotaciones/A12.png";
	const char* p13 = "Imagenes/Rotaciones/A13.png";
	const char* p14 = "Imagenes/Rotaciones/A14.png";
	const char* p15 = "Imagenes/Rotaciones/A15.png";

	const char* hitbox1 = "Imagenes/Rotaciones/hitbox.png";

	const char* bala_arriba = "Imagenes/Rotaciones_bala/BalaArriba.png";
	const char* bala22 = "Imagenes/Rotaciones_bala/bala 22.png";
	const char* bala44 = "Imagenes/Rotaciones_bala/bala 44.png";
	const char* bala68 = "Imagenes/Rotaciones_bala/bala 66.png";
	const char* bala_abajo = "Imagenes/Rotaciones_bala/BalaAbajo.png";
	const char* bala112 = "Imagenes/Rotaciones_bala/bala 112.png";
	const char* bala134 = "Imagenes/Rotaciones_bala/bala 134.png";
	const char* bala156 = "Imagenes/Rotaciones_bala/bala 156.png";
	const char* bala_derecha = "Imagenes/Rotaciones_bala/BalaDerecha.png";
	const char* bala202 = "Imagenes/Rotaciones_bala/bala 202.png";
	const char* bala224 = "Imagenes/Rotaciones_bala/bala 224.png";
	const char* bala246 = "Imagenes/Rotaciones_bala/bala 246.png";
	const char* bala_izquierda = "Imagenes/Rotaciones_bala/BalaIzquierda.png";
	const char* bala292 = "Imagenes/Rotaciones_bala/bala 292.png";
	const char* bala314 = "Imagenes/Rotaciones_bala/bala 314.png";
	const char* bala336 = "Imagenes/Rotaciones_bala/bala 336.png";
	const char* nulo = "Imagenes/Rotaciones_bala/+.png";

	const char* bala1_4 = "Imagenes/Recarga/bala 1,4.png";
	const char* bala2_4 = "Imagenes/Recarga/bala 2,4.png";
	const char* bala3_4 = "Imagenes/Recarga/bala 3,4.png";
	const char* bala_completa = "Imagenes/Recarga/bala completa.png";
	const char* circulo = "Imagenes/Recarga/circulo.png";
	const char* isla_ = "Imagenes/Isla.png";
	const char* enemy1_ = "Imagenes/Enemigos/enemy.png";
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_init_primitives_addon();
	int ancho = GetSystemMetrics(SM_CXSCREEN);
	int alto = GetSystemMetrics(SM_CYSCREEN);

	ALLEGRO_EVENT_QUEUE* cola = al_create_event_queue();
	ALLEGRO_BITMAP* fondo = al_load_bitmap("Imagenes/fondo.jpg");
	ALLEGRO_BITMAP* a0[16] = { al_load_bitmap(p0), al_load_bitmap(p1),al_load_bitmap(p2), al_load_bitmap(p3), al_load_bitmap(p4), al_load_bitmap(p5), al_load_bitmap(p6), al_load_bitmap(p7), al_load_bitmap(p8), al_load_bitmap(p9), al_load_bitmap(p10), al_load_bitmap(p11), al_load_bitmap(p12),al_load_bitmap(p13), al_load_bitmap(p14),al_load_bitmap(p15)};
	ALLEGRO_BITMAP* bala1[17] = {al_load_bitmap(bala_derecha), al_load_bitmap(bala112), al_load_bitmap(bala134), al_load_bitmap(bala156), al_load_bitmap(bala_abajo), al_load_bitmap(bala202), al_load_bitmap(bala224), al_load_bitmap(bala246), al_load_bitmap(bala_izquierda), al_load_bitmap(bala292), al_load_bitmap(bala314), al_load_bitmap(bala336),al_load_bitmap(bala_arriba),al_load_bitmap(bala22),al_load_bitmap(bala44),al_load_bitmap(bala68),al_load_bitmap(nulo)};
	ALLEGRO_BITMAP* circulo_ = al_load_bitmap(circulo);
	ALLEGRO_BITMAP* recargas = al_load_bitmap(bala_completa);
	ALLEGRO_BITMAP* enemy1 = al_load_bitmap(enemy1_);
	ALLEGRO_BITMAP* fuegos[6] = { al_load_bitmap(fuego1),al_load_bitmap(fuego2) ,al_load_bitmap(fuego3) ,al_load_bitmap(fuego4) ,al_load_bitmap(fuego5),al_load_bitmap(nulo)};
	ALLEGRO_BITMAP* hitbox = al_load_bitmap(hitbox1);
	ALLEGRO_BITMAP* isla = al_load_bitmap(isla_);
	ALLEGRO_BITMAP* isla_2 = al_load_bitmap("Imagenes/Isla2.png");
	ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
	ALLEGRO_DISPLAY* ventana = al_create_display(ancho, alto);
	ALLEGRO_TIMER* seg = al_create_timer(1/10.0);
	ALLEGRO_TIMER* recarga = al_create_timer(1.0);
	al_set_window_title(ventana, "Battleship 1945");
	al_set_window_position(ventana, 0, 0);

	al_register_event_source(cola, al_get_keyboard_event_source());
	al_register_event_source(cola, al_get_timer_event_source(seg));
	al_register_event_source(cola, al_get_timer_event_source(recarga));
	al_register_event_source(cola, al_get_mouse_event_source());
	printf("Ancho: %d\n", ancho);
	printf("Alto: %d", alto);
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
		omega[k] = 22*k;
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
		vel_y[k] = (speed_y * cos(omega[k] * f));
		vel_x[k] = (speed_x * sin(omega[k] * f));
	}



	ALLEGRO_EVENT Evento;
	while (true)
	{
		al_draw_bitmap(fondo, 0, 0, 0);
		al_draw_bitmap(isla, 1300, 500, 0);
		al_draw_bitmap(isla_2, 1000, 200, 0);
		al_wait_for_event(cola, &Evento);

		/*//==============     CARGAR POSICIONES DEL JUGADOR     =============================//*/

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
			y = y - vel_y[cont];
			x = x + vel_x[cont];
		}
		/*if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x1 = Evento.mouse.x;
			y1 = Evento.mouse.y;
			if (Evento.mouse.button & 1)
			{
				printf("\n X = %d\n", x1);
				printf("Y = %d", y1);
			}
		}*/
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
					else if((omega[cont1[cant_disparos]] >= 112 && omega[cont1[cant_disparos]] <= 134))
					{
						disparos_ply[cant_disparos].pos_y = y + 53 * cos(omega[cont1[cant_disparos]] * f) + 130;
					}
					else if((omega[cont1[cant_disparos]] >= 156 && omega[cont1[cant_disparos]] <= 180))
					{
						disparos_ply[cant_disparos].pos_y = y + 53 * cos(omega[cont1[cant_disparos]] * f) + 170;
					}
					else if((omega[cont1[cant_disparos]] >= 202 && omega[cont1[cant_disparos]] <= 224))
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
					
				}

			}
		}
		if (cant_disparos > 0)
		{
			for (i = 0; i < cant_disparos; i++)
			{
				disparos_ply[i].pos_x = disparos_ply[i].pos_x + disparos_ply[i].vel_x;
				disparos_ply[i].pos_y = disparos_ply[i].pos_y + disparos_ply[i].vel_y;
				al_draw_bitmap(bala1[cont1[i]], disparos_ply[i].pos_x, disparos_ply[i].pos_y, 0);

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
				segundo = segundo + 0.1;
			}
		}
		if (aux1 == 0 && b < max_enemy)
		{
			b++;
			enem[b].pos_x = 50 + rand() % 300;
			enem[b].pos_y = 1080;
			enem[b].vel_x = 0;
			enem[b].vel_y = vel_enemy;
			enem[b].ndisparos = 0;
			aux1 = 1;
		}

		if (cont2++ > 220)
		{
			aux1 = 0; cont2 = 0;
		}

		if (b > 0)
		{
			for (i = 1; i < max_enemy; i++)
			{
				if (enem[i].pos_y != -150 && enem[i].pos_y > -150)
				{
					enem[i].pos_y = enem[i].pos_y - enem[i].vel_y;
					al_draw_bitmap(enemy1, enem[i].pos_x, enem[i].pos_y, 0);
				}
			}		
		}


		if (segundo > 2 && aux == 0)
		{
			if (enem[b].ndisparos <= max_disparos)
			{
				enem[b].ndisparos++;
				disparos[enem[b].ndisparos].x = enem[b].pos_x + 97;
				disparos[enem[b].ndisparos].y = enem[b].pos_y + 39;

				disparos[enem[b].ndisparos].vel_x = 20;
				disparos[enem[b].ndisparos].vel_y = 0;

				aux = 1;
			}
			
		}
		
		if (contt++ > 30)
		{
			aux = 0; contt = 0;
		}
	
		
		if (enem[b].ndisparos > 0 && enem[b].ndisparos < max_disparos)
		{
			for (i = 1; i <= enem[b].ndisparos; i++)
			{
				disparos[i].x = disparos[i].x + disparos[i].vel_x;
				if (disparos[i].x >= enem[b].pos_x && disparos[i].x <= 1980)
				{
					al_draw_bitmap(bala1[0], disparos[i].x, disparos[i].y, 0);
				}
			}
		}

		//==================   COLISION BALA-----ENEMIGO   =================//
		if (cant_disparos > 0)
		{
			for (k = 0; k < max_enemy; k++)
			{
				for (i = 0; i <= cant_disparos; i++)
				{
					if (disparos_ply[i].pos_x >= enem[k].pos_x + 57 && disparos_ply[i].pos_x <= enem[k].pos_x + 97)
					{
						if (disparos_ply[i].pos_y >= enem[k].pos_y && disparos_ply[i].pos_y <= enem[k].pos_y + 157)
						{
							cont1[i] = 16;
						}
					}
				}
			}
			
		}

		//====================	COLISION BALA-------JUGADOR	================//
	
		for (i = 1; i <= enem[b].ndisparos; i++)
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
		//====================	FRAME FUEGO	====================//

		al_draw_bitmap(circulo_, 914, 933, 0);
		al_draw_bitmap(recargas, 914, 933, 0);	
		al_draw_bitmap(a0[cont], x, y, 0);
		al_flip_display();
		if (Evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			al_destroy_bitmap(a0[cont]);
			al_destroy_bitmap(circulo_);
			al_destroy_bitmap(recargas);
			return 0;
		}
	}
}
		
		
	
	

