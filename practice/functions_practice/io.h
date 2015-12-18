#pragma once
#include <cstdio>
#include <cstdint>

void read(FILE *f, uint64_t& val);
void read(FILE *f, double& val);
void read(FILE *f, int& val);
void read(FILE *f, char* val);

void write(FILE *f, uint64_t val);
void write(FILE *f, double val);
void write(FILE *f, int val);
void write(FILE *f, const char* val);
