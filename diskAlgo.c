#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CYLINDERS 10000
#define REQUESTS 5000

#define BILLION  1000000000L;

int fcfs(int *requests, int start) {

	struct timespec start_time, stop_time;
	double time_taken;

	if( clock_gettime( CLOCK_REALTIME, &start_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	int i = 0, num_of_head_movements = 0, start_position = requests[start];

	for(i = start; i < REQUESTS; i++) {

		num_of_head_movements += abs(requests[i] - start_position);
	}

	for(i = 0; i < start; i++) {

		num_of_head_movements += abs(start_position - requests[i]);
	}

	if( clock_gettime( CLOCK_REALTIME, &stop_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	time_taken = ( stop_time.tv_sec - start_time.tv_sec )
		+ (double)( stop_time.tv_nsec - start_time.tv_nsec )
		/ (double)BILLION;
	printf( "Time taken for FCFS: %lf\n", time_taken );

	return num_of_head_movements;
}


int sstf(int *requests, int start) {
	struct timespec start_time, stop_time;
	double time_taken;
	if( clock_gettime( CLOCK_REALTIME, &start_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}
	int left_ind = start-1, right_ind = start+1;
	int left_diff = 0, right_diff = 0;
	int num_of_head_movements = 0, total = REQUESTS-2, new_head = start, head_value = requests[start];
	while(total >= 0) {
		left_diff = abs(requests[new_head] - requests[left_ind]);
		right_diff = abs(requests[right_ind] - requests[new_head]);
		if(left_diff < right_diff) {
			num_of_head_movements += left_diff;
			new_head = left_ind;
			left_ind--;
		}
		else {
			num_of_head_movements += right_diff;
			new_head = right_ind;
			right_ind++;
		}
		total--;
	}
	if( clock_gettime( CLOCK_REALTIME, &stop_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}
	time_taken = ( stop_time.tv_sec - start_time.tv_sec )
		+ (double)( stop_time.tv_nsec - start_time.tv_nsec )
		/ (double)BILLION;
	printf( "Time taken for SSTF: %lf\n", time_taken );
	return num_of_head_movements;
}

int scan(int * requests, int start) {
	struct timespec start_time, stop_time;
	double time_taken;
	if( clock_gettime( CLOCK_REALTIME, &start_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	int i = 0, curr_index = 0, start_pos = requests[start], difference = 0;
	int num_of_head_movements = 0, curr_i = 0;

	for(i = start-1; i >= 0; --i) {

		curr_index = requests[i];
		difference = abs(start_pos - curr_index);
		num_of_head_movements += difference;
		start_pos = curr_index;

	}

	num_of_head_movements += start_pos;
	start_pos = 0;

	for(i = start+1; i < REQUESTS; i++) {

		curr_index = requests[i];
		difference = abs(curr_index - start_pos);
		num_of_head_movements += difference;
		start_pos = curr_index;

	}
	if( clock_gettime( CLOCK_REALTIME, &stop_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}
	time_taken = ( stop_time.tv_sec - start_time.tv_sec )
		+ (double)( stop_time.tv_nsec - start_time.tv_nsec )
		/ (double)BILLION;
	printf( "Time taken for SCAN: %lf\n", time_taken );

	return num_of_head_movements;

}
int cscan(int *requests, int start) {
	struct timespec start_time, stop_time;
	double time_taken;
	if( clock_gettime( CLOCK_REALTIME, &start_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}
	int curr_index = 0, start_pos = requests[start], difference = 0;
	int num_of_head_movements = 0, curr_i = 0, upper_bound = CYLINDERS - 1;
	for(int i = start+1; i < REQUESTS; i++) {
		curr_index = requests[i];
		difference = abs(start_pos - curr_index);
		num_of_head_movements += difference;
		start_pos = curr_index;
	}
	num_of_head_movements += upper_bound - start_pos; 
	start_pos = 0;
	num_of_head_movements += upper_bound;
	for(int j = 0; j < start; j++) {
		curr_index = requests[j];
		difference = abs(curr_index - start_pos);
		num_of_head_movements += difference;
		start_pos = curr_index;
	}
	if( clock_gettime( CLOCK_REALTIME, &stop_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	time_taken = ( stop_time.tv_sec - start_time.tv_sec )
		+ (double)( stop_time.tv_nsec - start_time.tv_nsec )
		/ (double)BILLION;
	printf( "Time taken for C-SCAN: %lf\n", time_taken );
	return num_of_head_movements;
}

int clook(int* requests, int start) {
	struct timespec start_time, stop_time;
	double time_taken;
	if( clock_gettime( CLOCK_REALTIME, &start_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	int curr_index = 0, start_pos = requests[start], difference = 0;
	int num_of_head_movements = 0, curr_i = 0;
	for(int i = start+1; i < REQUESTS; i++) {
		curr_index = requests[i];
		difference = abs(start_pos - curr_index);
		num_of_head_movements += difference;
		start_pos = curr_index;
	}
	for(int j = 0; j < start; j++) {
		curr_index = requests[j];
		difference = abs(curr_index - start_pos);
		num_of_head_movements += difference;
		start_pos = curr_index;
	}
	if( clock_gettime( CLOCK_REALTIME, &stop_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	time_taken = ( stop_time.tv_sec - start_time.tv_sec )
		+ (double)( stop_time.tv_nsec - start_time.tv_nsec )
		/ (double)BILLION;
	printf( "Time taken for C-LOOK: %lf\n", time_taken );
	return num_of_head_movements;
}

int look(int *requests, int start) {
	struct timespec start_time, stop_time;
	double time_taken;
	if( clock_gettime( CLOCK_REALTIME, &start_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	int i = 0, curr_index = 0, start_pos = requests[start], difference = 0;
	int num_of_head_movements = 0, curr_i = 0;

	for(i = start+1; i < REQUESTS; i++) {

		curr_index = requests[i];
		difference = abs(start_pos - curr_index);
		num_of_head_movements += difference;
		start_pos = curr_index;
	}
	
	for(i = start-1; i >= 0; --i) {

		curr_index = requests[i];
		difference = abs(curr_index - start_pos);
		num_of_head_movements += difference;
		start_pos = curr_index;
	}
	if( clock_gettime( CLOCK_REALTIME, &stop_time) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	time_taken = ( stop_time.tv_sec - start_time.tv_sec )
		+ (double)( stop_time.tv_nsec - start_time.tv_nsec )
		/ (double)BILLION;
	printf( "Time taken for LOOK: %lf\n", time_taken );

	return num_of_head_movements;
}

//selection sort
void sort(int* requests){ 
	int temp;
	for(int i = 0; i < REQUESTS; i++) {
		for(int j = i + 1; j < REQUESTS; j++) {
			if (requests[i] > requests[j]) {
				temp = requests[i];
				requests[i] = requests[j];
				requests[j] = temp;
			}
		}
	}
	return;
}

int main (int argc, char *argv[]) {

	int requests[REQUESTS];
	int start;
	if(argc != 2) {
		printf("Please run program with starting index from 0-4999. Ex. ./diskAlgo 4500\n");
		return 0;
	}
	start = atoi(argv[1]);
	srand(time(NULL));
	for(int i = 0; i < REQUESTS; i++) {
		requests[i] = rand() % 10000;
	}
	sort(requests);
	printf("\nstart index: %d, start value: %d\n\n", start, requests[start]);
	printf("Total number of Head movements in FCFS: %d\n\n", fcfs(requests, start));
	printf("Total number of Head movements in SSTF: %d\n\n", sstf(requests, start));
	printf("Total number of Head movements in SCAN: %d\n\n", scan(requests, start));
	printf("Total number of Head movements in C-SCAN: %d\n\n", cscan(requests, start));
	printf("Total number of Head movements in LOOK: %d\n\n", look(requests, start));
	printf("Total number of Head movements in C-LOOK: %d\n\n", clook(requests, start));
	return 0;
}
