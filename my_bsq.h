//
// Created by Kendra Moore on 10/17/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef BSQ_MY_BSQ_H
#define BSQ_MY_BSQ_H


#define MAX_SIZE 1000
#define READLINE_READ_SIZE 1024

typedef struct {
    char grid[MAX_SIZE][MAX_SIZE];
    int rows;
    int cols;
} Board;

typedef struct {
    int dp[MAX_SIZE][MAX_SIZE];
    char* buffer;
} Datam;

typedef struct {
    Board board;
    Datam data;
} Result_Metadata;


void *my_memset(void *pointer, char c, int size);
int my_strlen(const char* param);
char *my_strcat(char *dest, const char *src);
char *my_strcpy(char *dest, const char *src);
char *get_buffer();
void init_my_readline();
int find_newline(int size);
bool is_newline(int size);
char* my_readline(int fd);
void restart_readline();
int min(int first, int second, int third);
void init_result(Result_Metadata* result);
void free_result(Result_Metadata* result);
int read_file(char* filename);
int read_num_from_file (int fd,  Result_Metadata* result);
int read_board_rows(int fd,  Result_Metadata* result);
int read_board(int fd,  Result_Metadata* result);
void print_board(const Board* board);
void largest_square(Result_Metadata* result);
int my_atoi(const char *str);
int main(int argc, char* argv[]);


#endif


