//Shang-Chun, Lin  cs163 program#5

#include <iostream>
#include <cctype>
#include <cstring>

//This .h file supports steps(a title and notes) for the user to solve a problem.

const int SIZE = 201;
struct vertex;

struct add_a_step
{
	char * title;
	char * notes;
};

class step
{
	public:
		step();
		~step();
		int insert(const add_a_step & to_add);
		bool compare(char * key_value);
		int display(char * key_value);
		int find_title(char * & found);
	private:
		char * title;
		char * notes;
};

struct node
{
	vertex * adjacent;
	node * next;
};

struct vertex
{
	step * a_step;
	node * head;
};

class table
{
	public:
		table(int size = 10);
		~table();
		int delete_all();
		int insert_vertex(const add_a_step & to_add);
		int find_location(char * key);
		int insert_edge(char * current_vertex,char * to_attach);
		int display_adjacency(char * key_value);
	private:
		int delete_all(node * head);
		int find_location(int index,char * key);
		int display_adjacency(node * head,char * key_value);
		vertex * adjacency_list;
		int list_size;
};
