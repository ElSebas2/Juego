#include"Define.h"



int col_bala_enemigo(struct jugador player, struct enemy_ enem[max_enemy], int num_enem, int cant_disparos, struct bala_player disparos_ply[max_disparos_ply]);
struct jugador velocidades_jugador(struct jugador player, int orientacion_jugador, bool freno, int choque[16]);
struct enemy_* crear_enemgios(struct enemy_ enem[max_enemy], int num_enem);
void init();
float error_x_jugador(int omega[16], int orientacion_jugador);
float error_y_jugador(int omega[16], int orientacion_jugador);







void init()
{
	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
}
struct enemy_* crear_enemgios(struct enemy_ enem[max_enemy], int num_enem)
{
	enem[num_enem].pos_x = 50 + rand() % 300;
	enem[num_enem].pos_y = 720;
	enem[num_enem].vel_x = 0;
	enem[num_enem].vel_y = vel_enemy;
	enem[num_enem].ndisparos = 0;
	

	return enem;
}
struct jugador velocidades_jugador(struct jugador player, int orientacion_player, bool freno, int choque[16])
{
	if (freno == false)
	{
		if (choque[orientacion_player] == 0)
		{
			player.y = player.y - player.vel_y[orientacion_player];
			player.x = player.x + player.vel_x[orientacion_player];
			return player;
		}
	}
}
int col_bala_enemigo(struct jugador player, struct enemy_ enem[max_enemy], int num_enem, int cant_disparos, struct bala_player disparos_ply[max_disparos_ply])
{
	for (int k = 1; k <= num_enem; k++)
	{
		for (int i = 0; i <= cant_disparos; i++)
		{
			if (player.disparos_ply[i].pos_x >= enem[k].pos_x + 57 && player.disparos_ply[i].pos_x <= enem[k].pos_x + 97)
			{
				if (player.disparos_ply[i].pos_y >= enem[k].pos_y && player.disparos_ply[i].pos_y <= enem[k].pos_y + 157)
				{
					player.disparos_ply[i].pos_y = 2000;
					player.disparos_ply[i].pos_x = 2000;
					player.disparos_ply[i].vel_x = 0;
					player.disparos_ply[i].vel_y = 0;
					return 1;
				}
				
			}
		}
	}
	return 0;
}
float error_x_jugador(int omega[16], int orientacion_jugador)
{
	float error_x;
	if (omega[orientacion_jugador] == 0 || omega[orientacion_jugador] == 90 || omega[orientacion_jugador] == 180 || omega[orientacion_jugador] == 270)
	{
		error_x = 30 * cos(omega[orientacion_jugador] * f);
	}
	else
	{
		error_x = 0;
	}
	return error_x;
}
float error_y_jugador(int omega[16], int orientacion_jugador)
{
	float error_y;
	if (omega[orientacion_jugador] == 0 || omega[orientacion_jugador] == 90 || omega[orientacion_jugador] == 180 || omega[orientacion_jugador] == 270)
	{
		error_y = 30 * sin(omega[orientacion_jugador] * f);
	}
	else
	{
		error_y = 0;
	}
	return error_y;
}

void cargar_mapa(char nombre[10], char **mapa)
{
	char basura;
	int i, j;
	FILE* archivo;
	archivo = fopen(nombre, "r");

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fscanf(archivo, "%c", &mapa[i][j]);
		}
		fscanf(archivo, "%c", &basura);
	}
	fclose(archivo);
}

