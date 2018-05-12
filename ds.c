#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "utils.h"

void fcfs(struct Queue *req_queue);
void sstf(struct Queue *req_queue);
void look(struct Queue *req_queue);
void clook(struct Queue *req_queue);
int findTimeMin( struct request requests[], int size);
int findTimeMax( struct request requests[], int size);
int findHeadMin( struct request requests[], int size, int current_head);
int findHeadMax( struct request requests[], int size, int current_head);
int findArrivedMaxHead( struct request requests[], int size);
int findArrivedMinHead( struct request requests[], int size);
void updateArrivals(struct request requests[], int current_time, int size);
int findNumberArrivedAndUnprocessed();

int N;
int arrival_index = 0;

int main(int argc, char **argv) {

  //Variables
  struct Queue *req_queue;
  char input_file[MAX_FILENAME];

  //Initializations
  req_queue = createQueue();
  strcpy(input_file, argv[2]);
  N = atoi(argv[1]);

  readFile(req_queue, input_file);
  fcfs(req_queue);

  readFile(req_queue, input_file);
  sstf(req_queue);

  readFile(req_queue, input_file);
  look(req_queue);
  //
  // readFile(req_queue, input_file);
  // clook(req_queue, N);

  exit(0);
}

void fcfs(struct Queue *req_queue){
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

void sstf(struct Queue *req_queue){
  double total_wait_time = 0;
  double avarage_wait_time;
  double std_wait;

  int total_time = 0;
  int current_head = 1;
  int number_of_requests = req_queue->size;
  int index = 0;
  int wait_times[req_queue->size];
  int numOfProcessed;
  struct request requests[number_of_requests];

  int i;
  for (i = 0; i < number_of_requests; i++) {
    requests[i] = dequeue(req_queue);
  }

  numOfProcessed = 0;
  while (numOfProcessed != number_of_requests) {
    int wait_time;
    int head_replacement;

    int min_index = findMin(total_time, current_head,
      requests, number_of_requests, N);
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
  std_wait = calculateSTD(avarage_wait_time, wait_times, number_of_requests);

  printf("SSTF:\t %d\t%f\t%f\n", total_time, avarage_wait_time, std_wait);
}


void look(struct Queue *req_queue) {

  double total_wait_time = 0;
  double avarage_wait_time;
  double std_wait;
  int wait_times[req_queue->size];


  int total_time = 0;
  int current_head = 1;
  int head_direction = 1;

  int number_of_requests = req_queue->size;
  int number_of_processed = 0;

  // Create an array of time-sorted requests
  struct request requests[req_queue->size];
  int i;
  for (i = 0; i < number_of_requests; i++) {
    requests[i] = dequeue(req_queue);
  }

  // Start processing requests
  while (1) {

    int wait_time;
    int head_replacement;


    struct request req;
    int request_to_be_processed_index = -2;
    if (number_of_processed == number_of_requests) {
      break;
    }
    else if (findNumberArrivedAndUnprocessed(requests,number_of_requests, total_time) == 0) {
      /* There is no request in the arrival queue, but processes are not
      finished, so continue to the first arrived one */
      request_to_be_processed_index = (head_direction) ? findTimeMin(requests,
        number_of_requests) : findTimeMax(requests, number_of_requests);

      if (findTimeMin(requests,
        number_of_requests) == -1 && findTimeMax(requests, number_of_requests) == -1) {
        break;
      }
      req = requests[request_to_be_processed_index];


      if (req.disk_number < current_head) {
        head_direction = 0;
      }
      else if (req.disk_number > current_head) {
        head_direction = 1;
      }
    }
    else {
      /* There is at least one arrived process,
       choose the one which has closes head */

       if (findHeadMin(requests, number_of_requests, current_head) == -1
       && findHeadMax(requests, number_of_requests, current_head) == -1) {
         break;
       }

        if( head_direction == 1){
          request_to_be_processed_index = findHeadMin(requests, number_of_requests, current_head);
          if(request_to_be_processed_index == -1){
            head_direction = 0;
          }
        }

        if( head_direction == 0){
          request_to_be_processed_index = findHeadMax(requests, number_of_requests, current_head);
          if(request_to_be_processed_index == -1){
            head_direction = 1;
          }
        }

      req = requests[request_to_be_processed_index];
    }

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
    wait_times[request_to_be_processed_index] = wait_time;
    updateArrivals( requests,  number_of_requests, total_time);

    if (head_direction == 0 && current_head == findArrivedMinHead(requests, number_of_requests)) {
      head_direction = 1;
    }else if (head_direction == 1
      && current_head == findArrivedMaxHead(requests, number_of_requests)) {
      head_direction = 0;
    }

    requests[request_to_be_processed_index].processed = 1;
    number_of_processed++;
  }

  avarage_wait_time = total_wait_time / number_of_requests;
  std_wait = calculateSTD(avarage_wait_time, wait_times, number_of_requests);

  printf("LOOK:\t %d\t%f\t%f\n", total_time, avarage_wait_time, std_wait);
}

int findTimeMin( struct request requests[], int size){
  int index;
  for( index = 0; index < size; index++){
    if ( requests[index].processed == 0) {
      return index;
    }
  }
  return -1;
}

int findTimeMax( struct request requests[], int size){
  int index;
  for( index = size-1; index >= 0; index--){
    if( requests[index].processed == 0){
      return index;
    }
  }
  return -1;
}

int findHeadMin( struct request requests[], int size, int current_head){
  int index;
  int min_head;
  int min_head_index;

  min_head = N + 1;
  min_head_index = -1;
  for( index = 0; index < size; index++){
    if( requests[index].processed == 0 && requests[index].arrived == 1){
      if(requests[index].disk_number <= min_head && requests[index].disk_number > current_head){
        min_head = requests[index].disk_number;
        min_head_index = index;
      }
    }
  }
  return min_head_index;
}

int findArrivedMinHead( struct request requests[], int size){
  int index;
  int min_head;
  int min_head_index;

  min_head = N + 1;
  min_head_index = -1;
  for( index = 0; index < size; index++){
    if( requests[index].processed == 0 && requests[index].arrived == 1){
      if(requests[index].disk_number <= min_head){
        min_head = requests[index].disk_number;
        min_head_index = index;
      }
    }
  }
  return min_head_index;
}

int findHeadMax( struct request requests[], int size, int current_head){
  int index;
  int max_head;
  int max_head_index;

  max_head = -1;
  max_head_index = -1;
  for( index = 0; index < size; index++){
    if( requests[index].processed == 0 && requests[index].arrived == 1){
      if(requests[index].disk_number >= max_head && requests[index].disk_number < current_head ){
        max_head = requests[index].disk_number;
        max_head_index = index;
      }
    }
  }
  return max_head_index;
}


int findArrivedMaxHead( struct request requests[], int size){
  int index;
  int max_head;
  int max_head_index;

  max_head = -1;
  max_head_index = -1;
  for( index = 0; index < size; index++){
    if( requests[index].processed == 0 && requests[index].arrived == 1){
      if(requests[index].disk_number >= max_head){
        max_head = requests[index].disk_number;
        max_head_index = index;
      }
    }
  }
  return max_head_index;
}

void updateArrivals(struct request requests[], int size,int current_time){
  int i;
  for (i = arrival_index; i < size; i++) {
    if(requests[i].arrival_time <= current_time){
      requests[i].arrived = 1;
    }
  }
}

int findNumberArrivedAndUnprocessed(struct request requests[], int size, int current_time){
  int i;
  int count;
  count = 0;
  for (i = 0; i < size; i++) {
    if(requests[i].arrived == 1 && requests[i].processed == 0){
      count++;
    }
  }
  return count;
}
