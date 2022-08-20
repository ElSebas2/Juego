#include"Define.h"



void col_bala_enemigo(struct jugador player, struct enemy_ enem[max_enemy], int num_enem, int cant_disparos, struct bala_player disparos_ply[max_disparos_ply], int* ii, int* kk, int* activar_col);
struct jugador velocidades_jugador(struct jugador player, int orientacion_jugador, bool freno, int choque[16]);
struct enemy_ crear_enemgios(struct enemy_ enem[], int num_enem,int nivel_mapa);
void init();
void col_bala_jugador(struct jugador player, struct bala_ disparos[], int omega[], int orientacion_jugador, int col_jug_enem[], int ajuste, int* activar_col, int* ii);
float error_x_jugador(int omega[16], int orientacion_jugador);
float error_y_jugador(int omega[16], int orientacion_jugador);
void col_enem_jugador(struct jugador player, struct enemy_ enem[], int omega[], int orientacion_jugador, int num_enem, int ajuste, int col_jug_enem[], int* activar_col, int* ii);
struct bala_ crear_balas(struct bala_ disparos[], struct enemy_ enem[], int j,int nivel_mapa);
void reset_enem(struct enemy_ enem[]);
void reset_disparos(struct bala_ disparos[]);










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
struct enemy_ crear_enemgios(struct enemy_ enem[], int num_enem,int nivel_mapa)
{
	switch (nivel_mapa)
	{
	case 0:
		enem[num_enem].pos_x = 50 + rand() % 300;
		enem[num_enem].pos_y = 800;
		enem[num_enem].vel_x = 0;
		enem[num_enem].vel_y = -vel_enemy;
		enem[num_enem].ndisparos = 0;
		enem[num_enem].flag = 0;
		enem[num_enem].angulo = 0;
		break;
	case 1:
		enem[num_enem].pos_x = 900 + rand() % 300;
		enem[num_enem].pos_y = 0;
		enem[num_enem].vel_x = 0;
		enem[num_enem].vel_y = vel_enemy;
		enem[num_enem].ndisparos = 0;
		enem[num_enem].flag = 0;
		enem[num_enem].angulo = 180 * f;
		break;
	case 2: 
		enem[num_enem].pos_x = (50 + rand() % 300) - (50 + rand() % 300);
		enem[num_enem].pos_y = 720;
		enem[num_enem].vel_x = vel_enemy;
		enem[num_enem].vel_y = 0;
		enem[num_enem].ndisparos = 0;
		enem[num_enem].flag = 0;
		enem[num_enem].angulo = 45 * f;
		break;
	}
	return enem[num_enem];

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
void col_bala_enemigo(struct jugador player, struct enemy_ enem[max_enemy], int num_enem, int cant_disparos, struct bala_player disparos_ply[max_disparos_ply], int* ii, int* kk,int *activar_col)
{
	*activar_col = 0;
	for (int k = 1; k <= num_enem; k++)
	{
		for (int i = 0; i <= cant_disparos; i++)
		{
			if (player.disparos_ply[i].pos_x >= enem[k].pos_x - 20 && player.disparos_ply[i].pos_x <= enem[k].pos_x + 20)
			{
				if (player.disparos_ply[i].pos_y >= enem[k].pos_y - 75 && player.disparos_ply[i].pos_y <= enem[k].pos_y + 75 )
				{
					player.disparos_ply[i].pos_y = 2000;
					player.disparos_ply[i].pos_x = 2000;
					player.disparos_ply[i].vel_x = 0;
					player.disparos_ply[i].vel_y = 0;
					*activar_col = 1;
					*ii = i;
					*kk = k;

				}
				
			}
		}
	}	
}
void col_bala_jugador(struct jugador player,struct bala_ disparos[], int omega[], int orientacion_jugador, int col_jug_enem[], int ajuste,int* activar_col, int* ii)
{
	*activar_col = 0;

	for (int i = 1; i <= max_disparos; i++)
	{
		
		if (disparos[i].x <= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && disparos[i].x >= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
		{
			if (disparos[i].y >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && disparos[i].y <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
			{
				*activar_col = 1;
				*ii = i;

			}
		}
		
	}
}
void col_enem_jugador(struct jugador player, struct enemy_ enem[], int omega[], int orientacion_jugador, int num_enem, int ajuste, int col_jug_enem[], int* activar_col, int* ii)
{
	*activar_col = 0;

	for (int i = 1; i <= num_enem; i++)
	{
		if (enem[i].pos_x + 20 - 75 * sin(enem[i].angulo) <= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && enem[i].pos_x - 20 + 75 * sin(enem[i].angulo) >= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
		{
			if (enem[i].pos_y + 75 * cos(enem[i].angulo) >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && enem[i].pos_y - 75 * cos(enem[i].angulo) <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
			{
				*activar_col = 1;
				*ii = i;
			}
		}
	}

}
struct bala_ crear_balas(struct bala_ disparos[], struct enemy_ enem[], int j,int nivel_mapa)
{
	switch (nivel_mapa)
	{
	case 0:
		disparos[enem[j].ndisparos].x = enem[j].pos_x;
		disparos[enem[j].ndisparos].y = enem[j].pos_y - 39;
		disparos[enem[j].ndisparos].vel_x = speed_bala;
		disparos[enem[j].ndisparos].vel_y = 0;
		disparos[enem[j].ndisparos].angulo = 0;
		break;
	case 1:
		disparos[enem[j].ndisparos].x = enem[j].pos_x;
		disparos[enem[j].ndisparos].y = enem[j].pos_y + 39;
		disparos[enem[j].ndisparos].vel_x = -speed_bala;
		disparos[enem[j].ndisparos].vel_y = 0;
		disparos[enem[j].ndisparos].angulo = 180*f;

	}
	


	return disparos[enem[j].ndisparos];
	
}
void reset_disparos(struct bala_ disparos[])
{
	int i;
	for (i = 0; i < max_disparos; i++)
	{
		disparos[i].vel_x = 0;
		disparos[i].vel_y = 0;
		disparos[i].x = 0;
		disparos[i].y = 0;

	}
}
void reset_enem(struct enemy_ enem[])
{
	int i;
	for (i = 0; i < max_enemy; i++)
	{
		enem[i].ndisparos = 0;
		enem[i].pos_x = 0;
		enem[i].pos_y = 0;
		enem[i].vel_x = 0;
		enem[i].vel_y = 0;
		enem[i].ndisparos = 0;
		enem[i].flag = 0;
	}
	
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

