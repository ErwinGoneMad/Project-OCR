#include "mnist_parse.h"
#include "neuralnetwork.h"
#include "pixel_operations.h"
#include "imageToNeural.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <time.h>

layer *lay = NULL;
int num_layers = 4;
int num_neurons[4]  = {784, 100, 50, 10};
float alpha = 0.15;
float *cost;
float full_cost;
float * input[60000];
float desired_outputs[60000][10];
int num_training_ex = 10000;
int n=1;
float* test;


int main(int argc, char * argv[])
{
   
    srand( time( NULL ) );

    mnist_imageparse("./network_input", input);
    mnist_labelparse("./network_output", desired_outputs);

    // Initialize the neural network module
    create_architecture();
 	if(argc == 2)
    {
        FILE * NNtrd;
        if((NNtrd = fopen(argv[1], "r")))
        {
            initialize_trained_weights(argv[1]);
            test_nn();
            return 0;
        }
    }

	/*
	if (argc > 2)
	{
		FILE *NNtrd;
		if((NNtrd = fopen(argv[1], "r")))
		{
			initialize_trained_weights(argv[1]);
			use_nn(argc, argv);
			return 0;
		}
	}*/

    cost = (float *) malloc(num_neurons[num_layers-1] * sizeof(float));
    memset(cost,0,num_neurons[num_layers-1]*sizeof(float));

    train_neural_net();
    test_nn();
    saveModel("trained");

    return 0;
}

/*
 * Function: feed_input
 * ----------------------------
 *   Different inputs, pre created
 *   In our case, we only need it to learn XOR
 *   (Can also learn other logic gates)
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void feed_input(int i)
{
	//float *p= test;
    for(int j = 0; j < num_neurons[0]; j++)
    {
        lay[0].neu[j].actv = input[i][j];
		//lay[0].neu[j].actv = *p;
		//p++;
    }
}

/*
 * Function: feed_input
 * ----------------------------
 *   Different inputs, pre created
 *   In our case, we only need it to learn XOR
 *   (Can also learn other logic gates)
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 
void feed_input_train(int i, char* v[])
{
	float array[SIZE];
    for(int j = 0; j < SIZE; j++)
       array[j] = 0;
    SDL_Surface *img = loadImage(v[i]);
    imageToNeural(img,array);

    test = array;

	float *p= test;
    for(int j = 0; j < num_neurons[0]; j++)
    {
        //lay[0].neu[j].actv = input[i][j];
		lay[0].neu[j].actv = *p;
		p++;
    }
}*/

/*
 * Function: create_network
 * ----------------------------
 *   creates the network
 *   allocates memory
 *   calls create_layer and create_neuron
 *
 *    arg1: -
 *    .....
 *
 *   returns: 0
 */
int create_architecture()
{
    lay = (layer*) malloc(num_layers * sizeof(layer));

    for(int i = 0; i < num_layers; i++)
    {
        lay[i] = create_layer(num_neurons[i]);  
        lay[i].num_neu = num_neurons[i];

        for(int j = 0; j < num_neurons[i]; j++)
        {
            if(i < (num_layers-1)) 
            {
                lay[i].neu[j] = create_neuron(num_neurons[i+1]);
            }
        }
    }
    // Initialize the weights
    initialize_weights();
    return 0;
}

double true_rand()
{
    double x = 0;
    double y, u, n, m;
    u = 0.0;
    while(u >= 1.0 || u == 0.0)
    {
        n = (double)rand();
        x = pow(-1.0, n) * ((double) rand()) / ((double) RAND_MAX);
        m = (double)rand();
        y = pow(-1.0, m) * ((double) rand()) / ((double) RAND_MAX);
        u = x * x + y * y;
    }
    
    return x * sqrt((-2 * log(u)) / u);
}

/*
 * Function: initialize_weights
 * ----------------------------
 *   For each neuron of each layer, exept the output layer
 *   randomly generates weights
 *
 *    arg1: -
 *    .....
 *
 *   returns: 0
 */
int initialize_weights(void)
{
    int i,j,k;

    for(i=0;i<num_layers-1;i++)
    {
        
        for(j=0;j<num_neurons[i];j++)
        {
            for(k=0;k<num_neurons[i+1];k++)
            {
                
                lay[i].neu[j].out_weights[k] = true_rand();
                
                lay[i].neu[j].dw[k] = 0.0;
            }

            if(i>0) 
            {
                lay[i].neu[j].bias = true_rand();
                
            }
        }
    }   
    
    for (j=0; j<num_neurons[num_layers-1]; j++)
    {
        lay[num_layers-1].neu[j].bias = true_rand();
        
    }

    return 0;
}

/*
 * Function: initialize_trained_weights
 * ----------------------------
 *   For each neuron of each layer, exept the output layer
 *   randomly generates weights
 *
 *    arg1: -
 *    .....
 *
 *   returns: 0
 */
int initialize_trained_weights(char *filename)
{
    //Network n;
	FILE* filePointer;
	filePointer = fopen(filename, "r");


    int i,j,k;

    for(i=0;i<num_layers-1;i++)
    {
        
        for(j=0;j<num_neurons[i+1];j++)
        {
            for(k=0;k<num_neurons[i];k++)
            {
                
                fscanf(filePointer,"%f ",&lay[i].neu[k].out_weights[j]);
            }
            fscanf(filePointer,"%f",&lay[i+1].neu[j].bias);
        }
    }   
    return 0;
}

/*
 * Function: train_neural_net
 * ----------------------------
 *   Trains the neural network, calling different functions
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void train_neural_net(void)
{

    printf("Training...\n\n");

    // Gradient Descent
    for(int it = 0; it < 2000; it++)
    {
		if (it == 500) printf("25/100 of training done\n\n");
		if (it == 1000) printf("50/100 of training done\n\n");
		if (it == 1500) printf("75/100 of training done\n\n");
        for(int i = 0; i < 40; i++)
        {
            feed_input(i);
            forward_prop();
            compute_cost(i);
            back_prop(i);
            if(i % 10 == 0)
            {
                update_weights();
            }
        }
    }
    printf("\n");
}


/*
 * Function: update_weights
 * ----------------------------
 *   Updates weight with the learning rate (Tested with a learning rate of 3 and it didn't work)
 *   Current learning rate : 0.3
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void update_weights(void)
{
    for(int i = 0; i < num_layers-1; i++)
    {
        for(int j = 0; j < num_neurons[i]; j++)
        {
            for(int k = 0; k < num_neurons[i+1]; k++)
            {
                lay[i].neu[j].out_weights[k] = 
					lay[i].neu[j].out_weights[k] - 
						(alpha * lay[i].neu[j].dw[k]);
                lay[i].neu[j].dw[k] = 0;
            }
            // Update Bias
            lay[i].neu[j].bias = lay[i].neu[j].bias - (alpha * lay[i].neu[j].dbias);
            lay[i].neu[j].dbias = 0;
        }
    }
}

/*
 * Function: forward_propagation_train
 * ----------------------------
 *    Calls for activations function
 *    Computes the output of neuron, either 1 or 0
 *    Depends if the number is largely positive or negative
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void forward_prop(void)
{
    for(int i = 1; i < num_layers; i++)
    {   
        for(int j = 0; j < num_neurons[i]; j++)
        {
            lay[i].neu[j].z = lay[i].neu[j].bias;

            for(int k = 0; k < num_neurons[i-1]; k++)
            {
                lay[i].neu[j].z += ((lay[i-1].neu[k].out_weights[j])* (lay[i-1].neu[k].actv));
            }

            // Relu Activation Function for Hidden Layers
            if(i < num_layers-1)
            {
                if((lay[i].neu[j].z) < 0)
                {
                    lay[i].neu[j].actv = 0;
                }
                else
                {
                    lay[i].neu[j].actv = 1;
                }
            }
            
            // Sigmoid Activation function for Output Layer
            else
            {
                lay[i].neu[j].actv = 1/(1+exp(-lay[i].neu[j].z));
            }
        }
    }
}

/*
 * Function: compute_cost
 * ----------------------------
 *   computes the cost,
 *   quantifier to find weights and biases
 *
 *    arg1: num outputs
 *    .....
 *
 *   returns: -
 */
void compute_cost(int i)
{
    int j;
    float tmpcost=0;
    float tcost=0;

    for(j=0;j<num_neurons[num_layers-1];j++)
    {
        tmpcost = desired_outputs[i][j] - lay[num_layers-1].neu[j].actv;
        cost[j] = (tmpcost * tmpcost)/2;
        tcost = tcost + cost[j];
    }   

    full_cost = (full_cost + tcost)/n;
    n++;
}

/*
 * Function: b_propagation
 * ----------------------------
 *   Fast way of computing the cost function
 *
 *    arg1: num of outputs
 *    .....
 *
 *   returns: -
 */
void back_prop(int p)
{
    // Output Layer
    for(int j = 0; j < num_neurons[num_layers-1]; j++)
    {           
        lay[num_layers-1].neu[j].dz = (lay[num_layers-1].neu[j].actv - desired_outputs[p][j]) * (lay[num_layers-1].neu[j].actv) * (1- lay[num_layers-1].neu[j].actv);

        for(int k = 0; k < num_neurons[num_layers-2]; k++)
        {   
            lay[num_layers-2].neu[k].dw[j] += (lay[num_layers-1].neu[j].dz * lay[num_layers-2].neu[k].actv);
            lay[num_layers-2].neu[k].dactv = lay[num_layers-2].neu[k].out_weights[j] * lay[num_layers-1].neu[j].dz;
        }
            
        lay[num_layers-1].neu[j].dbias += lay[num_layers-1].neu[j].dz;           
    }

    // Hidden Layers
    for(int i = num_layers - 2; i > 0; i--)
    {
        for(int j = 0; j < num_neurons[i]; j++)
        {
            if(lay[i].neu[j].z >= 0 )
            {
                lay[i].neu[j].dz = 1 * lay[i].neu[j].dactv; 
            }  
            else
            {
                lay[i].neu[j].dz = 0;
            }

            for(int k = 0; k < num_neurons[i-1]; k++)
            {
                lay[i-1].neu[k].dw[j] = lay[i].neu[j].dz * lay[i-1].neu[k].actv;    
                
                if(i>1)
                {
                    lay[i-1].neu[k].dactv = lay[i-1].neu[k].out_weights[j] * lay[i].neu[j].dz;
                }
            }

            lay[i].neu[j].dbias = lay[i].neu[j].dz;
        }
    }
}

void saveModel(char *filename)
{
	printf("Weights successfully saved\n\n");

	FILE *f = fopen(filename, "wb");
	for(int layer=0;layer<num_layers-1;layer++)
    {
		fprintf(f,"\n");
		for(int node=0;node<num_neurons[layer+1];node++)
        {
			for(int i=0;i<num_neurons[layer];i++)
            {
				fprintf(f,"%f ",lay[layer].neu[i].out_weights[node]);
			}	
            fprintf(f,"%f",lay[layer+1].neu[node].bias);
			fprintf(f,"\n");
		}
    }

	fclose(f);
}

/*
 * Function: test_neuralnetwork
 * ----------------------------
 *   Called after the training,
 *   Test values of outputs according to inputs
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void test_nn(void) 
{
    for(int i = 0; i < 20; i++)
    {
        printf("Input %d\n\n", i);
        for(int j = 0; j < num_neurons[0]; j++)
        {
            lay[0].neu[j].actv = input[i][j];
        }
        forward_prop();

        float max = 0;
        int result = 0;
        for(int j = 0; j < num_neurons[num_layers-1]; j++)
        {
            printf("Network's output %d : %f \n", j, lay[num_layers-1].neu[j].actv);
            printf("Desired Output %d : %f\n\n", j, desired_outputs[i][j]);
            if(lay[num_layers-1].neu[j].actv > max)
            {
                max = lay[num_layers-1].neu[j].actv;
                result = j;
            }
        }
        printf("\n");
        printf("Result : %d\n\n", result);
		printf("----------------------------\n\n");
    }
}

/*
 * Function: use_neuralnetwork
 * ----------------------------
 *   Called after the training,
 *   Test values of outputs according to inputs
 *
 *    arg1: -
 *    .....
 *
 *   returns: -
 */
void use_nn(int c, char *v[])
{
    for(int i = 2; i < c; i++)
    {

		float array[SIZE];
    	for(int j = 0; j < SIZE; j++)
       		array[j] = 0;
    	SDL_Surface *img = loadImage(v[i]);
    	imageToNeural(img,array);

    	test = array;


        printf("Input %d\n\n", i);
        for(int j = 0; j < num_neurons[0]; j++)
        {
            lay[0].neu[j].actv = test[j];
        }
        forward_prop();

        float max = 0;
        int result = 0;
        for(int j = 0; j < num_neurons[num_layers-1]; j++)
        {
            printf("Network's output %d : %f \n", j, lay[num_layers-1].neu[j].actv);
            //printf("Desired Output %d : %f\n\n", j, desired_outputs[i][j]);
            if(lay[num_layers-1].neu[j].actv > max)
            {
                max = lay[num_layers-1].neu[j].actv;
                result = j;
            }
        }
        printf("\n");
        printf("Result : %d\n\n", result);
		printf("----------------------------\n\n");
    }
}

void test1000nn(void) 
{
    float * testinput[10000];
    float testoutput[10000][10];

    mnisttest_imageparse("../mnist/testimage_mnist", testinput);
    mnisttest_labelparse("../mnist/testlabel_mnist", testoutput);

    int count = 0;
    for(int ep = 0; ep < 1; ep++)
    {
        for(int i = 0; i < 10000; i++)
        {
            for(int j = 0; j < num_neurons[0]; j++)
            {
                lay[0].neu[j].actv = testinput[i][j];
            }

            forward_prop();

            float val = 0;
            float result = 0;
            for(int j = 0; j < num_neurons[num_layers-1]; j++)
            {
                if(lay[num_layers-1].neu[j].actv > val)
                {
                    val = lay[num_layers-1].neu[j].actv;
                    result = j;
                }
            }
            
            int desired = 0;
            for(int k = 0; k <10; k++)
            {
                if(testoutput[i][k] == 1)
                {
                    desired = k;
                }
            }

            if(desired == result)
            {
                count++;
            } 
        }
    }
    printf("%d/10000\n",count);
}

