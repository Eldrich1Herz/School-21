#include "documentation_module.h"

int validate(char* data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

int* check_available_documentation_module(int (*validate)(char*), int document_count, ...) {
    int* answ = (int*)malloc(15 * sizeof(int));
    va_list ap;
    va_start(ap, document_count);
    for (int i = 0; i < document_count; ++i) {
        char* elem = va_arg(ap, char*);
        answ[i] = validate(elem);
    }
    va_end(ap);
    return answ;
}
