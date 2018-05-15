#include "math.h"
#define MAX_FILENAME (128)

int find_first_unarrived_and_unprocessed_look(struct request requests[], int number_of_requests, int head_direction, int current_head, int N) {


    // Find the arrival time of next process
    int next_arrival_time = 99999999;
    int i;
    for (i = 0; i < number_of_requests; i++) {
      if (requests[i].arrived == 0 && requests[i].arrival_time <= next_arrival_time) {
        next_arrival_time = requests[i].arrival_time;
      }
    }

    int selected_index_on_right = -1;
    int selected_index_on_left = -1;
    int first_head_on_right = N+1;
    int first_head_on_left = -1;

    // Find request on right
    for (i = 0; i < number_of_requests; i++) {
        // A canditate to be selected
        if (requests[i].arrival_time == next_arrival_time) {
          if (requests[i].disk_number >= current_head
            && requests[i].disk_number <= first_head_on_right) {
              selected_index_on_right = i;
              first_head_on_right = requests[i].disk_number;
          }
        }
    }

    // Find request on left
    for (i = 0; i < number_of_requests; i++) {
        // A canditate to be selected
        if (requests[i].arrival_time == next_arrival_time) {
          if (requests[i].disk_number <= current_head
            && requests[i].disk_number >= first_head_on_left) {
              selected_index_on_left = i;
              first_head_on_left = requests[i].disk_number;
          }
        }
    }

    if ((head_direction == 1 && selected_index_on_right != -1) || (head_direction == 0 && selected_index_on_left == -1)) {
      return selected_index_on_right;
    }
    else {
      return selected_index_on_left;
    }
}

int findMin(int total_time, int current_head, struct request requests[], int size, int N){
  int min_index = -1;
  int min_disp = N + 1;
  int index = 0;
  int arrived_flag = 0;

  for (index = 0; index < size; index++) {
    if( requests[index].processed == 0 && requests[index].arrival_time <= total_time){
      arrived_flag = 1;
      break;
    }
  }

  if(arrived_flag == 0){
    int min_arrival_time = requests[size-1].arrival_time;
    int replacement = 0;
    for( index = 0; index < size; index++){
      if(requests[index].processed == 0 && requests[index].arrival_time <= min_arrival_time){
        min_index = index;
        replacement = abs( current_head - requests[min_index].disk_number);
        while( requests[index].arrival_time == requests[index+1].arrival_time && index < size -1){
          if( abs(requests[index + 1].disk_number - current_head) < replacement){
            min_index = index + 1;
            replacement = abs(requests[index + 1].disk_number - current_head);
          }
          index++;
        }
        break;
      }
  }
  }else{
    for( index = 0; index < size; index++){
      if( (abs(current_head - requests[index].disk_number) < min_disp) && requests[index].processed == 0 && requests[index].arrival_time <= total_time){
            min_index = index;
            min_disp = abs(current_head - requests[index].disk_number);
          }
    }
  }
  requests[min_index].processed = 1;
  return min_index;
}


double calculateSTD(double average, int data[], int size) {
  double square_sum = 0;
  int i;
  for (i = 0; i < size; i++) {
    double diff = average - data[i];
    if (diff < 0) {
      diff = -diff;
    }
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
    req.arrived = 0;
    enqueue(req_queue, req);
  }

  fclose(fp);
}

void swap(struct request* a, struct request* b)
{
    struct request temp = *a;
    *a = *b;
    *b = temp;
}

int partition (struct request requests[], int start, int end)
{
    struct request pivot = requests[end];    // pivot
    int smallElem = (start - 1);  // Index of smaller element

    for (int i = start; i <= end- 1; i++)
    {
        if (requests[i].disk_number <= pivot.disk_number)
        {
            smallElem++;
            swap(&requests[smallElem], &requests[i]);
        }
    }
    swap(&requests[smallElem + 1], &requests[end]);
    return (smallElem + 1);
}

void sort(struct request requests[], int start, int end) {
    if (start < end)
    {
        int index = partition(requests, start, end);

        sort(requests, start, index - 1);
        sort(requests, index + 1, end);
    }
}

int findTimeMin( struct request requests[], int size, int N){
  int index;
  for( index = 0; index < size - 1; index++){
    if ( requests[index].processed == 0 && requests[index].arrived == 0) {
      if( requests[index+1].processed == 0 && requests[index+1].arrived == 0 &&
      requests[index+1].arrival_time == requests[index].arrival_time){
        int selectedIndex = index;
        while (requests[index+1].processed == 0 && requests[index+1].arrived == 0 &&
        requests[index+1].arrival_time == requests[index].arrival_time && index != size - 1 ) {
          if (requests[index+1].disk_number < requests[index].disk_number) {
            selectedIndex = index + 1;
          }
          index++;
        }
        return selectedIndex;
      }
      return index;
    }
  }
  return -1;
}

// int findTimeMin(struct request requests[], int size) {
//   int returned_index;
//   int i;
//   while (i != size - 1 && requests[i].arrival_time == request[i+1].arrival_time)
// }

int findHeadMin( struct request requests[], int size, int current_head, int N){
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

int findArrivedMinHead( struct request requests[], int size, int N){
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


void updateArrivals(struct request requests[], int size,int current_time, int arrival_index){
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
