#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct bucketItem sBucketItem;
struct bucketItem
{
	int iValue;
	sBucketItem *pNext;
};

typedef struct bucket sBucket;
struct bucket
{
	sBucketItem *pHead;
	sBucketItem *pTail;
};

sBucketItem *pAllBucketItemPoint;
sBucket *pBucketArray;

void initBucket(int iArraySize, int iMaxByteSize)
{
	pAllBucketItemPoint = (sBucketItem *)malloc(iArraySize * sizeof(sBucketItem));
	pBucketArray = (sBucket *)malloc((iMaxByteSize + 1) * sizeof(sBucket));
}

void resetBucket(int iArraySize, int iMaxByteSize)
{
	bzero(pAllBucketItemPoint, iArraySize * sizeof(sBucketItem));
	bzero(pBucketArray, iMaxByteSize * sizeof(sBucket));
}

void putBucket(int *piValues, int iArraySize, int iBytePosition)
{
	int i = 0;
	for( i; i < iArraySize; i++)
	{
		int iByteValue = getByteValue(*(piValues + i), iBytePosition);
		//printf("iByte: %d \n", iByteValue);
		(pAllBucketItemPoint + i)->iValue = *(piValues + i);
		(pAllBucketItemPoint + i)->pNext = NULL;
		if((pBucketArray + iByteValue)->pHead == NULL)
		{
			// this bucket is empty
			(pBucketArray + iByteValue)->pHead = pAllBucketItemPoint + i;
			(pBucketArray + iByteValue)->pTail = pAllBucketItemPoint + i;
		}else
		{
			(pBucketArray + iByteValue)->pTail->pNext = pAllBucketItemPoint + i;
			(pBucketArray + iByteValue)->pTail = pAllBucketItemPoint + i;
		}
	}
}

void pushBackBucketToOriginArray(int *piValues, int iMaxByteValue)
{
	int i = 0, j = 0;
	for( i; i < iMaxByteValue + 1; i++)
	{
		while((pBucketArray + i)->pHead != NULL)
		{
			*(piValues + j) = (pBucketArray + i)->pHead->iValue;
			(pBucketArray + i)->pHead = (pBucketArray + i)->pHead->pNext;
			j++;
		}
	}
}

int getByteValue(int iNum, int iByte)
{
	if(iByte < 1)
		return 0;
	int i = 1;
	for(i; i < iByte; i++)
	{
		iNum = floor(iNum/10);
	}
	return iNum % 10;
}

void doSort(int *piValue, int iArraySize, int iByteCount, int iMaxByteValue)
{
	initBucket(iArraySize, iMaxByteValue);
	int iBytePosition = 1;
	
	for(; iBytePosition <= iByteCount; iBytePosition++)
	{
		putBucket(piValue, iArraySize, iBytePosition);
		pushBackBucketToOriginArray(piValue, iMaxByteValue);
	}
	return;
}

void printArray(int *piValue, int iArraySize)
{
	int i = 0;
	for( ; i < iArraySize; i++)
	{
		printf("%d ",*(piValue + i));
	}
}

int main(int argc, char *argv[])
{
	int values[] = {12,240,130,250,36,54,674,457,987,856,182,137,354,141};
	initBucket(14, 9);
	doSort(values, 14, 3, 9);
	printArray(values, 14);
	free(pAllBucketItemPoint);
	free(pBucketArray);
	printf("\n");
	return 0;
}
