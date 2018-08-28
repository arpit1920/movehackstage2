

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <ctime>
using namespace std;

//Node of linked list
struct QueueNode
{
	//ticket number records customer's place in line
	int ticketNumber;
	
	//time stamp records what time the customer arrived
	long timeStamp;

	QueueNode *link;
};
typedef QueueNode* QueueNodePtr;

//class to simulate queue at recharging station . New customers are added to back of queue
// while customers are helped from the front of the queue
class Queue
{
private:
	int array[3];		//holds wait times of the 3 most recent customers
	QueueNodePtr front;	//points to the head of list, items are removed at front
	QueueNodePtr back;	//points to other end of list, items are added at back

public:
	Queue();
	//constructor initializes the object to an empty queue

	~Queue();
	//destructor for Queue class object

	bool empty() const;
	//returns true if the queue is empty and returns false otherwise

	void helpCustomer();
	//precondition: queue is not empty
	//displays wait time of the customer and estimated wait time of next custonmer	
	//removes that customer from queue

	void addCustomer(int number);
	//post condition: item has been added to the back of the queue
	//inputs customer wait time into function 'Last3'

	int Last3(int num, long WaitTime);
	//saves the last three customer wait times and computes the average 
};

int main()
{
	Queue q;
	int choice, i;
	
	//the queue is always empty at the beginning of the program
	cout << "The line is empty" << endl;

	do
	{
		//give user a choice to add a customer to queue, help a customer currently
		//in the queue or end program
		cout << "Enter '1' to simulate a customer's arrival, '2' to help the" << endl;
		cout << "next customer, or '3' to quit." << endl;
		cin >> choice;

		//if adding a new customer to queue
		if(choice == 1)
		{
			q.addCustomer(i);
			i++;
		}

		//if helping a customer in queue
		else if(choice == 2)
		{
			q.helpCustomer();
		}

		//if invalid choice
		else if(choice > 3)
		{
			cout << "not a valid choice! ";
			choice = 3;
		}
		
	
	} while(choice != 3);

	//if choice is not 1 or 2, end program
	cout << "end of program" << endl;
	return 0;
}

//constructor to set front and back of list to NULL
Queue::Queue() : front(NULL), back(NULL)
{
	//intentionally empty
}

//destructor to delete linked list
Queue::~Queue()
{
	//create new pointer and point it to front of list
	QueueNodePtr temp = front;

	//while list is not empty
	while(temp != NULL)
	{
		//point to next node and delete the previous node
		temp = temp->link;
		delete temp;
	}
}

/**
*  @brief    This function is returns true is the queue is empty
*  @return   bool
*/
bool Queue::empty() const
{
	return (back == NULL);
}

/**
*  @brief    This function removes the customer from the queue, but only
	     after it records the time of service of the customer, displays the
	     wait time, and displays the estimated wait time of the next customer
	     based on the last 3 customers.
*
*  @return   void
*/
void Queue::helpCustomer()
{
	long int helpTime = 0;
	int waitTime = 0;
	
	//if queue is empty, do not run code to remove customer
	if(empty())
	{
		cout << "The line is empty" << endl;
	}
	
	//if queue is not empty
	else
	{
		//helpTime is the the time at which the customer recieved help	
		helpTime = static_cast<long>(time(NULL));

		//waitTime is the time the customer had to wait since time of arrival
		waitTime = helpTime - (front->timeStamp);
	
		//print times to console and call function 'Last3' to get estimated wait time
		//for next customer
		cout << "Customer " << front->ticketNumber+1 << " is being helped at time ";
		cout << helpTime << ". Wait time = " << waitTime << " seconds." << endl;
		cout << "The estimated wait time for customer " << front->ticketNumber + 2;
		cout << " is " << Last3(front->timeStamp, waitTime) << " seconds." << endl;
		
		//create new pointer to point at front and displace original front pointer
		QueueNodePtr discard = front;
		front = front->link;
	
		//if you removed the last node
		if (front == NULL)
		{
			back = NULL;
		}
		
		//remove the front customer
		delete discard;
	}
}

/**
*  @brief   This function adds a customer to the queue, gives the customer a ticket number
*	    and timestamp. the function then displays what time the customer entered queue
*
*  @param   number is the ticket number of the customer
*  @return  void
*/
void Queue::addCustomer(int number)
{
	long int seconds = static_cast<long>(time(NULL));
	
	//if queue is empty
	if(empty())
	{
		//add customer to front, give customer ticket number and timestamp
		//set link front to NULL since there is only one customer in queue
		front = new QueueNode;
		front->ticketNumber = number;
		front->timeStamp = seconds;
		front->link = NULL;
		back = front;
	}

	//if queue is not empty
	else
	{
		//add customer to back, give customer ticket number and timestamp
		QueueNodePtr temp = new QueueNode;
		temp->ticketNumber = number;
		temp->timeStamp = seconds;
		temp->link = NULL;
		back->link = temp;
		back = temp;		
	}
	
	//print time of arrival of customer to console
	cout << "customer " << number + 1 << " entered the que at time " << seconds << endl;
}

/**
*  @brief   This function saves the most recent 3 customers wait time. The function then
* 	    calculates the average wait time and returns an estimated wait time for the
* 	    next customer
*
*  @param   arrivalTime is the timestamp of customer
*  @param   WaitTime is (time of service - arrival time)
*  @return  int
*/
int Queue::Last3(int arrivalTime, long WaitTime)
{
	int average, i;

	//if theres less than 3 customers, input wait time of the customer into an array
	//that will hold maximum three wait times.
	if(front->ticketNumber < 3)
	{
		array[front->ticketNumber] = WaitTime;
		
		//if is the very first customer, the estimated wait time for
		//the next customer is just the wait time of this customer
		if(front->ticketNumber == 0)
		{
			average = WaitTime;
		}

		//if this is the second customer then the estimated wait
		//time is the average between first and second customer
		else
		{ 	
			average = (array[0] + array[1]) / 2;
		}
	}

	//if theres 3 or more customers, shift array so that only the last 3 customers
	else
	{
		//shift array so that there are only the last 3 customers in array
		for(i = 0; i < 3; i++)
		{
			array[i] = array[i + 1];
		}

		//input wait time of customer into the end of the array
		array[2] = WaitTime;

		//calculate the average of the 3 customer wait times held in the array
		average = (array[0] + array[1] + array[2]) / 3;
	}

	return average;
}



