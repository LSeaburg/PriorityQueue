/* Logan Seaburg
 *
 * In order to create these function I used lecture notes from class.
 */

#include "LinkedPriorityQueue.h"

/* Will initialize a new priority queue of length zero that will contain
 * just a pointer that declares the end of the list.
 */
LinkedPriorityQueue::LinkedPriorityQueue() {
    front = NULL;
}

/* Will call the clear function on the queue when it goes out of scope
 * to free up memory.
 */
LinkedPriorityQueue::~LinkedPriorityQueue() {
    clear();
}

/* This will find the value in the queue and, if it does prove to be valid,
 * will delete it and will then add a new value/ priority pair by calling the
 * enqueue function.
 */
void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    PQNode* curr = front;
    if (curr == NULL) {
        throw "PQ is Empty";
    } else if (curr->value == value) {
        if (curr->priority < newPriority) {
            throw "New priority is greater than the old priority";
        } else {
            curr->priority = newPriority;    //if it is already first in the queue, a lower priority will still make it first
        }
    }
    while (curr->next != NULL && curr->next->value != value) {
        curr = curr->next;
    }
    if (curr->next == NULL) {
        throw "Value not found in PQ";
    } else {
        cout << curr->value;
        PQNode* trash = curr->next;
        curr->next = curr->next->next;
        delete trash;
        enqueue(value, newPriority);
    }
}

/* Will loop through the entire priority queue and delete the elements one
 * at a time, freeing up memory in the system.
 */
void LinkedPriorityQueue::clear() {
    while (front != NULL) {
        PQNode* trash = front;
        front = front->next;
        delete trash;
    }
}

/* Will remove and return the value of the first element in the queue.
 */
string LinkedPriorityQueue::dequeue() {
    string value = front->value;
    PQNode* trash = front;
    front = front->next;
    delete trash;
    return value;
}

/* Will add an element into the queue. If the queue is empty or the
 *priority is lower than the first element it will add it at the beginning.
 * It will then continue looping through the queue waiting to find an element with
 * a priority that is greater, and then add that element directly before.
 */
void LinkedPriorityQueue::enqueue(string value, int priority) {
    if (front == NULL || priority < front->priority ||
            (priority == front->priority && value < front->value)) {
        PQNode* temp = new PQNode(value, priority, front);
        front = temp;
    } else {
        PQNode* curr = front;
        while (curr->next != NULL && !(priority < curr->next->priority ||
               (priority == curr->next->priority && value < curr->next->value))) {
            curr = curr->next;
        }
        PQNode* temp = new PQNode(value, priority, curr->next);
        curr->next = temp;
    }
}

/* Will return true if the front points to null, indicating that the queue
 * contains no elements.
 */
bool LinkedPriorityQueue::isEmpty() const {
    return front == NULL;
}

/* Will return the value of the first element in the queue.
 */
string LinkedPriorityQueue::peek() const {
    if (front == NULL) {
        throw "PQ is Empty";
    }
    return front->value;
}

/* Will return the priorty value of the first element in the
 * queue.
 */
int LinkedPriorityQueue::peekPriority() const {
    if (front == NULL) {
        throw "PQ is Empty";
    }
    return front->priority;
}

/* Loops through all of the elements of the queue and adds
 * to a counter to find the total number of elements in the queue.
 */
int LinkedPriorityQueue::size() const {
    PQNode* curr = front;
    int size = 0;
    while (curr != NULL) {
        size++;
        curr = curr->next;
    }
    return size;
}

/* Loops through the entire queue and will print the the value and the
 * priorty of the value in pairs.
 */
ostream& operator <<(ostream& out, const LinkedPriorityQueue& queue) {
    PQNode* curr = queue.front;
    cout << '{';
    while (curr != NULL) {
        out << '"' << curr->value << '"' << ':' << curr->priority;
        if (curr->next != NULL) {
            cout << ", ";
        }
        curr = curr->next;
    }
    cout << '}';
    return out;
}
