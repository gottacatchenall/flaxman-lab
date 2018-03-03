// Array length macro
#define len(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#define ENV_FACTOR_RANDOM       0
#define ENV_FACTOR_CLUSTERED    1
#define ENV_FACTOR_GRADIENT     2
