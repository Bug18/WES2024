typedef enum
{
    GAME_ENDED,
    GAME_ONGOING,
    GAME_WON,
    INVALID_MOVE
} game_status;

typedef enum{
    SERVER,
    DEVICE
} player;

void startGame(char start);
bool gameWon(void);
bool gameEnded();
game_status makeMove(char letter, int position);
player getCurrentPlayer();
