#define M 1000 // numarul de "intrari" //
typedef int Hash[M];
typedef int DataType;
Hash H;

void InitHash1(Hash H)
{ int i;

  for (i=0; i<M; H[i++]=0);
}

inline int h(DataType K)
{
  return K;
}

int Search1(Hash H, DataType K)
/* Intoarce -1 daca elementul nu exista in hash
   sau indicele in hash daca el exista */
{
  return H[h(K)] ? h(K) : -1;
}

void Add1(Hash H, DataType K)
{
  H[h(K)]=1;
}

void Delete1(Hash H, DataType K)
{
  H[h(K)]=0;
}
