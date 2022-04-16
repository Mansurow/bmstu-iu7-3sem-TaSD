#include <stdio.h>
#include <stdlib.h>

#include "../inc/struct_params.h"
#include "../inc/struct_library_address.h"

#include "../inc/array_modelling_queue.h"
#include "../inc/list_modelling_queue.h"

#include "../inc/menu.h"
#include "../inc/take_measure.h"

int main()
{
    setbuf(stdout, NULL);

    model_params params;
    default_model_params(&params);

    address_library_t addresses;
    default_address_library_t(&addresses);
    int rc = EXIT_SUCCESS;
    int step = -1;
    
    while(step != 0)
    {
        if (step != 0)
            print_menu();
        input_step_menu(&step, 0, 7);
        if (step == 1)
            array_queue_modeling(&params);
        else if (step == 2)
            list_queue_modeling(&params, &addresses);
        else if (step == 3)
            print_library_address(&addresses);
        else if (step == 4)
            analys_time_queue();
        else if (step == 5)
            analys_size_queue();
        else if (step == 6)
            change_add_time(&params);
        else if (step == 7)
            change_cons_time(&params);
        else if (step == 0)
            printf("До свидания!");
    }

    return rc;
}