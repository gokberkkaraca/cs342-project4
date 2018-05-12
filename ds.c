#include "algorithms.h"

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

  /*

  readFile(req_queue, input_file);
  look(req_queue, N);

  readFile(req_queue, input_file);
  clook(req_queue, N);
  */

  exit(0);
}
