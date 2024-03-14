#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void *Alloc(size_t sz)
{
extraMemoryAllocated += sz;
size_t* ret = malloc(sizeof(size_t) + sz);
*ret = sz;
printf("Extra memory allocated, size: %ld\n", sz);
return &ret[1];
}

void DeAlloc(void* ptr)
{
size_t* pSz = (size_t*)ptr - 1;
extraMemoryAllocated -= *pSz;
printf("Extra memory deallocated, size: %ld\n", *pSz);
free((size_t*)ptr - 1);
}
size_t Size(void* ptr)
{
return ((size_t*)ptr)[-1];
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r){
    int leftarray[r / 2], rightarray[r/2], mergedarray[r], subindex1 = 0, subindex2 = 0, subindex3 = 0;

for (int i=0;i<=r/2;i++){
    leftarray[i] = pData[i];
}
for (int i=r/2+1;i<=r;i++){
    rightarray[i] = pData[i];
}
while(subindex1 < r/2 && subindex2 < r/2){
    if(leftarray[subindex1] <= rightarray[subindex2]){
        mergedarray[subindex3] = leftarray[subindex1];
        subindex1++;
    }
    else{
        mergedarray[subindex3] = rightarray[subindex2];
        subindex2++;
    }
    subindex3++;
}
while(subindex1 < r/2){
    mergedarray[subindex3] = leftarray[subindex1];
    subindex1++;
    subindex3++;
}
while(subindex2 < r/2){
    mergedarray[subindex3] = leftarray[subindex2];
    subindex2++;
    subindex3++;
}
}




// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
FILE* inFile = fopen(inputFileName,"r");
int dataSz = 0;
int i, n, *data;
*ppData = NULL;

if (inFile)
{
fscanf(inFile,"%d\n",&dataSz);
*ppData = (int *)malloc(sizeof(int) * dataSz);
// Implement parse data block
if (*ppData == NULL)
{
printf("Cannot allocate memory\n");
exit(-1);
}
for (i=0;i<dataSz;++i)
{
fscanf(inFile, "%d ",&n);
data = *ppData + i;
*data = n;
}

fclose(inFile);
}

return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    int i, sz = (dataSz > 100 ? dataSz - 100 : 0);
    int firstHundred = (dataSz < 100 ? dataSz : 100);
    printf("\tData:\n\t");
    for (i=0;i<firstHundred;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\t");

    for (i=sz;i<dataSz;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\n");
}

int main(void)
{
clock_t start, end;
int i;
    double cpu_time_used;
char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };

for (i=0;i<4;++i)
{
int *pDataSrc, *pDataCopy;
int dataSz = parseData(fileNames[i], &pDataSrc);

if (dataSz <= 0)
continue;

pDataCopy = (int *)malloc(sizeof(int)*dataSz);

printf("---------------------------\n");
printf("Dataset Size : %d\n",dataSz);
printf("---------------------------\n");

printf("Merge Sort:\n");
memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
extraMemoryAllocated = 0;
start = clock();
mergeSort(pDataCopy, 0, dataSz - 1);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
printArray(pDataCopy, dataSz);

free(pDataCopy);
free(pDataSrc);
}

}
