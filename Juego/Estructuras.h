struct enemy_
{
	int pos_x;
	int pos_y;
	int vel_x;
	int vel_y;
	int ndisparos = 0;

}enem[max_enemy];;

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

struct jugador
{
	int vida;
};
typedef jugador jugador_;


