#include "neuralnetwork.h"

layer create_layer(int number_of_neurons)
{
	layer lay;
	lay.num_neu = -1;
	lay.neu = (struct neuron_t *) malloc(number_of_neurons * sizeof(struct neuron_t));
	return lay;
}


neuron create_neuron(int num_out_weights)
{
	neuron neu;

	neu.actv = 0.0;
	neu.out_weights = (float*) malloc(num_out_weights * sizeof(float));
	neu.bias=0.0;
	neu.z = 0.0;

	neu.dactv = 0.0;
	neu.dw = (float*) malloc(num_out_weights * sizeof(float));
	neu.dbias = 0.0;
	neu.dz = 0.0;

	return neu;
}



