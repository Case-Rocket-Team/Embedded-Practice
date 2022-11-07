/* Kyler Rosen
Implementation of Circular Queue
Last Modified: 11/04/2022 */

#include <Arduino.h>
#include "queue.hpp"


/* Function to create Circular queue */
void Queue::enQueue(float value) {
	if ((front == 0 && rear == size-1) || (rear == (front-1)%(size-1))) { /* If full, deletes oldest element. */
		Serial.print("\nDeleting Oldest Element: ");
    Serial.println(Queue::deQueue());
    rear++;
		arr[rear] = value;
	}

	else if (front == -1) /* Insert First Element */
	{
		front = rear = 0;
		arr[rear] = value;
	}

	else if (rear == size-1 && front != 0)
	{
		rear = 0;
		arr[rear] = value;
	}

	else
	{
		rear++;
		arr[rear] = value;
	}
}

// Function to delete element from Circular Queue
float Queue::deQueue()
{
	if (front == -1)
	{
		Serial.println("\nQueue is Empty");
		return -1;
	}

	float data = arr[front];
	arr[front] = -1;
	if (front == rear)
	{
		front = -1;
		rear = -1;
	}
	else if (front == size-1)
		front = 0;
	else
		front++;

	return data;
}

// Function displaying the elements
// of Circular Queue
void Queue::displayQueue(){
	if (front == -1){
		Serial.println("\nQueue is Empty");
		return;
	}

	Serial.println("\nElements in Circular Queue are: ");
	if (rear >= front){
		for (int i = front; i <= rear; i++){
			Serial.print(arr[i]);
      Serial.print("\t");
    }
	}

	else{
		for (int i = front; i < size; i++){
			Serial.print(arr[i]);
      Serial.print("\t");
    }

		for (int i = 0; i <= rear; i++){
			Serial.print(arr[i]);
      Serial.print("\t");
    }
	}
}

bool Queue::isEmpty(){
  return front ==- 1;
}

/* Queue Implementation test */
int queueTest()
{
	Queue q(5);

	// Inserting elements in Circular Queue
	q.enQueue(14);
	q.enQueue(22);
	q.enQueue(13);
	q.enQueue(-6);

	// Display elements present in Circular Queue
	q.displayQueue();

	// Deleting elements from Circular Queue
	Serial.print("\nDeleted value = ");
  Serial.println(q.deQueue());
	Serial.print("\nDeleted value = ");
  Serial.println(q.deQueue());

	q.displayQueue();

	q.enQueue(9);
	q.enQueue(20);
	q.enQueue(5);

	q.displayQueue();

	q.enQueue(20);
  q.displayQueue();
	return 0;
}

