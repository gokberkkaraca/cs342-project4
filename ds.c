#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "utils.h"

void fcfs(struct Queue *req_queue, int N);
void sstf(struct Queue *req_queue, int N);
void look(struct Queue *req_queue, int N);
void clook(struct Queue *req_queue, int N);

int main(int argc, char **argv) {

  //Variables
  struct Queue *req_queue;
  char input_file[MAX_FILENAME];
  int N;

  //Initializations
  req_queue = createQueue();
  strcpy(input_file, argv[2]);
  N = atoi(argv[1]);

  readFile(req_queue, input_file);
  fcfs(req_queue, N);

  readFile(req_queue, input_file);
  sstf(req_queue, N);

  // readFile(req_queue, input_file);
  // look(req_queue, N);
  //
  // readFile(req_queue, input_file);
  // clook(req_queue, N);

  exit(0);
}

void fcfs(struct Queue *req_queue, int N){
  double total_wait_time = 0;
  double avarage_wait_time;
  double std_wait;

  int total_time = 0;
  int current_head = 1;
  int number_of_requests = req_queue->size;
  int index = 0;
  int wait_times[req_queue->size];

  while (!is_empty(req_queue)) {
    int wait_time;
    int head_replacement;

    struct request req = dequeue(req_queue);
    if (req.arrival_time >= total_time) {
      total_time = req.arrival_time;
      wait_time = 0;
    }
    else {
      wait_time = total_time - req.arrival_time;
    }

    head_replacement = abs(req.disk_number - current_head);
    current_head = req.disk_number;
    total_time = total_time + head_replacement;
    total_wait_time += wait_time;
    wait_times[index] = wait_time;
    index++;
  }

  avarage_wait_time = total_wait_time / number_of_requests;
  std_wait = calculateSTD( avarage_wait_time, wait_times, number_of_requests);

  printf("FCFS:\t %d\t%f\t%f\n", total_time, avarage_wait_time, std_wait);
}

void sstf(struct Queue *req_queue, int N){
  double total_wait_time = 0;
  double avarage_wait_time;
  double std_wait;

  int total_time = 0;
  int current_head = 1;
  int number_of_requests = req_queue->size;
  int index = 0;
  int wait_times[req_queue->size];
  struct request requests[number_of_requests];

  int i;
  for (i = 0; i < number_of_requests; i++) {
    requests[i] = dequeue(req_queue);
  }

  int numOfProcessed = 0;
  while (numOfProcessed != number_of_requests) {
    int wait_time;
    int head_replacement;

    int min_index = findMin(total_time, current_head, requests, number_of_requests, N);
    struct request req = requests[min_index];
    if (req.arrival_time >= total_time) {
      total_time = req.arrival_time;
      wait_time = 0;
    }
    else {
      wait_time = total_time - req.arrival_time;
    }

    head_replacement = abs(req.disk_number - current_head);
    current_head = req.disk_number;
    total_time = total_time + head_replacement;
    total_wait_time += wait_time;
    wait_times[index] = wait_time;
    index++;
    numOfProcessed++;
  }

  avarage_wait_time = total_wait_time / number_of_requests;
  std_wait = calculateSTD( avarage_wait_time, wait_times, number_of_requests);

  printf("SSTF:\t %d\t%f\t%f\n", total_time, avarage_wait_time, std_wait);
}
