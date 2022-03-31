#include<stdio.h>
#include<stdlib.h>

/* Insertion Sort */
int sort(int* arr, int n){
	for(int i=1;i<n;i++){
		int j=i-1;
		int key=arr[i];
		while(j>=0 && arr[j]>key){
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=key;
	}
}

int printArray(int* arr, int n){
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int main(){
	int n;
	scanf("%d",&n);
	int* arr = (int*) malloc(sizeof(int)*n);

	for(int i=0;i<n;i++){
		scanf("%d",arr+i);
	}
	printf("Size of input array: %d\n", n);
	printf("Input array: ");
	printArray(arr, n);

	sort(arr, n);

	printf("Sorted array: ");
	printArray(arr, n);

	return 0;
}
