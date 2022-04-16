#ifndef _STRUCT_MODELING_H
#define _STRUCT_MODELING_H

typedef struct st_model
{
    int amount_input;
    int amount_output;
    int amount_calls;

    double model_time;
    double dowtime;
    double consideration_all;
    double add_all;

    int current_length_queue;
    double average_length_queue;
    double average_arrival_time;
} modeling_t;

void default_modeling_t(modeling_t *modeling);

#endif //_STRUCT_MODELING_H
