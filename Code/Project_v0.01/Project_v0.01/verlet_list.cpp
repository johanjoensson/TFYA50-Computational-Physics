#include "verlet_list.h"

verlet_list::verlet_list()
{
	verlet_skin = 0;
	data = 0;
	next = 0;
}

verlet_list::verlet_list(float r)
{
	verlet_skin = r;

	data = 0;
	next = 0;
}

void verlet_list::set_verlet_skin(float r){
	verlet_skin = r;
}
void verlet_list::set_dimensions(float x, float y, float z)
{
	x_dim = x;
	y_dim = y;
	z_dim = z;
}

void verlet_list::add_atom(verlet_list atom)
{
	verlet_list *next_atom = this->next;
	
	vector_3d r = this->data->pos.diff(atom.data->pos, x_dim, y_dim, z_dim);

	if(r*r < verlet_skin*verlet_skin){
		this->next = new verlet_list();
		this->next->data = atom.data;
		this->next->next = next_atom;
	}
}

/* This seems to work, should limit our potential memory leaks at least */
void verlet_list::clear_verlet_list()
{
	verlet_list *current = this->next;
	verlet_list *previous = 0;

	while(current != 0){
		previous = current;
		current = current->next;
		delete previous;
	}

	this->next = 0;
}
