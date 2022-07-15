#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<string>
#include<fstream>
using namespace std;


//////////////////////////////////////QUEUE-NODE////////////////////////////////////////

class QueueNode
{
public:
	int P_KEY; //key --> Priority
	int U_ID;	//User Id
	string Operation; //Operation
	bool A_granted; // check if access is granted
	QueueNode();
	QueueNode(int k, int id, string op);
};

QueueNode::QueueNode() //Default Constructor
{
	P_KEY = 0;
	U_ID = 0;
	Operation = "";
	A_granted = false;
}
QueueNode::QueueNode(int k, int id, string op) //Parametrised Constructor
{
	P_KEY = k;
	U_ID = id;
	Operation = op;
	A_granted = false;
}


/////////////////////////////////PriorityQueue///////////////////////////////
struct comparator
{
	bool operator()(QueueNode& first, QueueNode& second)
	{
		return first.P_KEY > second.P_KEY;
	}
};

template<typename Queue>
class PriorityQueue
{
public:
	// vector to store heap elements	
	vector<Queue> Q; //vector array
	unsigned int size() //size variable (data member)
	{
		return Q.size();
	}

	PriorityQueue() //Default constructor
	{
		//Q.push_back(QueueNode());
	}

	PriorityQueue(vector<Queue>& x) //Parametrised constructor
	{
		int size = x.size();
		x.resize(size);
		Q = x;
	}

	void setQueue(vector<Queue>& vec) //set a priority queue
	{
		Q = vec;
	}

	void BuildQueue()
	{
		make_heap(Q.begin(), Q.end(), comparator());
		sort_heap(Q.begin(), Q.end(), comparator());
	}


	// Function to check if the heap is empty or not
	int empty()
	{
		if (Q.size() == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	// insert P_KEY into the heap
	void Insert(QueueNode q)
	{
		// insert a new element at the end of the vector
		Q.push_back(q);

		make_heap(Q.begin(), Q.end(), comparator());
		sort_heap(Q.begin(), Q.end(), comparator());

	}

	QueueNode ExtractMax(PriorityQueue& X) //remove and give max node
	{
		// if the heap has no elements, throw an exception
		if (Q.size() == 0)
		{
			QueueNode x;
			cout << "Heap has no elements" << endl;
			return x;
		}
		else if (size() == 1)
		{
			QueueNode x;
			x = Q.back();
			Q.pop_back();
			return x;
		}
		else
		{
			// replace the root of the heap with the last element
			// of the vector
			QueueNode temp;
			temp = Q[0];
			Q[0] = Q.back();
			Q.pop_back();

			make_heap(Q.begin(), Q.end(), comparator());
			sort_heap(Q.begin(), Q.end(), comparator());

			return temp;
		}
	}

	int FindMax() //display max
	{
		// if the heap has no elements, throw an exception
		if (Q.size() == 0)
		{
			cout << "Heap has no elements" << endl;
			return 0;
		}
		else
		{
			cout << "------FINDING MAX------" << endl;
			// otherwise, return the top (first) element
			cout << "KEY: " << Q.at(0).P_KEY << endl;        // or return A[0];
			cout << "User Id: " << Q.at(0).U_ID << endl;
			cout << "Operation: " << Q.at(0).Operation << endl;
			return Q.at(0).P_KEY;
		}
	}

	int FindMin() //display minimum
	{
		// if the heap has no elements, throw an exception
		if (size() == 0)
		{
			cout << "Heap has no elements" << endl;
			return 0;
		}
		else
		{
			cout << "------FINDING MIN------" << endl;
			// otherwise, return the top (first) element
			cout << "KEY: " << Q.back().P_KEY << endl;        // or return A[0];
			cout << "User Id: " << Q.back().U_ID << endl;
			cout << "Operation: " << Q.back().Operation << endl;
			return Q.back().P_KEY;
		}
	}

	void showQueue()  //display priority queue
	{
		cout << "--------------QUEUE-----------" << endl;
		for (auto i = Q.begin(); i != Q.end(); i++)
		{
			cout << "KEY: " << i->P_KEY << endl;
			cout << "User Id: " << i->U_ID << endl;
			cout << "Operation: " << i->Operation << endl << endl;
		}
	}
};

///////////////////////////////////FILE//////////////////////////////
class File
{
public:
	int ID; //file id
	PriorityQueue<QueueNode> X_waiting; //priorty queue for waiting
	PriorityQueue<QueueNode> A_Granted; //priorty queue for access granted
	//id, waiting list
	File() // Default Constructor
	{
		ID = 0;
		//X = nullptr;
	}

	void InsertFile(int i, PriorityQueue<QueueNode> P, PriorityQueue<QueueNode> V) //insert
	{
		ID = i;
		X_waiting = P;
		A_Granted = V;
	}

	File(int i, PriorityQueue<QueueNode> P, PriorityQueue<QueueNode> V) //parametrised constructor
	{
		ID = i;
		X_waiting = P;
		A_Granted = V;

	}


	void print() //print function
	{
		cout << "File ID : " << ID << endl;
		cout << "Access granted to :";
		A_Granted.showQueue();
		cout << "Waiting Users :";
		X_waiting.showQueue();
		cout << endl;
	}
};

///////////////////////////////////HASH TABLE///////////////////////////

template<typename f>
class HashTable
{
public:
	list<f> arr[10]; //Array for Hash
	int Hash_Size; //Hash Size


	HashTable(int s = 10)
	{
		Hash_Size = s;
		/*for (int i = 0; i < s;i++)
		{
			arr[i] = nullptr;
		}*/
	}

	int calHash(int k) //Hashsize = 10;
	{
		int r = k % Hash_Size;
		return r;
	}

	void insertfile(f file) //insert a file
	{
		if (file.ID >= 5000 && file.ID <= 99999)
		{
			int res = calHash(file.ID);
			//int i = 0;
			auto i = arr->begin();
			for (i = arr[res].begin(); i != arr[res].end(); i++)
			{

				if (i->ID == file.ID) {
					return;
				}
			}
			arr[res].push_back(file);
		}
		else
		{
			cout << "Invalid File Id." << endl;
		}
	}

	void Request(int UserID, int FileId, int Pri, string op) //For integer priority
	{
		if (UserID >= 0 && UserID <= 10000 && Pri >= 0 && Pri <= 100)
		{
			//find file		
			int res = calHash(FileId);
			auto itr = arr[res].begin();
			if (arr[res].begin() == arr[res].end())
			{
				cout << "List is Empty." << endl;
				return;
			}
			while (itr != arr[res].end() && itr->ID != FileId)
			{
				itr++;
			}
			if (itr == arr[res].end())
			{
				cout << "File does not Exist." << endl;
			}
			else
			{

				QueueNode r(Pri, UserID, op);
				if (itr->A_Granted.empty() == 1) {
					itr->A_Granted.Insert(r);
					//itr->A_Granted.Q.end().A_granted = true;

				}
				else
				{
					if (itr->A_Granted.Q[0].Operation != "Write" && op == "Read")
					{
						itr->A_Granted.Insert(r);

					}
					else
					{

						itr->X_waiting.Insert(r);
					}


				}
			}
		}
		else
		{
			cout << "INVALID INPUT." << endl;
		}
	}

	void Request(int UserID, int FileId, string Pri, string op) //For string priority
	{
		if (UserID >= 0 && UserID <= 10000)
		{
			//find file		
			int res = calHash(FileId);
			auto itr = arr[res].begin();
			if (arr[res].begin() == arr[res].end())
			{
				cout << "List of files is Empty";
				return;
			}
			while (itr != arr[res].end() && itr->ID != FileId)
			{
				itr++;
			}
			if (itr == arr[res].end())
			{
				cout << "File does not Exist." << endl;
				return;
			}
			else
			{
				int priority;

				// h->write.  A_g
				// h->read 
				//
				if (Pri == "Highest" || Pri == "highest" || Pri == "HIGHEST")
				{
					priority = itr->X_waiting.FindMax() + 1;
					QueueNode r(priority, UserID, op);
					if (itr->A_Granted.empty() == 1) {
						itr->A_Granted.Insert(r);
						//itr->A_Granted.Q(priority).A_granted = true;

					}
					else
					{

						if (itr->A_Granted.Q[0].Operation != "Write" && op == "Read")
						{
							itr->A_Granted.Insert(r);

						}
						else
							itr->X_waiting.Insert(r);
					}

				}
				else if (Pri == "Lowest" || Pri == "lowest" || Pri == "LOWEST")
				{
					int count = itr->X_waiting.Q.size();

					priority = itr->X_waiting.FindMin();
					QueueNode r(priority, UserID, op);

					//QueueNode r(Pri, UserID, op);
					if (itr->A_Granted.empty() == 1) {
						itr->A_Granted.Insert(r);
						//itr->A_Granted.Q(priority).A_granted = true;

					}
					else
					{
						itr->X_waiting.Insert(r);
					}
				}
			}
		}
		else
		{
			cout << "INVALID INPUT." << endl;
		}
	}

	void Release(int UserID, int FileId) //release a file
	{
		int res = calHash(FileId);
		auto itr = arr[res].begin();

		if (arr[res].begin() == arr[res].end())
		{
			cout << "List Empty";
			return;
		}
		while (itr != arr[res].end() && itr->ID != FileId)
		{
			itr++;

		}

		QueueNode prev;
		int last = itr->A_Granted.size();
		int i = 0;
		while (i < last)

		{


			if (UserID == itr->A_Granted.Q.at(i).U_ID)
			{
				itr->A_Granted.Q.erase(itr->A_Granted.Q.begin() + i);
				if (itr->X_waiting.empty())
					return;
				bool b = false;
				if (itr->A_Granted.empty() == 1)
				{
					bool W = false;
					auto o = itr->X_waiting.Q.begin();
					for (o = itr->X_waiting.Q.begin(); o != itr->X_waiting.Q.end(); o++) {

						if (o->Operation == "Write") {

							itr->A_Granted.Q.push_back(itr->X_waiting.Q[0]);
							itr->X_waiting.Q.erase(itr->X_waiting.Q.begin() + 0);
							b = true;
							break;
						}
						else
							break;
					}
					if (b == true)
					{
						break;
					}
					o = itr->X_waiting.Q.begin();
					if (o->Operation == "Read")
					{

						while (itr->X_waiting.empty() != 1) {
							itr->A_Granted.Q.push_back(itr->X_waiting.Q[0]);
							itr->X_waiting.Q.erase(itr->X_waiting.Q.begin() + 0);

							if (itr->X_waiting.empty() != 1) {
								o = itr->X_waiting.Q.begin();
								if (o->Operation == "Write")
									break;
							}
						}


					}


				}
				else
					break;
			}
			i++;
		}
	}

	void DeleteFile(int fileid) //delete a file
	{
		bool del = false;
		for (int a = 0; a < Hash_Size; a++)
		{
			auto itr = arr[a].begin();
			int i = 0;
			for (itr = arr[a].begin(); itr != arr[a].end(); itr++)
			{
				if (itr->ID == fileid && itr->A_Granted.empty() == 1)
				{
					arr[a].erase(itr);
					del = true;
					break;
				}
				i++;
			}
			if (del == true)
			{
				cout << "File Deleted Successfully!" << endl;
				break;

			}
		}
	}

	void PrintHashTable() //prints the hash table
	{
		/*
			cout<<"H"<<i<<"->"<<"FILE"<<FILE ID
		*/


		for (int a = 0; a < Hash_Size; a++)
		{
			cout << "Hash Value: " << a << endl;
			auto itr = arr[a].begin();
			bool check = false;
			for (auto itr = arr[a].begin(); itr != arr[a].end(); itr++)
			{
				cout << "File " << itr->ID << " , ";
				cout << "Access Granted to ";
				//itr->X.Q.at(i).A_granted = false;
					//X_waiting
				int last = itr->A_Granted.size();
				int i = 0;
				while (i < last)
				{
					//while (itr->X.Q.at(i).A_granted == true)
					//{
					cout << "User " << itr->A_Granted.Q.at(i).U_ID << " (" << itr->A_Granted.Q.at(i).Operation << ")   ";
					check = true;
					i++;

					//}

				}
				//if()
				cout << endl;
				last = itr->X_waiting.size();
				i = 0;
				while (i < last)
				{
					//while (itr->X.Q.at(i).A_granted == true)
					//{
					if (i == 0)
						cout << "Next User " << itr->X_waiting.Q.at(i).U_ID << " (" << itr->X_waiting.Q.at(i).Operation << ")   ";
					check = true;
					i++;

					//}

				}
				cout << "waiting " << i << " Users" << endl;
			}
		}
	}

	void load(string file) //load the file
	{
		fstream in;
		in.open(file, ios::in);
		double ID, U_id;
		int p;
		File temp;
		HashTable<File> temp2;
		char op;
		if (in.is_open())
		{
			while (!in.eof())
			{
				//cout << "yessss";
				while (in >> ID) {

					in >> U_id;
					in >> p;
					in >> op;
					temp.ID = ID;
					temp2.insertfile(temp);
					if (op == 'W')
					{
						//QueueNode B(p, U_id, "Write");

						//temp.ID = ID;
						//temp2.insertfile(temp);

						temp2.Request(U_id, ID, p, "Write");
						//nt UserID, int FileId, int Pri, string op
					}
					else if (op == 'R')
					{
						//QueueNode B(p, U_id, "Write");
						File temp;
						//temp.ID = ID;
						//temp2.insertfile(temp);

						temp2.Request(U_id, ID, p, "Read");
						//nt UserID, int FileId, int Pri, string op
					}
				}
				if (in.eof()) {
					break;
				}
			}

		}
		else
			cout << "NOT FOUND" << endl;


		temp2.PrintHashTable();
		cout << endl << endl << endl << endl;
		*this = temp2;


	}
};

int main()
{
	int choice = 0;
	int userid;
	int fileid;
	char cho;
	int priority;
	string priority1;
	string operation;

	HashTable<File> temp2;
	QueueNode A(1, 1, "Read"); //P_KEY, id, choice
	QueueNode B(2, 2, "Write");
	QueueNode C(3, 3, "Read");
	QueueNode D(4, 4, "Write");
	PriorityQueue<QueueNode> P;
	vector<QueueNode> vec;
	vec.push_back(A);
	vec.push_back(B);
	P.setQueue(vec);

	PriorityQueue<QueueNode> V;
	vector<QueueNode> vec1;
	vec1.push_back(D);
	vec1.push_back(C);
	P.setQueue(vec);
	File tempp;
	File X;

	do
	{

		cout << "|---------------MENU---------------|" << endl;
		cout << "(1) To LOAD the data." << endl;
		cout << "(2) To INSERT a file." << endl;
		cout << "(3) To DELETE a file." << endl;
		cout << "(4) To REQUEST ACCESS." << endl;
		cout << "(5) To RELEASE a file." << endl;
		cout << "(6) To PRINT the hash table." << endl;
		cout << "(7) To EXIT." << endl;
		cout << "|----------------------------------|" << endl;

		cout << "\n ENTER YOUR CHOICE -> ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			temp2.load("File.txt");
			break;
		case 2:
			cout << "Enter FILE ID: ";
			cin >> fileid;
			//X.InsertFile(fileid, P, V);

			tempp.ID = fileid;
			temp2.insertfile(tempp);

			break;
		case 3:
			cout << "Enter FILE ID: ";
			cin >> fileid;
			temp2.DeleteFile(fileid);
			break;
		case 4:

			cout << "Enter USER ID: ";
			cin >> userid;
			cout << "Enter FILE ID: ";
			cin >> fileid;
			cout << "Enter operation: ";
			cin >> operation;
			cout << "Do you want to add priotity as a integer? (Y/N) ";
			cin >> cho;
			if (cho == 'Y' || cho == 'y')
			{
				cout << "Enter priority: ";
				cin >> priority;
				temp2.Request(userid, fileid, priority, operation);
			}
			else
			{
				cout << "Enter priority: ";
				cin >> priority1;
				temp2.Request(userid, fileid, priority1, operation);
			}
			break;
		case 5:

			cout << "Enter USER ID: ";
			cin >> userid;
			cout << "Enter FILE ID: ";
			cin >> fileid;
			temp2.Release(userid, fileid);
			break;
		case 6:
			temp2.PrintHashTable();
			break;
		case 7:
			cout << "-----TERMINATING PROGRAM-----\n";
			break;
		}

	} while (choice != 7);

	////QueueNode A(1, 1, "Read"); //P_KEY, id, choice
	////QueueNode B(2, 2, "Write");
	////QueueNode C(3, 3, "Read");
	////QueueNode D(4, 4, "Write");
	////QueueNode E(5, 5, "Read");
	////QueueNode F(6, 5, "Write");
	/////////////////////////////////////////////////////////////////////////////////////

	//File temp;
	//temp.ID = 5100;
	//HashTable<File> temp2;
	//temp2.insertfile(temp);
	// temp;
	//temp.ID = 5000;
	//temp2.insertfile(temp);
	// temp;
	//temp.ID = 5101;
	//temp2.insertfile(temp);
	// temp;
	//temp.ID = 5200;
	//temp2.insertfile(temp);
	// temp;
	//temp.ID = 5077;
	//temp2.insertfile(temp);

	////temp2.insertfile(temp);
	//temp2.Request(1, 5807, 1, "Read");
	//temp2.Request(3, 5100, 2, "Write");
	//temp2.Request(5, 5100, 3, "Read");
	//temp2.Request(15, 5100, 4, "Read");
	//temp2.Request(12, 5100, 1, "Read");
	//temp2.Request(2, 5201, 4, "Write");
	//temp2.Request(4, 5077, 5, "Read");
	//temp2.Release(15, 5100);
	//temp2.Release(5, 5100);
	//temp2.Release(3, 5100);
	//temp2.PrintHashTable();
	//cout << endl << endl << endl << endl;
	//vector<QueueNode> vec;
	//vec.push_back(A);
	//vec.push_back(B);
	//vec.push_back(C);
	//vec.push_back(D);
	//vec.push_back(E);
	//vec.push_back(F);
	//PriorityQueue<QueueNode> pq1;
	//pq1.setQueue(vec);
	//pq1.BuildQueue();
	//cout << "Size: " << pq1.size() << endl;
	//if (pq1.empty() == 1)
	//{
	//	cout << "HEAP IS EMPTY.!!" << endl;
	//}
	//else
	//{
	//	cout << "Heap is not empty." << endl;
	//}
	//pq1.showQueue();
	//pq1.FindMin();
	//pq1.FindMax();
	//pq1.ExtractMax(pq1);
	//pq1.FindMax();
	//pq1.ExtractMax(pq1);
	//pq1.FindMax();
	//pq1.ExtractMax(pq1);
	//pq1.FindMin();
	//pq1.FindMax();
	//pq1.ExtractMax(pq1);
	//pq1.FindMax();
	//pq1.ExtractMax(pq1);
	//pq1.FindMax();
	//pq1.FindMin();
	//pq1.Insert(E);
	//cout << pq1.size() << endl;
	//pq1.FindMax();
	//pq1.showQueue();


	///*File Q;
	//Q.ID = 5;*/
	//

	//HashTable<File> H(5);
	////H.insertfile(Q);
	//
	system("pause");
	return 0;
}