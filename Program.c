#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h> 

void sortArray(int *arr, int n) 
{ 
	int temp; 
	for (int i = 0; i < n - 1; i++) 
	{ 
		for (int j = 0; j < n - i - 1; j++) 
		{ 
			if (arr[j] > arr[j + 1]) 
			{ 
				temp = arr[j]; 
				arr[j] = arr[j + 1]; 
				arr[j + 1] = temp; 
			} 
		} 
	} 
} 

int main() 
{ 
	int n; 
	pid_t pid = fork(); 
	if (pid == -1) 
	{ 
		perror("Fork failed"); 
		exit(1); 
	} 
	else if (pid == 0) 
	{ // Child process 
		printf("Parent process ID: %d\n", getppid()); 
		printf("\nChild process ID: %d\n", getpid()); 
		printf("Enter number of elements in the array: "); 
		scanf("%d", &n); 
		int arr[n]; 
		printf("Enter elements of the array: \n");

		for (int i = 0; i < n; i++) 
		{ 
			scanf("%d", &arr[i]); 
		} 
		sortArray(arr, n); 
		printf("Sorted array in child process:\n"); 
		for (int i = 0; i < n; i++) 
		{ 
			printf("%d ", arr[i]); 
		} 
	} 
	else 
	{ 
	// Parent process 
	wait(NULL); 
	} 
	return 0; 
}