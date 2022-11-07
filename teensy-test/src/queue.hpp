/* Kyler Rosen
Declaration of Circular Queue
Last Modified: 11/04/2022 */ 

#ifndef QUEUE_H
#define QUEUE_H

class Queue {
  private:
	// Initialize front and rear
	int rear, front;

	// Circular Queue
	int size;
	float *arr;

  public:
  Queue(int s) {
	  front = rear = -1;
	  size = s;
	  arr = new float[s];
	}


	void enQueue(float value);
	float deQueue();
	void displayQueue();
    bool isEmpty();
};

int queueTest();

#endif