#include "kernel.h"
#include "keyboard.h"
#include "utils.h"
#include "types.h"
#include "box.h"
#include "tic.h"

#define PLAYER_1 1
#define PLAYER_2 2

uint8 grid[3][3];
uint8 row = 0, col = 0;
uint8 turn = PLAYER_1;

uint16 player_1_moves = 0;
uint16 player_2_moves = 0;

uint16 grid_inner_box_x = 30;
uint16 grid_inner_box_y = 2;
uint8 player_1_cell_color = BRIGHT_RED;
uint8 player_2_cell_color = BRIGHT_BLUE;

bool error = FALSE;

void update_cells()
{
  if(grid[0][0] == PLAYER_1){
    fill_box(NULL, 30, 2, 10, 5, player_1_cell_color);
  }else if(grid[0][0] == PLAYER_2){
    fill_box(NULL, 30, 2, 10, 5, player_2_cell_color);
  }
  if(grid[0][1] == PLAYER_1){
    fill_box(NULL, 43, 2, 10, 5, player_1_cell_color);
  }else if(grid[0][1] == PLAYER_2){
    fill_box(NULL, 43, 2, 10, 5, player_2_cell_color);
  }
  if(grid[0][2] == PLAYER_1){
    fill_box(NULL, 56, 2, 10, 5, player_1_cell_color);
  }else if(grid[0][2] == PLAYER_2){
    fill_box(NULL, 56, 2, 10, 5, player_2_cell_color);
  }
  if(grid[1][0] == PLAYER_1){
    fill_box(NULL, 30, 9, 10, 5, player_1_cell_color);
  }else if(grid[1][0] == PLAYER_2){
    fill_box(NULL, 30, 9, 10, 5, player_2_cell_color);
  }
  if(grid[1][1] == PLAYER_1){
    fill_box(NULL, 43, 9, 10, 5, player_1_cell_color);
  }else if(grid[1][1] == PLAYER_2){
    fill_box(NULL, 43, 9, 10, 5, player_2_cell_color);
  }
  if(grid[1][2] == PLAYER_1){
    fill_box(NULL, 56, 9, 10, 5, player_1_cell_color);
  }else if(grid[1][2] == PLAYER_2){
    fill_box(NULL, 56, 9, 10, 5, player_2_cell_color);
  }
  if(grid[2][0] == PLAYER_1){
    fill_box(NULL, 30, 16, 10, 5, player_1_cell_color);
  }else if(grid[2][0] == PLAYER_2){
    fill_box(NULL, 30, 16, 10, 5, player_2_cell_color);
  }
  if(grid[2][1] == PLAYER_1){
    fill_box(NULL, 43, 16, 10, 5, player_1_cell_color);
  }else if(grid[2][1] == PLAYER_2){
    fill_box(NULL, 43, 16, 10, 5, player_2_cell_color);
  }
  if(grid[2][2] == PLAYER_1){
    fill_box(NULL, 56, 16, 10, 5, player_1_cell_color);
  }else if(grid[2][2] == PLAYER_2){
    fill_box(NULL, 56, 16, 10, 5, player_2_cell_color);
  }
}


void draw_game_board()
{

  draw_box(BOX_SINGLELINE, 28, 1, 38, 20, WHITE, BLACK);

  draw_box(BOX_SINGLELINE, 28, 1, 12, 6, WHITE, BLACK);
  draw_box(BOX_SINGLELINE, 41, 1, 12, 6, WHITE, BLACK);
  draw_box(BOX_SINGLELINE, 54, 1, 12, 6, WHITE, BLACK);

  draw_box(BOX_SINGLELINE, 28, 8, 12, 6, WHITE, BLACK);
  draw_box(BOX_SINGLELINE, 41, 8, 12, 6, WHITE, BLACK);
  draw_box(BOX_SINGLELINE, 54, 8, 12, 6, WHITE, BLACK);

  draw_box(BOX_SINGLELINE, 28, 15, 12, 6, WHITE, BLACK);
  draw_box(BOX_SINGLELINE, 41, 15, 12, 6, WHITE, BLACK);
  draw_box(BOX_SINGLELINE, 54, 15, 12, 6, WHITE, BLACK);

  update_cells();
  
  fill_box(NULL, grid_inner_box_x, grid_inner_box_y, 10, 5, WHITE);

  draw_box(BOX_SINGLELINE, 0, 2, 18, 3, GREY, BLACK);

  gotoxy(0, 0);
  print_color_string("jogo da velha", YELLOW, BLACK);

  gotoxy(1, 3);
  print_color_string("VEZ DO JOGADOR 1: ", BRIGHT_RED, BLACK);
  print_int(player_1_moves);

  gotoxy(1, 5);
  print_color_string("VEZ DO JOGADOR 2: ", BRIGHT_BLUE, BLACK);
  print_int(player_2_moves);

  gotoxy(1, 7);
  print_color_string("VEZ: ", CYAN, BLACK);
  gotoxy(8, 7);
  if(turn == PLAYER_1){
    print_color_string("JOGADOR 1", BRIGHT_CYAN, BLACK);
  }else{
    print_color_string("JOGADOR 2", BRIGHT_CYAN, BLACK);
  }

  draw_box(BOX_SINGLELINE, 0, 9, 18, 8, GREY, BLACK);

  gotoxy(1, 9);
  print_color_string("TECLAS", WHITE, BLACK);

  gotoxy(1, 11);
  print_color_string("SETAS", WHITE, BLACK);

  gotoxy(12, 10);
  print_char(30);

  gotoxy(10, 11);
  print_char(17);

  gotoxy(14, 11);
  print_char(16);

  gotoxy(12, 12);
  print_char(31);

  gotoxy(2, 14);
  print_color_string("USE ESPACO PARA MARCAR", WHITE, BLACK);
  gotoxy(1, 16);
  print_color_string("MOVA O QUADRADO BRANCO", GREY, BLACK);
  gotoxy(1, 17);
  print_color_string(" PARA SELECIONAR O LOCAL", GREY, BLACK);

  if(error == TRUE){
    gotoxy(1, 20);
    print_color_string("JA SELECIONADO", RED, BLACK);
    error = FALSE;
  }
}

int get_winner() {
    int i, j;
    int total_moves = 0;

    // Verifica todas as linhas, colunas e diagonais para um vencedor
    for (i = 0; i < 3; i++) {
        // Verifica linhas
        if ((grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) && grid[i][0] != 0) {
            return grid[i][0];
        }
        // Verifica colunas
        if ((grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) && grid[0][i] != 0) {
            return grid[0][i];
        }
    }

    // Verifica diagonais
    if ((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) && grid[0][0] != 0) {
        return grid[0][0];
    }
    if ((grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2]) && grid[2][0] != 0) {
        return grid[2][0];
    }

    // Conta o número de movimentos para determinar se o tabuleiro está cheio
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (grid[i][j] != 0) {
                total_moves++;
            }
        }
    }

    // Se o total de movimentos for 9 e não houver vencedor, é empate
    if (total_moves == 9) {
        return -1;  // Código para empate, pode ajustar conforme necessário
    }

    return 0;  // Retorna 0 se não houver vencedor ainda e ainda existem movimentos possíveis
}

void restore_game_data_to_default()
{
  uint8 i,j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      grid[i][j] = 0;
    }
  }

  row = 0;
  col = 0;
  turn = PLAYER_1;

  player_1_moves = 0;
  player_2_moves = 0;

  grid_inner_box_x = 30;
  grid_inner_box_y = 2;
}

void launch_game()
{
  byte keycode = 0;
  restore_game_data_to_default();

  draw_game_board();
  
  do{
    keycode = get_input_keycode();
    switch(keycode){

      case KEY_RIGHT :
        if(grid_inner_box_x <= 43){
          grid_inner_box_x += 13;
          col++;
        }
        break;

      case KEY_LEFT :
        if(grid_inner_box_x >= 43){
          grid_inner_box_x -= 13;
          col--;
        }else{
          grid_inner_box_x = 30;
          col = 0;
        }
        break;

      case KEY_DOWN :
        if(grid_inner_box_y <= 9){
          grid_inner_box_y += 7;
          row++;
        }
        break;

      case KEY_UP :
        if(grid_inner_box_y >= 9){
          grid_inner_box_y-= 7;
          row--;
        }
        break;

      case KEY_SPACE :
        if(grid[row][col] > 0)
          error = TRUE;

        if(turn == PLAYER_1){
          grid[row][col] = PLAYER_1;
          player_1_moves++;
          turn = PLAYER_2;
        }else if(turn == PLAYER_2){
          grid[row][col] = PLAYER_2;
          player_2_moves++;
          turn = PLAYER_1;
        }
        break;
    }
    clear_screen(WHITE, BLACK);
    draw_game_board();
    if(player_1_moves == 3 && player_2_moves == 3){
      if(get_winner() == PLAYER_1){
        draw_box(BOX_DOUBLELINE, 3, 20, 16, 1, BRIGHT_GREEN, BLACK);
        gotoxy(6, 21);
        print_color_string("JOGADOR 1 VENCEU", BRIGHT_GREEN, BLACK);
      }else if(get_winner() == PLAYER_2){
        draw_box(BOX_DOUBLELINE, 3, 20, 16, 1, BRIGHT_GREEN, BLACK);
        gotoxy(6, 21);
        print_color_string("JOGADOR  2 VENCEU", BRIGHT_GREEN, BLACK);
      }else{
        draw_box(BOX_DOUBLELINE, 3, 20, 16, 1, CYAN, BLACK);
        gotoxy(6, 21);
        print_color_string("NINGUEM VENCE", BRIGHT_CYAN, BLACK);
      }
    }
    if(player_1_moves + player_2_moves == 9)
      return;
    
    //change sleep value if game is working so fast or slow
    sleep(0x04FFFFFF);
  }while(keycode > 0);
}