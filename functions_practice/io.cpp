#include "io.h"

void read(FILE* f, uint64_t& val)
{
    fscanf_s(f, "%llu", &val);
}

void read(FILE* f, double& val)
{
    fscanf_s(f, "%lf", &val);
}

void read(FILE* f, int& val)
{
    fscanf_s(f, "%d", &val);
}

void read(FILE* f, char* val)
{
    fscanf_s(f, "%s", val);
}

void write(FILE* f, uint64_t val)
{
    fprintf_s(f, "%llu\n", val);
}

void write(FILE* f, double val)
{
    fprintf_s(f, "%lf\n", val);
}

void write(FILE* f, int val)
{
    fprintf_s(f, "%d\n", val);
}

void write(FILE* f, const char* val)
{
    fprintf_s(f, "%s\n", val);
}
