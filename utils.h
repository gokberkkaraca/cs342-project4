#include "math.h"
#define MAX_FILENAME (128)

int findMin(int total_time, int current_head, struct request requests[], int size, int N){
  int min_index = -1;
  int min_disp = N + 1;
  int index = 0;
  for( index = 0; index < size; index++){
    if( (abs(current_head - requests[index].disk_number) < min_disp) && requests[index].processed == 0 && requests[index].arrival_time <= total_time){
      min_index = index;
      min_disp = abs(current_head - requests[index].disk_number);
    }
  }
  requests[min_index].processed = 1;
  return min_index;
}

double calculateSTD(double average, int data[], int size) {
  double square_sum = 0;
  int i;
  for (i = 0; i < size; i++) {
    double diff = abs(average - data[i]);
    square_sum = square_sum + diff * diff;
  }
  return sqrt(square_sum / (size-1));
}

void readFile( struct Queue *req_queue, char input_file[]){
  clear_queue(req_queue);
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char fileDir[MAX_FILENAME + 1];
  sprintf( fileDir, "%s", input_file);
  fp = fopen( fileDir, "r");

  if( fp == NULL){
    exit(1);
  }

  while( (read = getline( &line, &len, fp)) != -1){
    int in_arrival_time;
    int in_disk_no;
    sscanf( line, "%d %d", &in_arrival_time, &in_disk_no);
    struct request req;
    req.arrival_time = in_arrival_time;
    req.disk_number = in_disk_no;
    req.processed = 0;
    enqueue(req_queue, req);
  }

  fclose(fp);
}
