//Shang-Chun, Lin  cs163 program#5
#include "graph.h"
using namespace std;

//the purpose of this file is to implement the classes that I have declared in .h file (working as client program)

//constructor for each data in each node
step::step()
{
	title = NULL;
	notes = NULL;
}

//destructor for each data in each node
step::~step()
{
	if(title)
	{
		title[0] = '\0';
		delete []title;
		title = NULL;
	}
	if(notes)
	{
		notes[0] = '\0';
		delete []notes;
		notes = NULL;
	}
}

//insert a data in a node
int step::insert(const add_a_step & to_add)
{
	if(title || notes || !to_add.title || !to_add.notes)
	{
		return 0;
	}
	title = new char[strlen(to_add.title)+1];
	strcpy(title,to_add.title);
	notes = new char[strlen(to_add.notes)+1];
	strcpy(notes,to_add.notes);
	return 1;
}

//compare the key_value is same as the title in the node
bool step::compare(char * key_value)
{
	if(!title)
	{
		return false;
	}
	if(strcmp(title,key_value) == 0)
	{
		return true;
	}
	return false;
}

//display the data which are in the node
int step::display(char * key_value)
{
	if(!title || !notes)
	{
		return 0;
	}
	cout<<"(Showing the starting point : "<<key_value<<")"<<endl;
	cout<<"Step : "<<title<<endl;
	cout<<"Content : "<<notes<<endl;
	return 1;
}

//find the title in the node and pass it as the argument
int step::find_title(char * & found)
{
	if(!title)
	{
		return 0;
	}
	found = new char[strlen(title)+1];
	strcpy(found,title);
	return 1;
}

//constructor for the whole graph
table::table(int size)
{
	adjacency_list = new vertex[size];
	for(int i=0;i<size;++i)
	{
		adjacency_list[i].a_step = NULL;
		adjacency_list[i].head = NULL;
	}
	list_size = size;
}

//destructor for the whole graph
table::~table()
{
	int count = 0;
	count = delete_all();
	list_size = 0;
}

//serve for the destructor, deleting all data and nodes (this one is a wrapper function)
int table::delete_all()
{
	if(!adjacency_list)
	{
		return 0;
	}
	int count = 0;
	for(int i=0;i<list_size;++i)
	{
		if(adjacency_list[i].a_step)			//delete the vertex
		{
			adjacency_list[i].a_step->~step();
		}
		if(adjacency_list[i].head)			//delete the nodes following the vertex
		{
			count += delete_all(adjacency_list[i].head);
		}
	}
	delete []adjacency_list;
	adjacency_list = NULL;
	return count;
}

//serve for the destructor, deleting all data and nodes (this one is recursion)
int table::delete_all(node * head)
{
	if(!head)
	{
		return 0;
	}
	node * hold = head->next;
	head->adjacent = NULL;
	head->next = NULL;
	delete head;
	head = hold;
	if(!head)
	{
		return 1;
	}
	return delete_all(head->next) + 1;
}

//insert a vertex into the graph (the very first vertex through the paths)
int table::insert_vertex(const add_a_step & to_add)
{
	if(!to_add.title || !to_add.notes)
	{
		return 0;
	}
	if(!adjacency_list)
	{
		return 0;
	}
	int i = 0;
	while(adjacency_list[i].a_step && i<list_size)
	{
		++i;
	}
	
	if(i == list_size)
	{
		return 0;
	}
	step * temp = new step;
	if(temp->insert(to_add))
	{
		adjacency_list[i].a_step = temp;
		return 1;
	}
	delete []temp;
	return 0;
	return i;	
}

//find the vertex with the key (this one is a wrapper function)
int table::find_location(char * key)
{
	if(!adjacency_list || !key)
	{
		return -1;
	}
	int index = 0;
	return find_location(index,key);
}

//find the vertex with the key (this one is recursion)
int table::find_location(int index,char * key)
{
	if(index == list_size)
	{
		return -1;
	}
	if(adjacency_list[index].a_step->compare(key))
	{
		return index;
	}
	++index;
	return find_location(index,key);
}

//build a connection(edge) between two vertex
int table::insert_edge(char * current_vertex,char * to_attach)
{
	int index1 = find_location(current_vertex);
	int index2 = find_location(to_attach);
	node * temp = new node;
	temp->adjacent = &(adjacency_list[index2]);
	temp->next = adjacency_list[index1].head;
	adjacency_list[index1].head = temp;
	return 1;
}

//display the path with breadth first algorithm starting from the key valaue (this one is a wrapper function)
int table::display_adjacency(char * key_value)
{
	if(!key_value)
	{
		return 0;
	}
	int index = find_location(key_value);
	int count = 0;
	if(!adjacency_list[index].a_step)
	{
		return 0;
	}
	if(!adjacency_list[index].head)
	{
		count = adjacency_list[index].a_step->display(key_value);
		return count;
	}
	count = adjacency_list[index].a_step->display(key_value);
	return display_adjacency(adjacency_list[index].head,key_value);
}

//display the path with breadth first algorithm starting from the key valaue (this one is recursion)
int table::display_adjacency(node * head,char * key_value)	//using recursion to display all adjacent vertex with "breadth first"
{
	if(!head)
	{
		return 0;
	}
	int count = 1;
	count += head->adjacent->a_step->display(key_value);	//call function
	count += display_adjacency(head->next,key_value);	//recursion

	//after recursion call
	
	char * local_key = NULL;
	if(head->adjacent->a_step->find_title(local_key))
	{
		count += display_adjacency(local_key);		//call the wrapper function again
		--count;					//count the local_key twice, so need to minus 1
	}
	return count;
}

