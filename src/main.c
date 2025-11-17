#include <raylib.h>
#include <stddef.h>

const int screenWidth = 800;
const int screenHeight = 600;

enum { WHITE_KING = 1, WHITE_QUEEN, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK, WHITE_PAWN,
        BLACK_KING, BLACK_QUEEN, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK, BLACK_PAWN };

Texture2D boardTexture;
Texture2D piecesTexture;

Rectangle piecesRects[12] = { 0 };
int board[8][8] = { 0 };

void drawPiece(int piece,int rank, int file){
    if (rank < 1 || rank > 8 || file < 1 || file > 8 || piece < 1 || piece > 12)
    {
        return;
    }
    
    Rectangle source = piecesRects[piece-1];
    Rectangle dest = (Rectangle){ (file - 1) * 60.0f + 20.0f, ((7-(rank - 1)) * 60.0f) + 20.0f, 60.0f, 60.0f };
    DrawTexturePro(
        piecesTexture, 
        source, 
        dest, 
        (Vector2){ 0.0f, 0.0f }, 
        0.0f, 
        WHITE);
};
void drawBoard(){
    for (int rank = 1; rank <= 8; rank++)
    {
        for (int file = 1; file <= 8; file++)
        {
            int piece = board[rank - 1][file - 1];
            if (piece != 0)
            {
                drawPiece(piece, rank, file);
            }
        }
    }    
}

void initGame(){
    InitWindow(screenWidth, screenHeight, "Chess Game!");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    piecesTexture = LoadTexture("assets/images/chess_pieces.png");        // Texture loading
    boardTexture = LoadTexture("assets/images/brown_chessboard.png");        // Texture loading

    // Define rectangles for each chess piece in the texture atlas
    // The texture atlas is assumed to be a 1998x666 image with 2 rows of 6 pieces each
    // Each piece is 333x333 pixels, and the atlas is arranged as follows:
    // Row 1: White King, White Queen, White Bishop, White Knight, White Rook, White Pawn
    // Row 2: Black King, Black Queen, Black Bishop, Black Knight, Black Rook, Black Pawn
    for (int i = 0; i < 12; i++)
    {
        int row = i / 6; // 0 for white pieces, 1 for black pieces
        int col = i % 6; // Column index in the row
        piecesRects[i] = (Rectangle){ col * 333.0f, row * 333.0f, 333.0f, 333.0f };
    }
    
    // Initialize new game position
    board[0][0] = board[0][7] = WHITE_ROOK;
    board[0][1] = board[0][6] = WHITE_KNIGHT;
    board[0][2] = board[0][5] = WHITE_BISHOP;
    board[0][3] = WHITE_QUEEN;
    board[0][4] = WHITE_KING;
    for (int file = 0; file < 8; file++)
    {
        board[1][file] = WHITE_PAWN;
        board[6][file] = BLACK_PAWN;
    }
    board[7][0] = board[7][7] = BLACK_ROOK;
    board[7][1] = board[7][6] = BLACK_KNIGHT;
    board[7][2] = board[7][5] = BLACK_BISHOP;
    board[7][3] = BLACK_QUEEN;
    board[7][4] = BLACK_KING;
    

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
}
void updateGame(){}
void drawGame(){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexturePro(
        boardTexture, 
        (Rectangle){ 0.0f, 0.0f, 2048, 2048 }, 
        (Rectangle){ 20.0f, 20.0f, 480.0f, 480.0f }, 
        (Vector2){ 0.0f, 0.0f }, 
        0.0f, 
        WHITE);

    drawBoard();
    EndDrawing();
}
void unloadGame(){
    UnloadTexture(piecesTexture);   // Unload texture
    UnloadTexture(boardTexture);   // Unload texture
}

int main(void)
{
    // Initialization
    initGame();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        updateGame();

        // Draw
        drawGame();
    }

    unloadGame();

    CloseWindow();                // Close window and OpenGL context

    return 0;
}