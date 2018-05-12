#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue.h"

#define MAX_FILENAME (128)

double calculateSTD(double average, int data[], int size) {
  double square_sum = 0;
  int i;
  for (i = 0; i < size; i++) {
    double diff = abs(average - data[i]);
    square_sum = square_sum + diff * diff;
  }
  return sqrt(square_sum / (size-1));
}

//Reads input file and initializes the request queue
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

void fcfs(struct Queue *req_queue, int N){
  double total_wait_time;
  double avarage_wait_time;
  double std_wait;
  int total_time;
  int current_head;
  int number_of_requests;
  int index;
  int wait_times[req_queue->size];

  total_time = 0;
  index = 0;
  current_head = 1;
  total_wait_time = 0;
  number_of_requests = req_queue->size;

  while (!is_empty(req_queue)) {
    int wait_time;
    struct request req = dequeue(req_queue);
    if (req.arrival_time >= total_time) {
      // NO WAIT, UPDATE CURRENT TIME
      total_time = req.arrival_time;
      wait_time = 0;
    }
    else {
      // REQUEST WAITS
      wait_time = total_time - req.arrival_time;
    }

    int head_replacement = abs(req.disk_number - current_head);
    current_head = req.disk_number;
    total_time = total_time + head_replacement;
    total_wait_time += wait_time;
    wait_times[index] = wait_time;
    index++;
    printf("wait time: %d\n", wait_time);
    printf("head rep: %d\n", head_replacement);
  }

  avarage_wait_time = total_wait_time / number_of_requests;
  std_wait = calculateSTD( avarage_wait_time, wait_times, number_of_requests);

  printf("FCFS :\t %d\t%f\t%f\n", total_time, avarage_wait_time, std_wait);
}

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

void sstf(struct Queue *req_queue, int N){
  double total_wait_time;
  double avarage_wait_time;
  double std_wait;
  int total_time;
  int current_head;
  int index;
  int wait_times[req_queue->size];

  total_time = 0;
  index = 0;
  current_head = 1;
  total_wait_time = 0;

  int i;
  int number_of_requests = req_queue->size;
  struct request requests[number_of_requests];

  for (i = 0; i < number_of_requests; i++) {
    requests[i] = dequeue(req_queue);
  }

  int numOfProcessed = 0;
  while (numOfProcessed != number_of_requests) {
    int wait_time;
    int min_index = findMin(total_time, current_head, requests, number_of_requests, N);
    struct request req = requests[min_index];
    if (req.arrival_time >= total_time) {
      // NO WAIT, UPDATE CURRENT TIME
      total_time = req.arrival_time;
      wait_time = 0;
    }
    else {
      // REQUEST WAITS
      wait_time = total_time - req.arrival_time;
    }

    int head_replacement = abs(req.disk_number - current_head);
    current_head = req.disk_number;
    total_time = total_time + head_replacement;
    total_wait_time += wait_time;
    wait_times[index] = wait_time;
    index++;
    printf("wait time: %d\n", wait_time);
    printf("head rep: %d\n", head_replacement);
    numOfProcessed++;
  }

  avarage_wait_time = total_wait_time / number_of_requests;
  std_wait = calculateSTD( avarage_wait_time, wait_times, number_of_requests);

  printf("FCFS :\t %d\t%f\t%f\n", total_time, avarage_wait_time, std_wait);
}

/*
void look(struct Queue *req_queue, int N){

}

void clook(struct Queue *req_queue, int N){

}
*/
