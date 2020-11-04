//Shang-Chun,Lin  CS163 program#5 assignment
#include "graph.h"

using namespace std;

//the purpose of this file is to test the structs and classes that I have declared in .h file (working as client program)

int main()
{
	table graph;
	add_a_step hold;	//representing to_add as the argument what we got from the user
	hold.title = NULL;
	hold.notes = NULL;
	char * key_value;

	int answer = 0;
	cout<<"Please type a integer number to choose what you want to do."<<endl<<endl
	<<"1 for adding a new step (vertice)                         , 2 for inserting a connection between two vertices (edge), "<<endl
	<<"3 for typing in a vertice to display all adjacent vertices, 4 for quitting the program."<<endl;
	cin>>answer;
	cin.ignore(100,'\n');

	while(answer != 4)
	{
		hold.title = new char[SIZE];
		hold.notes = new char[SIZE];
		key_value = new char[SIZE];

		if(answer == 1)
		{
			cout<<"Please type in the name of the step."<<endl;
			cin.get(hold.title,SIZE-1,'\n');
			cin.ignore(100,'\n');

			cout<<"Please type in the content of the step."<<endl;
			cin.get(hold.notes,SIZE-1,'\n');
			cin.ignore(100,'\n');

			cout<<"We have added "<<graph.insert_vertex(hold)<<" vertex in the graph."<<endl<<endl;
			
			cout<<"There are "<<endl<<graph.display_adjacency(hold.title)<<" vertex on the path from "<<hold.title<<" to "<<endl
			<<"other adjacent vertex and those adjacent vertex to its adjacent vertex in the graph."<<endl<<endl;
		}

		if(answer == 2)
		{
			cout<<"Please type in a name of the step(vertex) to determine the starting point."<<endl;
			cin.get(hold.title,SIZE-1,'\n');
			cin.ignore(100,'\n');

			cout<<"Please type in a name of the step(vertex) to determine the ending point."<<endl;
			cin.get(key_value,SIZE-1,'\n');
			cin.ignore(100,'\n');

			cout<<"We have built"<<graph.insert_edge(hold.title,key_value)<<" connection from "<<hold.title<<" to "<<key_value<<endl<<endl;
	
			cout<<"There are "<<endl<<graph.display_adjacency(hold.title)<<" vertex on the path from "<<hold.title<<" to "<<endl
			<<"other adjacent vertex and those adjacent vertex to its adjacent vertex in the graph."<<endl<<endl;
		}

		if(answer == 3)
		{
			cout<<"Please type in a name of the step(vertex) to display all possible relations in the graph."<<endl;
			cin.get(hold.title,SIZE-1,'\n');
			cin.ignore(100,'\n');

			cout<<"There are "<<endl<<graph.display_adjacency(hold.title)<<" vertex on the path from "<<hold.title<<" to "<<endl
			<<"other adjacent vertex and those adjacent vertex to its adjacent vertex in the graph."<<endl<<endl;
		}

		cout<<"Please type a integer number to choose what you want to do."<<endl<<endl
		<<"1 for adding a new step (vertice)                         , 2 for inserting a connection between two vertices (edge), "<<endl
		<<"3 for typing in a vertice to display all adjacent vertices, 4 for quitting the program."<<endl;
		cin>>answer;
		cin.ignore(100,'\n');

		if(hold.title)		//reset
		{
			hold.title[0] = '\0';
			delete []hold.title;
			hold.title = NULL;
		}
		if(hold.notes)
		{
			hold.notes[0] = '\0';
			delete []hold.notes;
			hold.notes = NULL;
		}
		if(key_value)
		{
			key_value[0] = '\0';
			delete []key_value;
			key_value = NULL;
		}
	}
	return 0;
}
