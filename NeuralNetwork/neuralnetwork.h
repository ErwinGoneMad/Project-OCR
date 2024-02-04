#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int init(void);
int dinit(void);

void saveModel(char *filename);
int create_architecture(void);
int initialize_weights(void);
void feed_input(int i);
void train_neural_net(void);
void forward_prop(void);
void compute_cost(int i);
void back_prop(int p);
void update_weights(void);
void xor_table(void);
void xor_result(void);
void test_nn(void);
int initialize_trained_weights(char *filename);
void test_nn2(void);
int initialize_dummy_weights(void);
void use_nn(int c, char *v[]);

typedef struct layer_t
{
	int num_neu;
	struct neuron_t *neu; 
} layer;

layer create_layer(int num_neurons);

typedef struct neuron_t
{
	float actv;
	float *out_weights;
	float bias;
	float z;

	float dactv;
	float *dw;
	float dbias;
	float dz;

	// TODO: Add function pointer for destructor

} neuron;

neuron create_neuron(int num_out_weights);

#endif
