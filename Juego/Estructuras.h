struct enemy_
{
	int vida = 0;
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
};

struct jugador
{
	int x = 700;
	int y = 700;
	int vel_x;
	int vel_y;
	int vida = 0;
	struct bala_player disparos_ply[max_disparos_ply];
}player;
typedef jugador jugador_;

struct jefe
{
	int vida = 10;
	int pos_x;
	int pos_y;
	int vel_x;
	int vel_y;
	int ndisparos;

}boss;


