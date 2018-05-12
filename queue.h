// This queue implementation was inspired from
// https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/

struct request {
  int arrival_time;
  int disk_number;
  int processed;
};

struct Node {
  struct request data;
  struct Node *next;
};

struct Queue {
  struct Node *head, *tail;
  int size;
};

struct Queue* createQueue() {
  struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
  temp->head = NULL;
  temp->tail = NULL;
  temp->size = 0;
  return temp;
}

void enqueue(struct Queue* queue, struct request data) {
  struct Node* node = (struct Node*) malloc(sizeof(struct Node));
  node->data = data;
  node->next = NULL;

  if (queue->tail == NULL) {
    queue->head = node;
    queue->tail = node;
    queue->size = queue->size + 1;
  }
  else {
    queue->tail->next = node;
    queue->tail = node;
    queue->size = queue->size + 1;
  }
}

struct request dequeue(struct Queue* queue) {
  if (queue->head == NULL) {
    struct request req;
    req.arrival_time = -1;
    return req;
  }
  else {
    struct Node* node = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL) {
      queue->tail = NULL;
    }
    queue->size = queue->size - 1;
    struct request data = node->data;
    free(node);
    return data;
  }
}

int is_empty(struct Queue* queue) {
  return queue->head == NULL;
}

void clear_queue(struct Queue* queue) {
  while (!is_empty(queue)) {
    dequeue(queue);
  }
}

void print_queue(struct Queue* queue) {
  while (!is_empty(queue)) {
    struct request req = dequeue(queue);
    printf("Arrival: %d\t Disk: %d\n", req.arrival_time, req.disk_number);
  }
}
