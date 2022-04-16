#include "../inc/struct_library_address.h"

void default_address_library_t(address_library_t *lib)
{
    for (int i = 0; i < MAX_QUEUE; i++)
    {
        lib->data->ptr = 0;
        lib->data->create = false;
        lib->data->free = false;
    }
    lib->size = 0;
}

void add_address_create(address_library_t *lib_address, size_t address)
{
    if (lib_address->size <= MAX_QUEUE)
    {
        lib_address->data->ptr = address;
        lib_address->data->create = true;
        lib_address->size++;
    }
}
void add_address_free(address_library_t *lib_address, size_t address)
{
    if (lib_address->size <= MAX_QUEUE)
    {
        lib_address->data->ptr = address;
        lib_address->data->free = true;
        lib_address->size++;
    }
}

void print_library_address(const address_library_t *lib_addresses)
{
    if (lib_addresses->size == 0)
        printf("Адресса не использованны!\n");
    else
        for (int i = 0; i < lib_addresses->size; i++)
        {
            if (lib_addresses->data[i].create == true)
                printf("Cоздан: %p\n", (void *) &lib_addresses->data[i].ptr);
            if (lib_addresses->data[i].free == true)
                printf("Освобожден: %p\n", (void *) &lib_addresses->data[i].ptr);
        }
}