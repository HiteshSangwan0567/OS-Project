
#include <iostream>
#include <queue>   	 // For ready and block queue
#include <fstream>	// For ifstream (Reading File)
#include <cstdlib>     // For atoi
using namespace std;
void checkblockqueue(); //prototype of checkblockqueue function
class data
{	public:
	string PID;
	int AT, CPU1, IO, CPU2, priority, TAT, wt, finish_time,wait_for_IO ; //finish_time means,that time when CPU2 become Zero
	bool is_in_any_queue; //First time when process goes to either ready or block queue, it becomes true and never become false again.
	data() //constructor
	{
		AT = 0; CPU1 = 0; IO = 0; CPU2 = 0; priority = 0 ; finish_time = 0; wait_for_IO = 0; TAT = 0; wt=0 ; is_in_any_queue = false;
	}
};
	string temp;
	data p[5]; 				//Array of object of class
	data check;				//Object of class
	data running_process; 	//Object of class
	data object[5];			//when i sort queue, i must have to pop all elements and store in this array of objects.
	int total_cpu_time = 0 ;
	int cpu_time = 0;
	int quantum = 0;
	int idle_time = 0;
	int processes_range;
	int total_lines = 0;
	queue<data> readyqueue;
	queue<data> blockqueue;
int main()
{
	ifstream read;

	// File pointer
	fstream fout;


	// ************************************ Calculating Total Number of Processes in file **********************************//
	read.open("C:/Users/LENOVO/Desktop/ProjectOS/input2.csv");
	int count=0;
	while (getline(read, temp))
	{
        count = count + 1;
	}
	if (count != 6)
	{
		cout<<"Sorry, Processes Exceed Five"<<endl;
		return 0;
	}
	read.close();
	// ************************************ Validating Quantum (only be 4 or 7) ******************************************//
	cout << "Enter Quantum: "<<endl;
	cin >> quantum ;
	while (quantum <=0 )
	{
		cout << "Incorrect time quantum. Enter correct value";
		cin>>quantum;
	}
	cout << "Time Quantum Set by the user: "<<quantum<<endl;
	//********************************************* File Reading Start *********************************************************//
	//************************************************** Copied ****************************************************************//

    // file pointer

    // opens an existing csv file or creates a new file.
    read.open("C:/Users/LENOVO/Desktop/ProjectOS/input2.csv", ios::out | ios::app);

    cout << "Enter the Process ID,  AT, CPU1, IO, CPU2, PRI "<< endl;

    string PID;
	int AT, CPU1, IO, CPU2, priority;
    cout<<"Enter the PID, AT, CPU1, IO, CPU2 and PRI";
    // Read the input
    for (int i = 0; i < 5; i++) {

        cin >> p[i].PID
            >> p[i].AT
            >> p[i].CPU1
            >> p[i].IO
            >> p[i].CPU2
            >> p[i].priority;

        // Insert the data to file
        fout << p[i].PID << ", "
             << p[i].AT << ", "
             << p[i].CPU1 << ", "
             << p[i].IO << ", "
             << p[i].CPU2 << ", "
             << p[i].priority<<","
             << "\n";
    }



	//********************************************* File Reading End ***********************************************************//
	for (int i=0 ; i <=4 ; i++)
	{
			//cout << p[i].PID<<"\t";		cout << p[i].AT<<"\t";		cout << p[i].CPU1<<"\t";		cout << p[i].IO<<"\t";			cout << p[i].CPU2<<"\t";		cout << p[i].priority<<"\t";		cout << endl<<endl<<"\n";
			total_cpu_time = total_cpu_time + (p[i].CPU1 + p[i].CPU2 + p[i].IO) ; //cpu_time can never exceed total_cpu_time, so it help us in while loop
	}
	//**************************************** Sorting Of All processes AT Start ****************************************************//
	for(int i=0;i<=4;i++)
	{
		for(int j=0;j<4-i;j++)
		{
			if(p[j].AT > p[j+1].AT)
			 {
				check = p[j];
				p[j] = p[j+1];
				p[j+1]=check;
			 }
		}
	}
	//**************************************** Sorting Of All processes AT End ****************************************************//
	cpu_time = p[0].AT; //Minimum AT of any process goes to cpu_time
	if (cpu_time != 0) //If Min AT is not zero, than from 0 to that AT, cpu will remains idle
	{
		idle_time = idle_time + cpu_time;
	}
	while (cpu_time <= total_cpu_time)
	{
		 //*************** When AT become Equal or less than cpu_time, push in Ready or Block Queue (START) ********************//
		for (int i=0 ; i<=4 ; i++)
		{
			if (p[i].AT <= cpu_time && p[i].is_in_any_queue == false)
			{
				if (p[i].CPU1 == 0 )
				{
					p[i].wait_for_IO = cpu_time + p[i].IO;
					blockqueue.push(p[i]);
					p[i].is_in_any_queue = true;
				}
				else
				{
				readyqueue.push(p[i]);
				p[i].is_in_any_queue = true;
				}
			}
		}
		 //*************** When AT become Equal or less than cpu_time, push in Ready or Block Queue (END) ********************//
		checkblockqueue(); //Function Call
		int N = readyqueue.size();
		if (N==0)
		{
			int P = blockqueue.size();
			//************* if (N+P==0) is true only when both Ready & Block is empty, Means all process Ends ************//
			if (N+P == 0)
			{
				cout <<"Output Table Shown Below"<<endl;
				for (int i=0 ; i <=4 ; i++)
				{
						if (i==0)
						{ cout << "Process\t" ; cout <<"AT\t"; cout <<"FT\t"; cout <<"TAT\t"; cout <<"WT\t"<<endl;};
						cout << p[i].PID<<"\t";cout << p[i].AT<<"\t";cout << p[i].finish_time<<"\t";cout << p[i].TAT<<"\t";cout << p[i].wt<<"\t";cout <<endl;
				}
				float wt;
				float tat;
				wt = p[0].wt + p[1].wt + p[2].wt + p[3].wt + p[4].wt;
				wt = wt/5;
				tat = p[0].TAT + p[1].TAT + p[2].TAT + p[3].TAT + p[4].TAT;
				tat = tat/5;
				cout << "Average Waiting Time is: "<<wt<<endl;
				cout << "Average TurnAroundTime is: "<<tat<<endl;
				//cout << "Total idle time of system is : "<<idle_time<<endl;
				float y = (cpu_time-1)-idle_time;
				float x = cpu_time-1;
				float result ;
				result = (y/x)*100 ;
				cout << "CPU utilization percentage is : " << result <<"%"<<endl;
				cpu_time  = total_cpu_time+1;		//End While Loop
			}
			//********* These two statement Runs only when Ready Queue size is zero , Means system is idle at this time ******//
			idle_time = idle_time + 1;
			cpu_time = cpu_time + 1;
		}
		else //Else will run, when ready queue size is not zero
		{
			if (N != 1) //If Ready Queue size is != 1, than we have to sort them according to priority
			{
				for (int i=0 ; i<N ; i++)
				{
					object[i] = readyqueue.front();
					readyqueue.pop();
				}
				for (int i=0 ; i< N ; i++)
				{
					for (int j= 0 ; j< ((N-1)-i) ; j++)
					{
						if (object[j].priority > object[j+1].priority) //Sort According To priority
						{
							check = object[j];
							object[j]= object[j+1];
							object[j+1] = check;
						}
						if (object[j].priority == object[j+1].priority) //If priority Same than check arrival time
						{
							if (object[j].AT == object[j+1].AT) // if arrival time same than sort according to order they are listed in input file
							{
								int u = atoi (&object[j].PID[1]); //in P1 u will be 1 , in P2 u will be 2 and so on , PID[1] means integer is at index 1
								int v = atoi (&object[j+1].PID[1]);
								if (u > v )
								{
									check = object[j];
									object[j]= object[j+1];
									object[j+1] = check;
								}
							}
							else
							{
								if (object[j].AT > object[j+1].AT) //Sort According to Arrival time
								{
									check = object[j];
									object[j]= object[j+1];
									object[j+1] = check;
								}
							}

						}
					}
				}
				for (int i=0; i<N ; i++)
				{
					readyqueue.push(object[i]);
				}
			}
			running_process = readyqueue.front(); //Get process from ready queue, having Highest priority
			readyqueue.pop();	//Pop that process from ready queue
		if (running_process.CPU1 != 0)
			{
				if (running_process.CPU1 > quantum)
				{
					running_process.CPU1 = running_process.CPU1 - quantum;
					cpu_time = cpu_time + quantum;
					readyqueue.push(running_process); //Push again to ready queue, because CPU1 still left
				}
				else
				{
					int b = running_process.CPU1;
					cpu_time = cpu_time + b;
					running_process.CPU1 = 0;
					running_process.wait_for_IO = cpu_time + running_process.IO; //How many units running process will wait after CPU1 becomes Zero
					blockqueue.push(running_process); //Push to block queue because this process needs IO units.
				}
			}
			else
			{
				if (running_process.CPU2 > quantum)
				{
					running_process.CPU2 = running_process.CPU2 - quantum;
					cpu_time = cpu_time + quantum;
					readyqueue.push(running_process); //Push again to ready queue, because CPU2 still left
				}
				else //this else will execute only when cpu1==0 and cpu2<quantum , now running process is going to ends in this else statement
				{
					int b = running_process.CPU2;
					cpu_time = cpu_time + b;
					running_process.CPU2 = 0;
					running_process.finish_time = cpu_time; //Current cpu_time will be the finish time of running process
					running_process.TAT =running_process.finish_time - running_process.AT ; //TAT=FT - AT

					//Now Deciding Running process was which process, because running process(object) changed with time, but P remains same //
					if (running_process.PID == "P1")
					{
						int z=0;
						z = p[z].CPU1+p[z].CPU2;
						p[0].TAT = running_process.TAT;
						p[0].wt = running_process.TAT - z;
						p[0].finish_time = running_process.finish_time ;

					}
					if (running_process.PID == "P2")
					{
						int z=1;
						z = p[z].CPU1+p[z].CPU2;
						p[1].TAT = running_process.TAT;
						p[1].wt = running_process.TAT - z;
						p[1].finish_time = running_process.finish_time ;
					}
					if (running_process.PID == "P3")
					{
						int z=2;
						z = p[z].CPU1+p[z].CPU2;
						p[2].TAT = running_process.TAT;
						p[2].wt = running_process.TAT - z;
						p[2].finish_time = running_process.finish_time ;
					}
					if (running_process.PID == "P4")
					{
						int z=3;
						z = p[z].CPU1+p[z].CPU2;
						p[3].TAT = running_process.TAT;
						p[3].wt = running_process.TAT - z;
						p[3].finish_time = running_process.finish_time ;
					}
					if (running_process.PID == "P5")
					{
						int z=4;
						z = p[z].CPU1+p[z].CPU2;
						p[4].TAT = running_process.TAT;
						p[4].wt = running_process.TAT - z;
						p[4].finish_time = running_process.finish_time ;
					}
				}
			}
		}
	}
}
void checkblockqueue()
{
		int N = blockqueue.size();
		if (N == 0)
		{
			return;
		}
		else if (N!= 1) //This will not execute if block queue size is 1, because we don't need to sort one process in block queue
			{
				for (int i=0 ; i<N ; i++)
				{
					object[i] = blockqueue.front();
					blockqueue.pop();
				}
				for (int i=0 ; i< N ; i++)
				{
					for (int j= 0 ; j< ((N-1)-i) ; j++)
					{
						if (object[j].wait_for_IO > object[j+1].wait_for_IO)
						{
							check = object[j];
							object[j]= object[j+1];
							object[j+1] = check;
						}
					}
				}
				for (int i=0; i<N ; i++)
				{
					blockqueue.push(object[i]);
				}
			}
		for (int i=0 ; i<N ; i++)
		{
			check = blockqueue.front();
			if (check.wait_for_IO <= cpu_time) //Checking if wait_for_IO becomes equal or less than current cpu_time, if true than pop from block queue, and push into ready queue.s
			{
			blockqueue.pop();
			readyqueue.push(check);
			}
		}
}
