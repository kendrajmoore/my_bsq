#include "my_bsq.h"

void *my_memset(void *pointer, char c, int size){
    char* pointer_to_char = (char*)pointer;
    for(int i = 0; i < size; i++)
    {
        pointer_to_char[i] = c;
    }
    return pointer;
}

int my_strlen(const char* param) {
    int length = 0;
    while(*param != '\0')
    {
        length++;
        param++;
    }
    return length;
}

char *my_strcat(char *dest, const char *src) {
    char *original_dest = dest;
    while(*dest)
    {
        dest++;
    }
    while(*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original_dest;
}

char *my_strcpy(char *dest, const char *src) {
    char *old_dest = dest;
    while(*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return old_dest;
}

int my_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
        i++;
    }

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}




char* buffer;

void restart_readline(){
    if(buffer != NULL){
        free(buffer);
        buffer = NULL;
    }
}


char *get_buffer()
{
    return buffer;
}

void init_my_readline()
{
    if(buffer != NULL)
    {
        free(buffer);
    }
    buffer = malloc(sizeof(char) * READLINE_READ_SIZE);
    if(buffer != NULL)
    {
        my_memset(buffer, '\0', READLINE_READ_SIZE);
        get_buffer();
    }
}




int resize_buffer(int size)
{
    int buffer_size = my_strlen(buffer) + 1;
    char tmp_buffer[buffer_size];
    int total_size = size + buffer_size;
    my_strcpy(tmp_buffer, buffer);
    free(buffer);
    buffer = malloc(total_size + 1);
    my_strcpy(buffer, tmp_buffer);
    buffer[buffer_size] = '\0';
    return size + buffer_size;
}

int find_newline(int size) {
    for (int i = 0; i < size - 1; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\0') {
            return i;
        }
    }
    return size - 1;
}

bool is_newline(int size) {
    for (int i = 0; i < size - 1; i++) {
        if (buffer[i] == '\n') {
            return true;
        }
    }
    return false;
}


char* my_readline(int fd)
{
    if (fd == -1)
    {
        free(buffer);
        buffer = NULL;
        return buffer;
    }

    char* new = NULL;
    char tmp_buffer[READLINE_READ_SIZE];
    char tmp;
    int len = 0;
    int idx = 0;
    int idx_two = 0;
    int bytes = 0;

    int size = my_strlen(buffer) + 1;
    int cursor = find_newline(size);
    while (is_newline(size) == false
           && (bytes = read(fd, tmp_buffer, READLINE_READ_SIZE -1)))
    {
        tmp_buffer[bytes] = '\0';
        resize_buffer(bytes);
        my_strcat(buffer, tmp_buffer);
        size = my_strlen(buffer) + 1;
        cursor = find_newline(size);
    }
    new = malloc(sizeof(char)*cursor +1);
    while (idx < cursor )
    {
        new[idx] = buffer[idx];
        idx += 1;
    }

    new[idx] = '\0';
    idx += 1;
    len = size - 1;

    if (idx == size)
    {
        idx = 1;
        len = 0;
    }
    while (size - idx)
    {
        tmp = buffer[idx];
        buffer[idx_two] = tmp;
        if (idx > len)
        {
            buffer[idx_two] = '\0';
        }
        idx += 1;
        idx_two += 1;
    }
    if (cursor == 0 && bytes == 0 && buffer[0] == '\0')
    {
        if (size == 1)
        {
            free(new);
            free(buffer);
            buffer = NULL;
            return buffer;
        }
    }
    return new;
}

int min(int first, int second, int third){
    int first_comparsion = first < second ? first : second;
    return first_comparsion < third ? first_comparsion : third;
}

void init_result(Result_Metadata* result){
    result->board.rows = 0;
    result->board.cols = 0;
    result->data.buffer = malloc(sizeof(char) * READLINE_READ_SIZE);
    if (result->data.buffer != NULL){
        my_memset(result->data.buffer, '\0', READLINE_READ_SIZE);
    }
}

void free_result(Result_Metadata* result){
    if(result->data.buffer != NULL) {
        free(result->data.buffer);
        result->data.buffer = NULL;
    }
}

int read_num_from_file (int fd,  Result_Metadata* result){
    char* num_line = my_readline(fd);
    if( num_line == NULL){
        printf("Error in readline");
        return -1;
    }
    result->board.rows = my_atoi(num_line);
    free(num_line);
    if (result->board.rows <= 0 || result->board.rows > MAX_SIZE) {
        printf("Invalid number of rows\n");
        return -1;
    }
    return 1;
}


int read_file(char* filename){
    int fd = open(filename, O_RDONLY);
    if (fd == -1){
        return -1;
    }
    init_my_readline();
    return fd;
}

int read_board_rows(int fd,  Result_Metadata* result){
    for (int row = 0; row < result->board.rows; row++) {
        char* line = my_readline(fd);
        if (line == NULL) {
            printf("Error reading rows");
            return 0;
        }
        int row_length = my_strlen(line);
        if(row_length > MAX_SIZE -1){
            printf("row is too long");
            return 0;
        }
        my_strcpy(result->board.grid[row], line);
        free(line);

        if(row == 0){
            result->board.cols = row_length;
        } else if (row_length != result->board.cols){
            printf("Error");
            return 0;
        }
    }
    return 1;
}

int read_board(int fd,  Result_Metadata* result){
    if(read_num_from_file(fd, result) <= 0){
        return 0;
    }
    if(!read_board_rows(fd, result)){
        close(fd);
        return 0;
    };
    return 1;
}

void init_board(Result_Metadata* result){
    for(int row = 0; row < result->board.rows; row++){
        result->data.dp[row][0] = (result->board.grid[row][0] == '.' ? 1 : 0);
    }

    for(int col = 0; col < result->board.cols; col++){
        result->data.dp[0][col] = (result->board.grid[0][col] == '.' ? 1 : 0);
    }
}

void fill_board(Result_Metadata * result, int* max_size, int* max_row, int* max_col) {
    for (int row = 1; row < result->board.rows; row++) {
        for (int col = 1; col < result->board.cols; col++) {
            if (result->board.grid[row][col] == '.') {
                result->data.dp[row][col] = min(result->data.dp[row-1][col],
                                                result->data.dp[row][col-1],
                                                result->data.dp[row-1][col-1]) + 1;
                if (result->data.dp[row][col] > *max_size) {
                    *max_size = result->data.dp[row][col];
                    *max_row = row;
                    *max_col = col;
                }
            } else {
                result->data.dp[row][col] = 0;
            }
        }
    }
}


void draw_square(Result_Metadata* result, int square_size, int bottom_right_row, int bottom_right_col){
    for (int row = bottom_right_row; row > bottom_right_row - square_size; row--) {
        for(int col = bottom_right_col; col > bottom_right_col - square_size; col--){
            result->board.grid[row][col] = 'x';
        }
    }
}

void largest_square(Result_Metadata* result){
    int largest_square_size = 0;
    int largest_row = 0;
    int largest_col = 0;

    init_board(result);
    fill_board(result, &largest_square_size, &largest_row, &largest_col);
    draw_square(result, largest_square_size, largest_row, largest_col);

}



void print_board(const Board* board){
    for (int i = 0; i < board->rows; i++){
        printf("%s\n", board->grid[i]);
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2)
    {
        return 1;
    }

    int fd = read_file(argv[1]);


    if(fd == -1) {
        return 1;
    }

    Result_Metadata* result = malloc(sizeof(Result_Metadata));
    if (!result) {
        close(fd);
        return 1;
    }


    init_result(result);

    if(!read_board(fd, result)) {
        close(fd);
        free_result(result);
        return 1;
    }

    largest_square(result);
    print_board(&result->board);
    free_result(result);
    free(result);

    close(fd);
    return 0;
}
